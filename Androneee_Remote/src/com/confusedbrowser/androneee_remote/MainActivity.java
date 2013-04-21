package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
import android.view.View;
import android.app.Activity;
import android.view.Menu;
import android.content.Intent;
import android.widget.EditText;
import android.util.Log;
import android.widget.TextView;

import java.io.*;
import java.net.*;

public class MainActivity extends Activity {
	
	public final static String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";
	InetAddress serverAddr;
	UDP_thread connection;
	TextView t;
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        connection = new UDP_thread(this, "54.246.151.139", 2047);
        connection.start();

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
