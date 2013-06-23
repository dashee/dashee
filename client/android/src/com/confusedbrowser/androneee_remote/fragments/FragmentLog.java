package com.confusedbrowser.androneee_remote.fragments;

import com.confusedbrowser.androneee_remote.R;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.view.View;
import android.support.v4.app.Fragment;

/**
 * This class will handle updating our LogFragment
 * 
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class FragmentLog extends Fragment 
{
    /**
     * return our view, required by the parent
     */
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) 
    {
            return inflater.inflate(R.layout.fragment_log, container, false);
    }
}
