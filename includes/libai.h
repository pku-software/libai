#ifndef LIBAI_H
#define LIBAI_H

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
#define AI_ERROR_HTTP_CONNECTION_TIMEOUT 13
#define AI_ERROR_RESPONSE_MALFORMED 128
#define AI_ERROR_RESPONSE_FAILED 129
#define AI_ERROR_RESPONSE_INVALID_DATA 130
#define AI_ERROR_MISUSE_NOT_SENT 256
#define AI_ERROR_MISUSE_UNKNOWN_TYPE 257

struct AI;

AI* ai_create(const char* token);
int ai_send(AI* ai, int type, const char* prompt);
int ai_status(AI* ai);
int ai_result(AI* ai, char* dest);
void ai_free(AI* ai);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
