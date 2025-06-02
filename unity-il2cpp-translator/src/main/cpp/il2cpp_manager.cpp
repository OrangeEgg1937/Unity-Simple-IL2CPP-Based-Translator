#include <string>
#include <android/log.h>
#include <dlfcn.h>

#include "shadowhook.h"
#include "il2cpp_manager.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "Il2cpp-Manager", __VA_ARGS__)
#define LIB_NAME "libil2cpp.so"

std::map<std::string, Il2CppClass *> TMP_klass_map;

void *handle = nullptr;

/**
 * Function pointers for IL2CPP functions
 */
size_t (*il2cpp_image_get_class_count)(const Il2CppImage *image) = nullptr;

void *(*il2cpp_image_get_class)(const Il2CppImage *image, size_t index) = nullptr;

const char *(*il2cpp_class_get_name)(const Il2CppClass *klass) = nullptr;

const MethodInfo *(*il2cpp_class_get_methods)(const Il2CppClass *klass, void **iter) = nullptr;

const char *(*il2cpp_method_get_name)(const MethodInfo *method) = nullptr;

uint32_t (*il2cpp_method_get_param_count)(const MethodInfo *method) = nullptr;

const Il2CppType* (*il2cpp_method_get_param)(const MethodInfo *method, uint32_t index) = nullptr;

Il2CppClass* (*il2cpp_class_from_il2cpp_type)(const Il2CppType* type) = nullptr;

/**
 * Function pointers for Convert C# string to C++ string
 */
Il2CppChar *(*il2cpp_string_chars)(const Il2CppString *str) = nullptr;

/**
 * Function pointers for TMPro functions
 */
Il2CppString *(*TMP_Text_get_text)(void *instance) = nullptr;

void (*TMP_Text_set_text)(void *instance, Il2CppString *text) = nullptr;

void (*TextMeshProUGUI_onEnable)(void *instance) = nullptr;

void (*TMP_Text_SetText)(void *instance, Il2CppString *text) = nullptr;

namespace TextMeshProUGUI_onEnable_hook {
    void *orig;
    void *stub;

    void proxy(void *instance) {
        SHADOWHOOK_STACK_SCOPE();

        LOGD("TextMeshProUGUI_onEnable_hook: instance=%p", instance);
        if (TMP_Text_get_text != nullptr) {
            auto *text = TMP_Text_get_text(instance);
            if (text != nullptr) {
                Il2CppChar *chars = il2cpp_string_chars(text);
                std::u16string str(chars, text->length);
                LOGD("TextMeshProUGUI_onEnable_hook: text=%s",
                     std::string(str.begin(), str.end()).c_str());
            } else {
                LOGD("TextMeshProUGUI_onEnable_hook: text is NULL");
            }
        }
        SHADOWHOOK_CALL_PREV(proxy, instance);
    }

    void hook() {
        if (TextMeshProUGUI_onEnable == nullptr) {
            __android_log_print(ANDROID_LOG_ERROR, "test", "TextMeshProUGUI_onEnable is NULL");
            return;
        }

        stub = shadowhook_hook_func_addr(
                (void *) TextMeshProUGUI_onEnable,
                (void *) proxy,
                &orig
        );

        int err = shadowhook_get_errno();
        const char *error_msg = shadowhook_to_errmsg(err);
        __android_log_print(ANDROID_LOG_WARN, "test", "(%p)hook return: %p, %d - %s",
                            TextMeshProUGUI_onEnable, stub, err,
                            error_msg);
    }
}

namespace TMP_Text_set_text_hook {
    void *orig;
    void *stub;

    void proxy(void *instance, Il2CppString *text) {
        SHADOWHOOK_STACK_SCOPE();

        LOGD("TMP_Text_set_text_hook: instance=%p, text=%p", instance, text);
        if (text != nullptr) {
            Il2CppChar *chars = il2cpp_string_chars(text);
            std::u16string str(chars, text->length);
            LOGD("TMP_Text_set_text_hook: current text=%s",
                 std::string(str.begin(), str.end()).c_str());
        }
        SHADOWHOOK_CALL_PREV(proxy, instance, text);
    }

