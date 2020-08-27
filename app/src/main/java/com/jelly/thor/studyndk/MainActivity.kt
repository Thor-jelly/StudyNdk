package com.jelly.thor.studyndk

import android.content.pm.PackageInfo
import android.content.pm.PackageManager
import android.content.pm.Signature
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.jelly.thor.studyndk.test1.SignatureUtils
import kotlinx.android.synthetic.main.activity_main.*


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //java方法获取签名，正式包才是正确的签名 切记
        /*var packageInfo: PackageInfo? = null
        try {
            packageInfo =
                packageManager.getPackageInfo(packageName, PackageManager.GET_SIGNATURES)
        } catch (e: PackageManager.NameNotFoundException) {
            e.printStackTrace()
        }
        val signatures: Array<Signature> = packageInfo!!.signatures
        Log.e("123===", signatures[0].toCharsString())*/

        SignatureUtils.signatureVerify(this)

        val nameStr = "userName=wdd&userPwd=123456"
        val signatureParams = SignatureUtils.signatureParams(nameStr)
        Log.e("123===", "signatureParams=${signatureParams}")
        sample_text.text = signatureParams
    }
}
