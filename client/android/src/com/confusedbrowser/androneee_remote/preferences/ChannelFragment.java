package com.confusedbrowser.androneee_remote.preferences;

import android.app.ActionBar;
import android.os.Bundle;
import android.preference.PreferenceFragment;
import com.confusedbrowser.androneee_remote.R;
 
/**
 * This will handle our Preference object
 * 
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class ChannelFragment 
	extends PreferenceFragment
{
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.channels);

        ActionBar ab = getActivity().getActionBar();
        ab.setSubtitle(R.string.pref_channel_subtitle);
    }
}
