package com.jelly.thor.studyndk

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.jelly.thor.studyndk.test1.SignatureUtils
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        val nameStr = "userName=wdd&userPwd=123456"
        val signatureParams = SignatureUtils.signatureParams(nameStr)
        sample_text.text = signatureParams
    }
}
