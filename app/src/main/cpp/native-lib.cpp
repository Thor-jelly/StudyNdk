#include <jni.h>
#include <string>
#include <android/log.h>
#include "md5.h"

//额外附加的字符串
static char *EXTRA_SIGNATURE = "THOR_JELLY";
//校验签名
static int is_verify = 0;
static char *PACKAGE_NAME = "com.jelly.thor.studyndk";
/////切记这里用这是包生成的签名
static char *APP_SIGNATURE = "308202e2308201ca020101300d06092a864886f70d010105050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b3009060355040613025553301e170d3139313033303037343830335a170d3439313032323037343830335a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330820122300d06092a864886f70d01010105000382010f003082010a02820101008d4743120331756ad5ac66e3e12d0b247572a718f43e58c3c8c56c6d3fdb27c5c1f77abff243db147dcc46ef87c6aa3f79f20e6c659ae1945490ed9485c2df139456c8ac8265d74abca63e4b8fb910f29b3b5e4625d79897ad709dc7bcd995da3631396d242d75c86a6bdb094a6db1f0b9e5d2a01b2be43f0a3ea0889268f0fec75c68cf0762a4f7a09a79b2979fe8503608d6ebabb19ceca07a07f525064101d695a792359fc475f43a43d1d9b2810878b5f5288673a689284633c5367f6fae2bdb8c54e2f6932b0fac9b36b394a611b5aa65f138ffd6dd9dc9d445f12bfa9416641b2794217c61bbc6bffed1346fd098a924f461929419645194f5b2adcc790203010001300d06092a864886f70d01010505000382010100392767fe8666ad7522f272e534e3aa9a844ed574049374d62e17872c9b1d3e88d7bfe3a3c17e76dc875552d9659e6622710511e9db52f58df3d31b88480e16f5285f41e73fc75e164039c790f56d6916071daa499d71140130f8172bd20567002eaf5247192faf48e4449b4d9c88c147b697be53902fdeac69bef23e8bea7726a8e4d990804d5ac251e4c8c11205702654945e1d9c5cca58b287f3396e599e3308665dbcf6641227b1a40aba718b48141c5517066a030678ebf610eb58b3acd45a25a8eddbd8ab36b72db804554fd68bac9dbff36db548e174ecb164dd061de0f1eea847a41967115ab8eaa13bf94453c8f20de83adfd23671a4ac9505f28025";

extern "C" JNIEXPORT jstring JNICALL
Java_com_jelly_thor_studyndk_test1_SignatureUtils_signatureParams(JNIEnv *env, jobject type,
                                                                  jstring params_) {
    const char *params = env->GetStringUTFChars(params_, 0);
    if (is_verify == 0) {
        return env->NewStringUTF("error_signature");
    }

    // MD5 签名规则，加点料
    // 1. 字符串前面加点料
    std::string signature_str(params);
    signature_str.insert(0, EXTRA_SIGNATURE);
    // 2. 后面去掉两位
    signature_str = signature_str.substr(0, signature_str.length() - 2);
    __android_log_print(ANDROID_LOG_ERROR, "123===", "加密前文本: %s", signature_str.c_str());

    // 3. md5 去加密 C++ 和 Java 是一样的，唯一不同就是需要自己回收内存
    auto *ctx = new MD5_CTX();
    MD5Init(ctx);
    MD5Update(ctx, (unsigned char *) signature_str.c_str(), signature_str.length());
    unsigned char digest[16] = {0};
    MD5Final(digest, ctx);
    __android_log_print(ANDROID_LOG_ERROR, "123===", "加密后文本: %s", digest);

    // 生成 32 位的字符串
    char md5_str[34];
    for (int i = 0; i < 16; i++) {
        // 不足的情况下补0 f = 0f, ab = ab
        sprintf(md5_str, "%s%02x", md5_str, digest[i]);
    }
    __android_log_print(ANDROID_LOG_ERROR, "123===", "加密文本: %s", md5_str);

    // 释放资源
    env->ReleaseStringUTFChars(params_, params);
    return env->NewStringUTF(md5_str);
}

/**
   var packageInfo: PackageInfo? = null
   try {
       packageInfo =
           packageManager.getPackageInfo(packageName, PackageManager.GET_SIGNATURES)
   } catch (e: PackageManager.NameNotFoundException) {
       e.printStackTrace()
   }
   val signatures: Array<Signature> = packageInfo!!.signatures
 */
extern "C" JNIEXPORT void JNICALL
Java_com_jelly_thor_studyndk_test1_SignatureUtils_signatureVerify(JNIEnv *env, jobject thiz,
                                                                  jobject context) {
    //c调用java代码
    // 1. 获取包名
    jclass j_clz = env->GetObjectClass(context);
    jmethodID j_mid = env->GetMethodID(j_clz, "getPackageName", "()Ljava/lang/String;");//()代表调用的是无参构造方法，后面代表返回值
    jstring j_package_name = (jstring) env->CallObjectMethod(context, j_mid);
    // 2 . 比对包名是否一样
    const char *c_package_name = env->GetStringUTFChars(j_package_name, NULL);
    if (strcmp(c_package_name, PACKAGE_NAME) != 0) {
        return;
    }
    // 3. 获取签名
    // 3.1 获取 PackageManager
    j_mid = env->GetMethodID(j_clz, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject pack_manager = env->CallObjectMethod(context, j_mid);
    // 3.2 获取 PackageInfo
    j_clz = env->GetObjectClass(pack_manager);
    j_mid = env->GetMethodID(j_clz, "getPackageInfo",
                             "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject package_info = env->CallObjectMethod(pack_manager, j_mid, j_package_name, 0x00000040);
    // 3.3 获取 signatures 数组
    j_clz = env->GetObjectClass(package_info);
    jfieldID j_fid = env->GetFieldID(j_clz, "signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signatures = (jobjectArray) env->GetObjectField(package_info, j_fid);
    // 3.4 获取 signatures[0]
    jobject signatures_first = env->GetObjectArrayElement(signatures, 0);
    // 3.5 调用 signatures[0].toCharsString();
    j_clz = env->GetObjectClass(signatures_first);
    j_mid = env->GetMethodID(j_clz, "toCharsString", "()Ljava/lang/String;");
    jstring j_signature_str = (jstring) env->CallObjectMethod(signatures_first, j_mid);
    const char *c_signature_str = env->GetStringUTFChars(j_signature_str, NULL);
    // 4. 比对签名是否一样
    if (strcmp(c_signature_str, APP_SIGNATURE) != 0) {
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, "JNI_TAG", "签名校验成功: %s", c_signature_str);
    // 签名认证成功
    is_verify = 1;
}