package com.confusedbrowser.androneee_remote;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.*;
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
        upper.setColor(0xFFFFFF);
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
        //canvas.translate( (canvas.getWidth()/2-(sqWidth)), (canvas.getHeight()/2-(sqWidth)));
        
        // Draw our sky
        //canvas.drawRect(0, 0, sqWidth*2, sqWidth, upper);

        // Draw our ground
        //canvas.drawRect(0, sqWidth, 2*sqWidth, 2*sqWidth, lower);
        //

        float radius = (canvas.getWidth() * 0.66f) / 2.0f;
        float sweepAngle = 8.0f;
        float startAngle = -30.0f;

        float p1x = canvas.getWidth()/2 - radius;
        float p1y = canvas.getHeight()/2 - radius;
        float p2x = canvas.getWidth()/2 + radius;
        float p2y = canvas.getHeight()/2 + radius;
        
        final RectF oval1 = new RectF();
        final RectF oval2 = new RectF();
        oval1.set(p1x, p1y, p2x, p2y);
        oval2.set(p1x-100, p1y-100, p2x+100, p2y+100);
        //oval2.set(p1x+100, p1y, p2x+100, p2y);
        //
        //

        Path path = new Path();
        path.addRect(10, 10, 600, 200, Path.Direction.CW);

        //canvas.clipRect(oval1, Region.Op.DIFFERENCE);

   //     canvas.drawRect(10, 10, 300, 75, upper);
    //    canvas
        
        Path path2 = new Path();
        path2.arcTo(oval1, 0.0f, 300);
        canvas.clipPath(path);
        canvas.clipPath(path2, Region.Op.DIFFERENCE);
        
        /*
        float radiusDiff = 100/radius;
        float sweepAngleDecrease = sweepAngle - (sweepAngle * radiusDiff);
        path.arcTo(oval2, startAngle, -(float) sweepAngleDecrease, true);
        path.arcTo(oval2, startAngle+10, -sweepAngleDecrease, true);
        path.arcTo(oval2, startAngle+20, -sweepAngleDecrease, true);
        path.arcTo(oval2, startAngle+30, -sweepAngleDecrease, true);
        path.arcTo(oval2, startAngle+40, -sweepAngleDecrease, true);
        path.arcTo(oval2, startAngle+50, -sweepAngleDecrease, true);
        path.arcTo(oval2, startAngle+60, -sweepAngleDecrease, true);
        path.arcTo(oval2, startAngle+70, -sweepAngleDecrease, true);
        */

        //canvas.drawPath(path, upper);
        canvas.drawPath(path, upper);

        invalidate();
    }
}
