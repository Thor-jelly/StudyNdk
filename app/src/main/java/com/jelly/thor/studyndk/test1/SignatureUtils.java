package com.jelly.thor.studyndk.test1;

/**
 * 类描述：请求参数加密<br/>
 * 创建人：吴冬冬<br/>
 * 创建时间：2020/8/26 15:28 <br/>
 */
public class SignatureUtils {
    /**
     * native 方法签名参数
     */
    public static native String signatureParams(String params);
}
