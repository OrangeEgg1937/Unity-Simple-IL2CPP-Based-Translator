#include "translator.h"

#include <map>

std::map<std::string, std::string> translation_map = {
    {"Hello, welcome to the test Demo!", "你好歡迎來到測試Demo!"},
    {"You can press the button nearby!", "你可以按下這附近的按鈕!"},
    {"You can also press the speed button!", "也可以按一下速度按鈕!"},
    {"This message keeps looping!", "此訊息不斷循環!"},
    {"This is the last message.", "這是最後一則訊息!"},
    {"Pressed the settings button.", "按下設定按鈕"},
    {"You clicked the save button.", "你點擊了儲存按鈕"},
    {"Setting", "[設定]"},
    {"Save", "[儲存]"},
};

namespace translator {

    std::string translate(std::string orig) {
        auto it = translation_map.find(orig);
        if (it != translation_map.end()) {
            return it->second;
        }
        return orig; // Return original if no translation found
    }

} // namespace translator