package com.confusedbrowser.androneee_remote;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.View;

public class DrawHud extends View
{
    Context context;
    
    Paint upper;
    Paint lower;

    /**
     * Set our paint colours, for use with the Draw functions
     * 
     * @param Context mContext - The context required by super
     */
    public DrawHud(Context mContext)
    {
        super(mContext);
        context = mContext;
        
        // Upper Colour: #00CC99
        upper = new Paint();
        upper.setColor(0x0A0A0A);
        upper.setAlpha(255);
        upper.setStrokeWidth(3.0f);
        upper.setStyle(Paint.Style.FILL);
        upper.setAntiAlias(true);
        
    }
    
    /**
     * This function will draw our artificial horizon, which works at an opposing angle
     * to that of the phone. The rotation is handled outside, but this function deals with
     * drawing our horizon boxes just big enough so there are no white spaces
     * 
     * @param Canvas canvas - The canvas object to draw on.
     */
    protected void onDraw(Canvas canvas)
    {
        super.onDraw(canvas);

        // Our box's half width must be equal to exactly the width from the centre of the screen to
        // a corner. Let this value be C, and given pythagoras theorem (C^2=A^2+B^2) we can calculate C where A = screenWidth/2 
        // and B = screenHeight / 2. The reason we divide by 2 is because the centre point to the edge, is half the screen[Width/Height]
        int sqWidth = (int) ((int) ( Math.sqrt((Math.pow(canvas.getWidth()/2,2) + Math.pow(canvas.getHeight()/2,2)))));
    
        // Centre square use screen height / width over 2 and then move back 1/2 the square width (sqWidth) 
        canvas.translate( (canvas.getWidth()/2-(sqWidth)), (canvas.getHeight()/2-(sqWidth)));
        
        // Draw our sky
        //canvas.drawRect(0, 0, sqWidth*2, sqWidth, upper);

        // Draw our ground
        //canvas.drawRect(0, sqWidth, 2*sqWidth, 2*sqWidth, lower);

        invalidate();
    }
}
