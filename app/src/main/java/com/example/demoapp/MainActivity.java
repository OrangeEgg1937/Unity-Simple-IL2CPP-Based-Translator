package com.example.demoapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.example.unity_il2cpp_translator.UnityIl2cppTranslator;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        UnityIl2cppTranslator.loadLibraryFromInternalStorage(this);
    }
}