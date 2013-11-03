package com.confusedbrowser.androneee_remote.preferences;

import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.Preference;
import android.preference.PreferenceScreen;
import android.preference.PreferenceFragment;
import android.util.Log;

import com.confusedbrowser.androneee_remote.R;
import com.confusedbrowser.androneee_remote.models.ModelServerState;

import java.util.List;
import java.util.Map;

/**
 * This will handle our Preference object
 * 
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class MainFragment 
    extends PreferenceFragment 
    implements OnSharedPreferenceChangeListener
{
    SharedPreferences sharedPref;
    List<String> summaryToValue = java.util.Arrays.asList("pref_server_ip", "pref_server_port",
        "pref_channel01_trim", "pref_channel02_trim", "pref_channel01_max",
        "pref_channel02_max", "pref_channel02_max", "pref_channel01_min", "pref_channel02_min");

    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.preferences);
            
        this.sharedPref = getPreferenceScreen().getSharedPreferences();
        sharedPref.registerOnSharedPreferenceChangeListener(this);
        
        Log.d("Dashee", "Init main setting fragment");
        this.setSharedPreferenceState(sharedPref);
    }

   // @Override
    public boolean onPreferenceTreeClick(PreferenceScreen prefScreen, Preference pref) 
    {

        /*if (pref.getKey().contains("pref_channel")) 
        {
            //Display the fragment as the main content.
        	Intent channelSettingsActivity = new Intent(getActivity(), ChannelActivity.class);
        	startActivity(channelSettingsActivity);
        	return true;
        }*/
        
        return super.onPreferenceTreeClick(prefScreen, pref);
    }
    
    /**
     * Set the Value of shared preferences given the last state.
     *
     * @param sharedPref - The sharedPref Object
     */
    private void setSharedPreferenceState(SharedPreferences sharedPref) 
    {
        Map<String,?> values = sharedPref.getAll();
        for (Map.Entry<String, ?> entry : values.entrySet())
        {
            ///Log.d("Dashee", "init setting " + entry.getKey());
            if(summaryToValue.contains(entry.getKey()))
                findPreference(entry.getKey()).setSummary(sharedPref.getString(entry.getKey(), "0"));
        }
    }

    /**
     * Change the value of the Textbox
     *
     * @param sharedPreferences - The SharedPreference object
     * @param key - The preference changed
     */
    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key)
    {
        Preference pref = findPreference(key);
        if (pref instanceof EditTextPreference) 
        {
            EditTextPreference etp = (EditTextPreference) pref;

            if (
                    key.contentEquals("pref_channel01_min") ||
                    key.contentEquals("pref_channel01_max") ||
                    key.contentEquals("pref_channel02_min") ||
                    key.contentEquals("pref_channel02_max") ||
                    key.contentEquals("pref_channel03_min") ||
                    key.contentEquals("pref_channel03_max")
            )
            {
                float val = Float.parseFloat(etp.getText());

                // Invalid value so break out of any following tasks
                if (val < 0.0f || val > 255.0f)
                    return;
            }

            pref.setSummary(etp.getText());
        }
    }
}
