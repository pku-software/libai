#include "./ai_impl.h"

#include <basen.hpp>
#include <iterator>

#include "./api_def.h"
#include "rjsjai.h"

using namespace std::literals;

namespace rjsj_ai {

Ai::Ai(const char* token)
    : token(token), cli(HOST, PORT), errorCode{AI_ERROR_MISUSE_NOT_SENT} {
    httplib::Headers headers;
    headers.insert({"Authorization", "Bearer "s + token});
    cli.set_default_headers(headers);
    cli.set_read_timeout(30);
}

std::string getHttpErrorDetail(httplib::Error e) {
    switch (e) {
        case httplib::Error::Unknown: return "Unknown HTTP error"s;
        case httplib::Error::Connection:
            return "Failed to establish HTTP connection"s;
        case httplib::Error::BindIPAddress: return "Failed to bind IP address"s;
        case httplib::Error::Read: return "Error while reading HTTP contents"s;
        case httplib::Error::Write: return "Error while writing HTTP contents"s;
        case httplib::Error::ExceedRedirectCount:
            return "Maximum count of HTTP redirection exceeded"s;
        case httplib::Error::Canceled: return "HTTP connection cancelled"s;
        case httplib::Error::SSLConnection:
            return "Failed to establish SSL connection"s;
        case httplib::Error::SSLLoadingCerts:
            return "Failed to load SSL certification"s;
        case httplib::Error::SSLServerVerification:
            return "Failed to verify SSL server"s;
        default: return "Internal error: unsupported HTTP error"s;
    }
}

bool decodeDataUrl(const std::string& url, std::string& result) {
#ifdef __cpp_lib_starts_ends_with
    if (!url.starts_with("data:")) {
        return false;
    }
#endif
    auto semicolon = url.find(";base64,");
    if (semicolon == std::string::npos) {
        return false;
    }
    auto begin = url.begin() + semicolon + 8;
    bn::decode_b64(begin, url.end(), std::back_inserter(result));
    return true;
}

void Ai::sendRequest(const char* path, nlohmann::json body, bool isImage) {
    auto reqStr = nlohmann::to_string(body);
    auto res =
        cli.Post(path, reqStr.c_str(), reqStr.size(), "application/json");
    if (auto e = res.error(); e != httplib::Error::Success) {
        errorCode = static_cast<int>(e);
        error = getHttpErrorDetail(e);
        return;
    }
    nlohmann::json response;
    try {
        response = nlohmann::json::parse(res->body);
    } catch (nlohmann::json::parse_error& e) {
        errorCode = AI_ERROR_RESPONSE_MALFORMED;
        error = e.what();
        return;
    }
    if (!response.is_object()) {
        errorCode = AI_ERROR_RESPONSE_MALFORMED;
        error = "Response from server is not a JSON object"s;
        return;
    }
    if (!response.contains("status")) {
        errorCode = AI_ERROR_RESPONSE_MALFORMED;
        error = "Response from server do not have a 'status' property"s;
        return;
    }
    if (response["status"] != "ok") {
        errorCode = AI_ERROR_RESPONSE_FAILED;
        if (response.contains("text")) {
            if (!response["text"].is_string()) {
                error = nlohmann::to_string(response["text"]);
            } else {
                error = std::string(response["text"]);
            }
        } else {
            error = "Unknown failed status, no more info provided"s;
        }
        return;
    }
    auto checkPayload = [&](const char* propName) {
        if (!response.contains(propName)) {
            errorCode = AI_ERROR_RESPONSE_MALFORMED;
            error = "Status ok, but no payload provided"s;
            return false;
        }
        if (!response[propName].is_string()) {
            errorCode = AI_ERROR_RESPONSE_MALFORMED;
            error = propName + " property is not a string: "s +
                    nlohmann::to_string(response[propName]);
            return false;
        }
        return true;
    };
    if (isImage) {
        if (!checkPayload("image")) return;
        if (!decodeDataUrl(response["image"], this->response)) {
            errorCode = AI_ERROR_RESPONSE_INVALID_DATA;
            error = "Response contains an invalid data url"s;
            return;
        }
    } else {
        if (!checkPayload("text")) return;
        this->response = response["text"];
    }
    errorCode = 0;
}

int Ai::send(int type, const char* prompt) {
    switch (type) {
        case AI_TYPE_TRANSLATE:
            sendRequest(TRANSLATE_PATH, TRANSLATE_BODY(prompt), false);
            break;
        case AI_TYPE_CHAT:
            sendRequest(CHAT_PATH, CHAT_BODY(prompt), false);
            break;
        case AI_TYPE_DRAW:
            sendRequest(DRAW_PATH, DRAW_BODY(prompt), true);
            break;
        case AI_TYPE_WOLFRAM:
            sendRequest(WOLFRAM_PATH, WOLFRAM_BODY(prompt), true);
            break;
        default: errorCode = AI_ERROR_MISUSE_UNKNOWN_TYPE; break;
    }
    return errorCode;
}

int Ai::getError() const {
    return errorCode;
}

int Ai::writeResult(char* dest) const {
    if (errorCode) {
        if (dest) {
            std::memcpy(dest, error.c_str(), error.size());
        }
        return error.size();
    } else {
        if (dest) {
            std::memcpy(dest, response.c_str(), response.size());
        }
        return response.size();
    }
}

}  // namespace rjsj_ai
