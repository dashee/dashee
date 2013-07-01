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
import android.util.Log;

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

    /**
     * Run the creation of our PreferenceActivity.
     *
     * @param savedInstanceState - The state of the running activity
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
    	
        addPreferencesFromResource(R.xml.preferences);
        
        ActionBar ab = getActionBar();
        ab.setSubtitle(R.string.subtitle_activity_preferences);
        ab.setDisplayHomeAsUpEnabled(true);

        SharedPreferences sharedPreferences = getPreferenceScreen().getSharedPreferences();
        sharedPreferences.registerOnSharedPreferenceChangeListener(this); 
        
        // This will ensure that previous settings are loaded, rather
        // than the default one's.
        this.setSharedPreferenceState(sharedPreferences);
    }

    /**
     * Set default values. from previous state
     *
     * @param sharedPreferences - The shared pref object
     */
    public void setSharedPreferenceState(SharedPreferences pref)
    {
        EditTextPreference Ip = (EditTextPreference)findPreference("pref_server_ip");
        Ip.setSummary(pref.getString("pref_server_ip", "192.168.1.11"));
        
        EditTextPreference Port = (EditTextPreference)findPreference("pref_server_port");
        Port.setSummary(pref.getString("pref_server_port", "2047"));
    }

    /**
     * Listener for when an option is changed.
     *
     * @param sharedPreference - The preference object
     * @param key - The preference changed
     */
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) 
    {
        Preference pref = findPreference(key);

        if (pref instanceof EditTextPreference) 
        {
            EditTextPreference etp = (EditTextPreference) pref;
            pref.setSummary(etp.getText());
        }

        Log.e("Dashee", "PreferenceActivity: Hello");
    }

    /**
     * Handler of the Action bar selected Option
     *
     * @param item - The item clicked
     *
     * @return boolean - true if selected other wise see parent
     */
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

    /**
     * Resume operations
     */
    public void onResume()
    {
        super.onResume();

        getPreferenceScreen()
            .getSharedPreferences()
            .registerOnSharedPreferenceChangeListener(this);
    }   

    /**
     * Pause operations
     */
    public void onPause()
    {
        super.onPause();
        getPreferenceScreen()
            .getSharedPreferences()
            .unregisterOnSharedPreferenceChangeListener(this);
    }
}
