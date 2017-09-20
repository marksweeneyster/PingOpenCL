package org.oedteq.pingopencl;

import android.support.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertFalse;

@RunWith(AndroidJUnit4.class)
public class LoadOpenCLTest {
    @Test
    public void loadOpenCL() throws Exception {
        // Context of the app under test.
        String failPrefix = "PingOpenCL: load OpenCL FAIL";

        String loadString = PingOpenCL.stringFromJNI();

        assertFalse(loadString.startsWith(failPrefix));
    }

    static {
        System.loadLibrary("pingopencl-jni");
    }
}
