#include <nlohmann/json.hpp>

#define STR_(S) #S
#define STR(S) STR_(S)

#define HOST STR(SERVER_HOST)
#define PORT SERVER_PORT

#define TRANSLATE_PATH "/api/v1/ai/translate"

#define TRANSLATE_BODY(prompt) \
    nlohmann::json({{"text", prompt}, {"from", "en"}, {"to", "zh"}})

#define CHAT_PATH "/api/v1/ai/chat"

#define CHAT_BODY(prompt) nlohmann::json({{"prompt", prompt}})

#define DRAW_PATH "/api/v1/ai/draw"

#define DRAW_BODY(prompt)               \
    nlohmann::json({{"prompt", prompt}, \
                    {"number", 1},      \
                    {"width", 1024},    \
                    {"height", 1024}})

#define WOLFRAM_PATH "/api/v1/ai/wolfram"

#define WOLFRAM_BODY(prompt) nlohmann::json({{"input", prompt}})
