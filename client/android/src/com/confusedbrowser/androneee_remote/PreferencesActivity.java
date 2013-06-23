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
public class PreferencesActivity extends PreferenceActivity {
	
    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        getFragmentManager()
            .beginTransaction()
            .replace(android.R.id.content, new PreferencesFragment())
            .commit();
    }
    
    public static class PreferencesFragment extends PreferenceFragment
    {
        @Override
        public void onCreate(final Bundle savedInstanceState)
        {
            super.onCreate(savedInstanceState);
            addPreferencesFromResource(R.xml.preferences);
        }
    }
}
