#include <jni.h>
#include <string>
#include <android/log.h>

#include "il2cpp_manager.h"

#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, "UnityIl2cppTranslator", __VA_ARGS__)

extern "C" JNIEXPORT void JNICALL
Java_com_example_unity_1il2cpp_1translator_UnityIl2cppTranslator_init(
        JNIEnv* env,
        jclass /* this */) {
    std::string hello = "Hello from C++";
    LOGD("UnityIl2cppTranslator", "%s", hello.c_str());

    // Initialize the il2cpp manager
    il2cpp_manager_init();
}