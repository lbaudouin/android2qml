package org.qtproject.test;


import android.util.Log;
import android.os.Bundle;


class MyJavaNatives
{
    public static native void callbackWithoutArguments();
    public static native void callbackWithBool(boolean b);
    public static native void callbackWithInt(int i);
    public static native void callbackWithString(String s);
    public static native void callbackWithStringArray(String[] s);
}

public class Test extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static Test m_instance;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        m_instance = this;
        super.onCreate(savedInstanceState);
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        m_instance = null;
    }

    static public void functionWithoutArguments(){
        Log.v("Test","functionWithoutArguments");
    }

    static public void functionWithBool(boolean b){
        Log.v("Test","functionWithBool: " + b);
    }

    static public void functionWithInt(int i){
        Log.v("Test","functionWithInt: " + i);
    }

    static public void functionWithString(String s){
        Log.v("Test","functionWithString: " + s);
    }

    static public boolean getBool(){
        return true;
    }

    static public int getInt(){
        return 11;
    }

    static public String getString(){
        return "test";
    }

    static public String intToString(int i){
        return String.valueOf(i);
    }

    static public void callbacks(){
        Log.v("Test","callbacks");
        MyJavaNatives.callbackWithoutArguments();
        MyJavaNatives.callbackWithBool(true);
        MyJavaNatives.callbackWithInt(5);
        MyJavaNatives.callbackWithString("test");

        String[] list = new String[3];
        list[0] = "Item 1";
        list[1] = "Item 2";
        list[2] = "Item 3";

        MyJavaNatives.callbackWithStringArray(list);
    }

}
