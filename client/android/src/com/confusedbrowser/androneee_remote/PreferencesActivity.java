package com.confusedbrowser.androneee_remote;

import android.app.ActionBar;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;
import android.support.v4.app.NavUtils;
import android.view.MenuItem;

/**
 * This will handle our Preference object
 * 
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class PreferencesActivity 
    extends PreferenceActivity 
    implements OnSharedPreferenceChangeListener
{
    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
    	
        addPreferencesFromResource(R.xml.preferences);
        
        ActionBar ab = getActionBar();
        ab.setSubtitle(R.string.subtitle_activity_preferences);
        ab.setDisplayHomeAsUpEnabled(true);

        SharedPreferences sharedPref = getPreferenceScreen().getSharedPreferences();
        sharedPref.registerOnSharedPreferenceChangeListener(this); 
    }

    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) 
    {
        Preference pref = findPreference(key);

        if (pref instanceof EditTextPreference) 
        {
            EditTextPreference etp = (EditTextPreference) pref;
            pref.setSummary(etp.getText());
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) 
    {
        switch (item.getItemId()) 
        {
            //Respond to the action bar's Up/Home button
            case android.R.id.home:
                NavUtils.navigateUpFromSameTask(this);
                return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public void onResume()
    {
        super.onResume();

        getPreferenceScreen()
            .getSharedPreferences()
            .registerOnSharedPreferenceChangeListener(this);
    }   

    public void onPause()
    {
        super.onPause();
        getPreferenceScreen()
            .getSharedPreferences()
            .unregisterOnSharedPreferenceChangeListener(this);
    }
}