    void hook() {
        if (TMP_Text_set_text == nullptr) {
            __android_log_print(ANDROID_LOG_ERROR, "test", "TMP_Text_set_text is NULL");
            return;
        }

        stub = shadowhook_hook_func_addr(
                (void *) TMP_Text_set_text,
                (void *) proxy,
                &orig
        );

        int err = shadowhook_get_errno();
        const char *error_msg = shadowhook_to_errmsg(err);
        __android_log_print(ANDROID_LOG_WARN, "test", "(%p)hook return: %p, %d - %s",
                            TMP_Text_set_text, stub, err,
                            error_msg);
    }
}

namespace TMP_Text_SetText_hook {
    void *orig;
    void *stub;

    void proxy(void *instance, Il2CppString *text) {
        SHADOWHOOK_STACK_SCOPE();

        LOGD("TMP_Text_SetText_hook: instance=%p, text=%p", instance, text);
        if (text != nullptr) {
            Il2CppChar *chars = il2cpp_string_chars(text);
            std::u16string str(chars, text->length);
            LOGD("TMP_Text_SetText_hook: current text=%s",
                 std::string(str.begin(), str.end()).c_str());
        }
        SHADOWHOOK_CALL_PREV(proxy, instance, text);
    }

    void hook() {
        if (TMP_Text_SetText == nullptr) {
            __android_log_print(ANDROID_LOG_ERROR, "test", "TMP_Text_SetText is NULL");
            return;
        }

        stub = shadowhook_hook_func_addr(
                (void *) TMP_Text_SetText,
                (void *) proxy,
                &orig
        );

        int err = shadowhook_get_errno();
        const char *error_msg = shadowhook_to_errmsg(err);
        __android_log_print(ANDROID_LOG_WARN, "test", "(%p)hook return: %p, %d - %s",
                            TMP_Text_SetText, stub, err,
                            error_msg);
    }
}

namespace il2cpp_domain_assembly_open_hook {
    void *orig;
    void *stub;

    void *proxy(void *domain, const char *name) {
        SHADOWHOOK_STACK_SCOPE();

        auto asm_ptr = SHADOWHOOK_CALL_PREV(proxy, domain, name);
        LOGD("il2cpp_domain_assembly_open_hook: domain=%p, name=%s, ptr=%p", domain, name, asm_ptr);

        return asm_ptr;
    }

    void hook() {
        stub = shadowhook_hook_sym_name(
                LIB_NAME,
                "il2cpp_domain_assembly_open",
                (void *) proxy,
                &orig
        );

        int err = shadowhook_get_errno();
        const char *error_msg = shadowhook_to_errmsg(err);
        __android_log_print(ANDROID_LOG_WARN, "test", "hook return: %p, %d - %s", stub, err,
                            error_msg);
    }
}

namespace il2cpp_assembly_get_image_hook {
    void *orig;
    void *stub;

