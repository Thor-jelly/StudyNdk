package com.jelly.thor.studyndk.test1

/**
 * 类描述：请求参数加密<br></br>
 * 创建人：吴冬冬<br></br>
 * 创建时间：2020/8/26 15:28 <br></br>
 */
object SignatureUtils {
    // Used to load the 'native-lib' library on application startup.
    init {
        System.loadLibrary("native-lib")
    }

    /**
     * native 方法签名参数
     */
    external fun signatureParams(params: String): String
}