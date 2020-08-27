#include <jni.h>
#include <string>
#include "md5.h"

//额外附加的字符串
static char *EXTRA_SIGNATURE = "THOR_JELLY";

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jelly_thor_studyndk_test1_SignatureUtils_signatureParams(JNIEnv *env, jobject type,
                                                                  jstring params_) {
    const char *params = env->GetStringUTFChars(params_, 0);

    // MD5 签名规则，加点料
    // 1. 字符串前面加点料
    std::string signature_str(params);
    signature_str.insert(0, EXTRA_SIGNATURE);
    // 2. 后面去掉两位
    signature_str = signature_str.substr(0, signature_str.length() - 2);

    // 3. md5 去加密 C++ 和 Java 是一样的，唯一不同就是需要自己回收内存
    MD5_CTX *ctx = new MD5_CTX();
    MD5Init(ctx);
    MD5Update(ctx, (unsigned char *) signature_str.c_str(), signature_str.length());
    unsigned char digest[16] = {0};
    MD5Final(digest, ctx);

    // 生成 32 位的字符串
    char md5_str[34];
    for (int i = 0; i < 16; i++) {
        // 不足的情况下补0 f = 0f, ab = ab
        sprintf(md5_str, "%s%02x", md5_str, digest[i]);
    }

    // 释放资源
    env->ReleaseStringUTFChars(params_, params);
    return env->NewStringUTF(md5_str);
    //return env->NewStringUTF((const char *)digest);
//    const char *bytes = reinterpret_cast<const char *>(digest);
//    return env->NewStringUTF(bytes);
}