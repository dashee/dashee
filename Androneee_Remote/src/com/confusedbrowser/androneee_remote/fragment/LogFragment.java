package com.confusedbrowser.androneee_remote.fragment;

import com.confusedbrowser.androneee_remote.R;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.view.View;
import android.support.v4.app.Fragment;

public class LogFragment extends Fragment {
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

		return inflater.inflate(R.layout.fragment_log, container, false);
        /*TextView textview = new TextView(this);
        textview.setText("This is the Artists tab");
        setContentView(textview);*/
    }
}