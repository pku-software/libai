#include <rjsjai.h>
#include <iostream>
#include <fstream>

int main() {
    auto a = ai_create("your token goes here");
    constexpr int type = AI_TYPE_CHAT;
    constexpr const char* prompt = "Hi there. Who are you?";
    int err = ai_send(a, type, prompt);
    std::cout << err << std::endl;
    int size = ai_result(a, nullptr);
    char* buf = new char[size + 1];
    ai_result(a, buf);
    if (err || type == AI_TYPE_CHAT || type == AI_TYPE_TRANSLATE) {
        std::cout << buf << std::endl;
    } else {
        std::ofstream ofs("a.png", std::ios::binary);
        ofs.write(buf, size);
    }
    ai_free(a);
    delete[] buf;
}
