#include "./ai_impl.h"

using libai::Ai;

extern "C" {

Ai* ai_create(const char* token) {
    return new libai::Ai(token);
}
int ai_send(Ai* ai, int type, const char* prompt) {
    return ai->send(type, prompt);
}
int ai_status(Ai* ai) {
    return ai->getError();
}
int ai_result(Ai* ai, char* dest) {
    return ai->writeResult(dest);
}
void ai_free(Ai* ai) {
    delete ai;
}
}
