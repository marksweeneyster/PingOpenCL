package org.oedteq.pingopencl;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class PingOpenCL extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView)findViewById(R.id.pingopencl_textview);
        tv.setText( stringFromJNI() );
    }

    public native String  stringFromJNI();

    static {
        System.loadLibrary("pingopencl-jni");
    }
}
