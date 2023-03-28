#ifndef RJSJAI_H
#define RJSJAI_H

#ifdef __cplusplus
extern "C" {
#endif

#define AI_TYPE_TRANSLATE 1
#define AI_TYPE_CHAT 2
#define AI_TYPE_DRAW 3
#define AI_TYPE_WOLFRAM 4

#define AI_ERROR_NONE 0
#define AI_ERROR_HTTP_UNKNOWN 1
#define AI_ERROR_HTTP_CONNECTION 2
#define AI_ERROR_HTTP_BIND_IP_ADDRESS 3
#define AI_ERROR_HTTP_READ 4
#define AI_ERROR_HTTP_WRITE 5
#define AI_ERROR_HTTP_REDIRECT_COUNT_EXCEEDED 6
#define AI_ERROR_HTTP_CANCELED 7
#define AI_ERROR_HTTPS_CONNECTION 8
#define AI_ERROR_HTTPS_CERTIFICATE 9
#define AI_ERROR_HTTPS_VERIFICATION 10
#define AI_ERROR_HTTP_CONNECTION_TIMEOUT 13
#define AI_ERROR_RESPONSE_MALFORMED 128
#define AI_ERROR_RESPONSE_FAILED 129
#define AI_ERROR_RESPONSE_INVALID_DATA 130
#define AI_ERROR_MISUSE_NOT_SENT 256
#define AI_ERROR_MISUSE_UNKNOWN_TYPE 257

struct RJSJAI_;
typedef struct RJSJAI_ RJSJAI;

RJSJAI* ai_create(const char* token);
int ai_send(RJSJAI* ai, int type, const char* prompt);
int ai_status(RJSJAI* ai);
int ai_result(RJSJAI* ai, char* dest);
void ai_free(RJSJAI* ai);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
