package com.confusedbrowser.androneee_remote;

import android.app.ActionBar;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.EditTextPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceFragment;
import android.view.MenuItem;
 
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
        
        ActionBar ab = getActionBar();
        ab.setSubtitle(R.string.subtitle_activity_preferences);
        ab.setDisplayHomeAsUpEnabled(true);

        getFragmentManager()
            .beginTransaction()
            .replace(android.R.id.content, new PreferencesFragment())
            .commit();
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
                finish();
                return true;
        }

        return super.onOptionsItemSelected(item);
    }
    
    public static class PreferencesFragment extends PreferenceFragment implements OnSharedPreferenceChangeListener
    {
        @Override
        public void onCreate(final Bundle savedInstanceState)
        {
            super.onCreate(savedInstanceState);
            addPreferencesFromResource(R.xml.preferences);
            
            SharedPreferences sharedPref = getPreferenceScreen().getSharedPreferences();
            sharedPref.registerOnSharedPreferenceChangeListener(this);
            // This will ensure that previous settings are loaded, rather
            // than the default one's.
            this.setSharedPreferenceState(sharedPref);
        }

		private void setSharedPreferenceState(SharedPreferences sharedPref) {
			// TODO Auto-generated method stub
			EditTextPreference Ip = (EditTextPreference)findPreference("pref_server_ip");
	        Ip.setSummary(sharedPref.getString("pref_server_ip", "192.168.1.11"));
	        
	        EditTextPreference Port = (EditTextPreference)findPreference("pref_server_port");
	        Port.setSummary(sharedPref.getString("pref_server_port", "2047"));
		}

		@Override
		public void onSharedPreferenceChanged(
				SharedPreferences sharedPreferences, String key) {
			Preference pref = findPreference(key);

	        if (pref instanceof EditTextPreference) 
	        {
	            EditTextPreference etp = (EditTextPreference) pref;
	            pref.setSummary(etp.getText());
	        }
			
		}
    }
}
