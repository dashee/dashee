package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;
 
/**
 * This will handle our Preference object
 * 
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class Preferences extends PreferenceActivity {
	
        @Override
        protected void onCreate(Bundle savedInstanceState) 
        {
                super.onCreate(savedInstanceState);
                getFragmentManager().beginTransaction().replace(android.R.id.content, new MyPreferenceFragment()).commit();
        }
        
        public static class MyPreferenceFragment extends PreferenceFragment
        {
            @Override
            public void onCreate(final Bundle savedInstanceState)
            {
                super.onCreate(savedInstanceState);
                addPreferencesFromResource(R.xml.preferences);
            }
        }
}