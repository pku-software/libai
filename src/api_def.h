#include <nlohmann/json.hpp>

#define STR_(S) #S
#define STR(S) STR_(S)

#define HOST STR(SERVER_HOST)
#define PORT SERVER_PORT

#define TRANSLATE_PATH "/api/ai/v1/translate"

#define TRANSLATE_BODY(prompt) \
    nlohmann::json({{"text", prompt}, {"from", "en"}, {"to", "zh"}})

#define CHAT_PATH "/api/ai/v1/chat"

#define CHAT_BODY(prompt)                     \
    nlohmann::json({{"prompt", prompt},       \
                    {"max_tokens", 10},       \
                    {"temperature", 0.9},     \
                    {"top_p", 1},             \
                    {"frequency_penalty", 0}, \
                    {"presence_penalty", 0},  \
                    {"stop", {"\n", " Human:", " AI:"}}})

#define DRAW_PATH "/api/ai/v1/draw"

#define DRAW_BODY(prompt)               \
    nlohmann::json({{"prompt", prompt}, \
                    {"number", 1},      \
                    {"width", 1024},    \
                    {"height", 1024}})

#define WOLFRAM_PATH "/api/ai/v1/wolfram"

#define WOLFRAM_BODY(prompt) nlohmann::json({{"input", prompt}})
