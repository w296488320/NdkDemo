package com.lyh.nkddemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    public String name ="zhen xi";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    int[] source=new int[]{4,3,2,1};

    public String getName(){
      return "1234";
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        String str="";
        getArray(source);
        for(int a:source){str+=a+"";};
        //  tv.setText(stringFromJNI());
        //C函数更新java字段数据
        //tv.setText(upDateName());
        //C函数调用java方法
        //  tv.setText(getMethod());
        //C函数调用数组方法
        tv.setText(str);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String upDateName();
    public native String getMethod();
    public native void getArray(int[] array);
    public native void getlocalReference();

}
