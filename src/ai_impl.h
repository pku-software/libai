#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>

namespace rjsj_ai {

class Ai {
    std::string token;
    std::string response;
    int errorCode;
    std::string error;
    httplib::Client cli;

    void sendRequest(const char* path, nlohmann::json body, bool isImage);

public:
    Ai(const char* token);

    int send(int type, const char* prompt);
    int getError() const;
    int writeResult(char* dest) const;

    ~Ai() = default;
};

}
