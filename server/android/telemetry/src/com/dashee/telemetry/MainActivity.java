package com.dashee.telemetry;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.WindowManager;
import java.util.Observable;
import java.util.Observer;

import com.dashee.telemetry.models.*;

public class MainActivity 
    extends Activity
    implements Observer
{
    ModelPhonePosition modelPhonePosition;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        // Keep our screen constantly on
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setContentView(R.layout.main);

        this.modelPhonePosition = new ModelPhonePosition(getBaseContext());
    }

    /**
     * Set our top menue
     * 
     * @param menu - The Menu object
     *
     * @return boolean - always true
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    /**
     *  Update our view and model. Given the phone's roll
     *  we update our server/model using our thread and we also
     *  update the HUD rotational value
     *  
     *  @param o - The observer handler
     *  @param arg - The arguments to the Observer
     */
    public void update(Observable o, Object arg)
    {
        try
        {
            if (o instanceof ModelPhonePosition)
            {
                ModelPhonePosition position = (ModelPhonePosition)o;
                //this.modelVehicle.setFromPhonePosition(position);
                //fragmentHud.setPosition((ModelVehicleCar) this.modelVehicle);
                //fragmentHud.setHudConnection(position.getPitch()+"");
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
}
