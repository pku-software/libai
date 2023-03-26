#include <libai.h>
#include <iostream>

int main() {
    auto a = ai_create("my_token");
    std::cout << ai_send(a, AI_TYPE_CHAT, "Hello!") << std::endl;
    int size = ai_result(a, nullptr);
    char* buf = new char[size + 1];
    ai_result(a, buf);
    ai_free(a);
    std::cout << buf << std::endl;
    delete[] buf;
}
