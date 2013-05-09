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

    protected void onDraw(Canvas canvas)
    {
        super.onDraw(canvas);
        // Upper Colour: #00CC99
        Paint upper = new Paint();
        upper.setColor(0x00CC99);
        upper.setAlpha(255);
        upper.setStrokeWidth(3.0f);
        upper.setStyle(Paint.Style.FILL);
        
        // Lower Colour: #CC6633
        Paint lower = new Paint();
        lower.setColor(0xCC6633);
        lower.setAlpha(255);
        lower.setStrokeWidth(3.0f);
        lower.setStyle(Paint.Style.FILL);
        //WindowManager mWinMgr = (WindowManager)context.getSystemService(Context.WINDOW_SERVICE);
        int displayWidth = 30;
        int displayHeight = 30;
        int circleRadius = 100;
        int sqWidth = (int) ((int) ( Math.sqrt((Math.pow(canvas.getWidth()/2,2) + Math.pow(canvas.getHeight()/2,2)))));
        canvas.translate( (canvas.getWidth()-(2*sqWidth))/2, (canvas.getHeight()-(2*sqWidth))/2); 
        canvas.drawRect(0, 0, sqWidth*2, sqWidth, upper);
        canvas.drawRect(0, sqWidth, 2*sqWidth, 2*sqWidth, lower);
        invalidate();
    }

}