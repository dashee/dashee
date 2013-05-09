package com.confusedbrowser.androneee_remote;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;

public class DrawHud extends View
{
    Context context;

    public DrawHud(Context mContext)
    {
        super(mContext);
        context = mContext;
    }
    
    /*
     * This function will draw our artificial horizon, which works at an oposing angle
     * to that of the phone. The rotation is handeled outside, but this function deals with
     * drawing our horizon boxes just big enough so there are no white spaces
     */
    protected void onDraw(Canvas canvas)
    {
        super.onDraw(canvas);

        // Upper Colour: #00CC99
        Paint upper = new Paint();
        upper.setColor(0x00CC99);
        upper.setAlpha(255);
        upper.setStrokeWidth(3.0f);
        upper.setStyle(Paint.Style.FILL);
        upper.setAntiAlias(true);
        
        // Lower Colour: #CC6633
        Paint lower = new Paint();
        lower.setColor(0xCC6633);
        lower.setAlpha(255);
        lower.setStrokeWidth(3.0f);
        lower.setStyle(Paint.Style.FILL);
        lower.setAntiAlias(true);

        // Our box's half width must be equal to exactly the width from the center of the screen to
        // a corner. Let this value be C, and given pythagoras theorm (C^2=A^2+B^2) we can calculate C where A = screenWidth/2 
        // and B = screenHeight / 2. The reason we divide by 2 is because the center point to the edge, is half the screen[Width/Height]
        int sqWidth = (int) ((int) ( Math.sqrt((Math.pow(canvas.getWidth()/2,2) + Math.pow(canvas.getHeight()/2,2)))));
    
        // This will translate our given canvas to be center of our bigger square, so we can draw the 
        // Rectangles using 0,0 as starting point
        canvas.translate( (canvas.getWidth()-(2*sqWidth))/2, (canvas.getHeight()-(2*sqWidth))/2); 
        
        // Draw our sky
        canvas.drawRect(0, 0, sqWidth*2, sqWidth, upper);

        // Draw our ground
        canvas.drawRect(0, sqWidth, 2*sqWidth, 2*sqWidth, lower);

        invalidate();
    }
}