    void *proxy(Il2CppAssembly *assembly) {
        SHADOWHOOK_STACK_SCOPE();

        auto image_ptr = SHADOWHOOK_CALL_PREV(proxy, assembly);
        //LOGD("il2cpp_assembly_get_image_hook: assembly=%p (%s), image_ptr=%p", assembly, assembly->aname.name, image_ptr);
        if (strcmp(assembly->aname.name, "Unity.TextMeshPro") == 0) {
            LOGD("Found Unity.TextMeshPro.dll, try to loop its class:");
            size_t class_count = il2cpp_image_get_class_count((const Il2CppImage *) image_ptr);
            for (size_t i = 0; i < class_count; ++i) {
                auto *klass = (Il2CppClass *) il2cpp_image_get_class(
                        (const Il2CppImage *) image_ptr, i);
                if (!klass) {
                    continue;
                }
                auto *class_name = il2cpp_class_get_name(klass);
                if (!class_name) {
                    continue;
                }
                TMP_klass_map[class_name] = (Il2CppClass *) klass;
            }

            // Get the TMP_Text Class out
            auto it = TMP_klass_map.find("TextMeshProUGUI");
            if (it != TMP_klass_map.end()) {
                Il2CppClass *tmp_text_class = it->second;
                LOGD("Found TextMeshProUGUI class: %p", tmp_text_class);
                void *_iter = nullptr;
                while (auto method_info = il2cpp_class_get_methods(tmp_text_class, &_iter)) {
                    auto method_name = il2cpp_method_get_name(method_info);
                    if (strcmp(method_name, "OnEnable") == 0) {
                        LOGD("Found method: %s", method_name);
                        TextMeshProUGUI_onEnable = (void (*)(void *)) method_info->methodPointer;
                        // Hook the OnEnable method
                        TextMeshProUGUI_onEnable_hook::hook();
                    }
                }

            } else {
                LOGD("TMP_Text class not found in Unity.TextMeshPro.dll");
            }

            // Get the TMP_Text Class out
            auto it2 = TMP_klass_map.find("TMP_Text");
            if (it2 != TMP_klass_map.end()) {
                Il2CppClass *tmp_text_class = it2->second;
                LOGD("Found TMP_Text class: %p", tmp_text_class);
                void *_iter = nullptr;
                while (auto method_info = il2cpp_class_get_methods(tmp_text_class, &_iter)) {
                    auto method_name = il2cpp_method_get_name(method_info);
                    auto param_count = il2cpp_method_get_param_count(method_info);
                    LOGD("[TMP_Text] Found method: %s", method_name);
                    if (strcmp(method_name, "get_text") == 0) {
                        LOGD("Found method: %s", method_name);
                        TMP_Text_get_text = (Il2CppString *(*)(void *)) method_info->methodPointer;
                    }
                    if (strcmp(method_name, "set_text") == 0) {
                        LOGD("Found method: %s", method_name);
                        TMP_Text_set_text = (void (*)(void *,
                                                      Il2CppString *)) method_info->methodPointer;
                        TMP_Text_set_text_hook::hook();
                    }
                    if (strcmp(method_name, "SetText") == 0 && param_count == 1) {
                        auto *param_type = il2cpp_method_get_param(method_info, 0);
                        auto *param_class = il2cpp_class_from_il2cpp_type(param_type);
                        auto *param_class_name = il2cpp_class_get_name(param_class);
                        LOGD("Found method: %s (param=%s)", method_name, param_class_name);
                        if (strcmp(param_class_name, "String") == 0) {
                            LOGD("Found method: %s", method_name);
                            TMP_Text_SetText = (void (*)(void *,
                                                         Il2CppString *)) method_info->methodPointer;
                            TMP_Text_SetText_hook::hook();
                        }
                    }
                }
            } else {
                LOGD("TMP_Text class not found in Unity.TextMeshPro.dll");
            }
        }

        return image_ptr;
    }

    void hook() {
        stub = shadowhook_hook_sym_name(
                LIB_NAME,
                "il2cpp_assembly_get_image",
                (void *) proxy,
                &orig
        );

        int err = shadowhook_get_errno();
        const char *error_msg = shadowhook_to_errmsg(err);
        __android_log_print(ANDROID_LOG_WARN, "test", "hook return: %p, %d - %s", stub, err,
                            error_msg);
    }
}

void il2cpp_manager_init() {

    handle = shadowhook_dlopen(LIB_NAME);
    if (handle) {
        il2cpp_image_get_class_count = (size_t (*)(const Il2CppImage *)) shadowhook_dlsym(handle,
                                                                                          "il2cpp_image_get_class_count");
        il2cpp_image_get_class = (void *(*)(const Il2CppImage *, size_t)) shadowhook_dlsym(handle,
                                                                                           "il2cpp_image_get_class");
        il2cpp_class_get_name = (const char *(*)(const Il2CppClass *)) shadowhook_dlsym(handle,
                                                                                        "il2cpp_class_get_name");
        il2cpp_class_get_methods = (const MethodInfo *(*)(const Il2CppClass *,
                                                          void **)) shadowhook_dlsym(handle,
                                                                                     "il2cpp_class_get_methods");
        il2cpp_method_get_name = (const char *(*)(const MethodInfo *)) shadowhook_dlsym(handle,
                                                                                        "il2cpp_method_get_name");
        il2cpp_string_chars = (Il2CppChar *(*)(const Il2CppString *)) shadowhook_dlsym(handle,
                                                                                       "il2cpp_string_chars");
        il2cpp_method_get_param_count = (uint32_t (*)(const MethodInfo *)) shadowhook_dlsym(handle,
                                                                                              "il2cpp_method_get_param_count");
        il2cpp_method_get_param = (const Il2CppType *(*)(const MethodInfo *, uint32_t)) shadowhook_dlsym(handle,
                                                                                              "il2cpp_method_get_param");
        il2cpp_class_from_il2cpp_type = (Il2CppClass *(*)(const Il2CppType *)) shadowhook_dlsym(handle,
                                                                                                  "il2cpp_class_from_il2cpp_type");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "Il2cpp-Manager", "Failed to open %s: %s", LIB_NAME,
                            dlerror());
        return;
    }

    il2cpp_assembly_get_image_hook::hook();
}