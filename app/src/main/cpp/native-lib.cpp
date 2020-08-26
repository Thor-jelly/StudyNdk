#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_jelly_thor_studyndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jelly_thor_studyndk_test1_SignatureUtils_signatureParams(JNIEnv *env, jclass clazz,
                                                                  jstring params) {
    std::string hello = "签名成功！";
    return env->NewStringUTF(hello.c_str());
}