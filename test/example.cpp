#include <rjsjai.h>
#include <iostream>
#include <fstream>

int main() {
    auto a = ai_create("5e966ba7-3949-40c1-b207-aa0adab6bda1");
    constexpr int type = AI_TYPE_DRAW;
    constexpr const char* prompt = "apple and banana";
    int err = ai_send(a, type, prompt);
    std::cout << err << std::endl;
    int size = ai_result(a, nullptr);
    char* buf = new char[size + 1]{};
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
