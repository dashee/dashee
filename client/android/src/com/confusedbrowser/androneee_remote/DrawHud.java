package com.confusedbrowser.androneee_remote;

import android.app.Activity;
import android.content.Context;
import android.graphics.*;
import android.graphics.PorterDuff.Mode;
import android.util.Log;
import android.view.View;
import android.view.Window;

public class DrawHud extends View
{
    Context context;
    

    
    Path steerPath = new Path();
    Path[] powerPaths = new Path[12];
    Path[] batteryPaths = new Path[12];
    float steerArcRadius;
    final RectF steerOval = new RectF();
    
    
    
    float centerX = 0.0f;
    float centerY = 0.0f;
    
    final RectF oval2 = new RectF();
    float tilt = 50.0f;
    float powerPerc = 0.0f;
    
    Paint steerLine;
    Paint steerLineLock;
    Paint activePowerBar;
    Paint inactivePowerBar;
    Paint activeBatteryBar;
    int lineColor = 0x333333;
    int lockColor = 0xD93600;
    int activeBarColor = 0xD96D00;
    int inactiveBarColor = 0x20202F;
    int activeBattery = 0xEEEEEE;

    /**
     * Set our paint colours, for use with the Draw functions
     * 
     * @param Context mContext - The context required by super
     */
    public DrawHud(Context mContext)
    {
        super(mContext);
        context = mContext;
      
        steerLine = new Paint();
        steerLine.setAntiAlias(true);
        steerLine.setColor(lineColor);
        steerLine.setAlpha(255);
        steerLine.setStrokeWidth(4.0f);
        steerLine.setStyle(Paint.Style.STROKE);
        
        steerLineLock = new Paint();
        steerLineLock.setAntiAlias(true);
        steerLineLock.setColor(lockColor);
        steerLineLock.setAlpha(255);
        steerLineLock.setStrokeWidth(4.0f);
        steerLineLock.setStyle(Paint.Style.STROKE);
        
        activePowerBar = new Paint();
        activePowerBar.setAntiAlias(true);
        activePowerBar.setColor(activeBarColor);
        activePowerBar.setAlpha(255);
        activePowerBar.setStyle(Paint.Style.FILL);
        
        inactivePowerBar = new Paint();
        inactivePowerBar.setAntiAlias(true);
        inactivePowerBar.setColor(inactiveBarColor);
        inactivePowerBar.setAlpha(255);
        inactivePowerBar.setStyle(Paint.Style.FILL);
        
        activeBatteryBar = new Paint();
        activeBatteryBar.setAntiAlias(true);
        activeBatteryBar.setColor(activeBattery);
        activeBatteryBar.setAlpha(255);
        activeBatteryBar.setStyle(Paint.Style.FILL);
        
    }
    
    /**
     * Implementing this function gives access to the canvas width and height meaning
     * those calculation can be done as required (usually just once), instead of doing them
     * constantly in the draw.
     */
    protected void onSizeChanged (int w, int h, int oldw, int oldh){
    	this.centerX = w/2;
    	this.centerY = h/2;
    	this.buildSteerPath(w, h);
    	this.addGaugePath(w, h, this.powerPaths, true);
    	this.addGaugePath(w, h, this.batteryPaths, false);
    }
    
    /*
     * Put together the arc that is to rotate on steer.
     */
    private void buildSteerPath(int w, int h){
    	if (w == 0 || h==0) return;
    	steerArcRadius = (h - h*0.08f) / 2.0f;
    	// No thought in angles below simply played around till it
    	// looked ok.
    	float steerArcSweepAngle = 280.0f;
        float steerArcStartAngle = -180.0f;

        float p1x = (w/2) - steerArcRadius;
        float p1y = (h/2) - steerArcRadius;
        float p2x = (w/2) + steerArcRadius;
        float p2y = (h/2) + steerArcRadius;
        
        this.steerOval.set(p1x, p1y, p2x, p2y);
        this.steerPath.arcTo(this.steerOval, steerArcStartAngle, -steerArcSweepAngle, true);
    }
    
    /*
     * Put together the arc that is to rotate on steer.
     */
    private void addGaugePath(int w, int h, Path[] paths, boolean leftHandSide){
    	if (w == 0 || h==0) return;
    	final RectF innerOval = new RectF();
        final RectF outerOval = new RectF();
    	float innerRadius = steerArcRadius + steerArcRadius*0.16f;
    	float outerRadius = steerArcRadius + steerArcRadius*0.38f;
    	
    	//Log.d("dashee", "percHieght: "+h*0.1);
    	double curY = h-Math.round(h*0.1);
    	//Log.d("dashee", "rectSize: "+h*0.053);//38.0
    	double rectHeight = Math.round(h*0.053);
    	//Log.d("dashee", "gap: "+ Math.round(h*0.015));//11
    	double gap =   Math.round(h*0.015);
    	
    	float p1x = (w/2) - innerRadius;
        float p1y = (h/2) - innerRadius;
        float p2x = (w/2) + innerRadius;
        float p2y = (h/2) + innerRadius;
        
        float outerP1x = (w/2) - outerRadius;
        float outerP1y = (h/2) - outerRadius;
        float outerP2x = (w/2) + outerRadius;
        float outerP2y = (h/2) + outerRadius;
        
        innerOval.set(p1x, p1y, p2x, p2y);
        outerOval.set(outerP1x, outerP1y, outerP2x, outerP2y);
    	
        int count  = 0;
        
    	while(count <=11){
    		
	        float[] innerArcParams = this.getArcParams(curY, curY-rectHeight, innerRadius, false, leftHandSide);
	        float[] outerArcParams = this.getArcParams(curY, curY-rectHeight, outerRadius, true, leftHandSide);
	        
	        paths[count] = new Path();
	        paths[count].arcTo(innerOval, innerArcParams[0], -innerArcParams[1], true);
	        paths[count].lineTo(outerArcParams[2], (float) (curY-rectHeight));
	        paths[count].arcTo(outerOval, outerArcParams[0], -outerArcParams[1], true);
	        paths[count].lineTo(innerArcParams[2], (float) (curY));
	        
	        curY = curY-rectHeight-gap;
	        count++;
        }
    }
    
    public float[] getArcParams(double startY, double endY, float radius, boolean reverse, boolean leftHandSide){
    	double startXCoor[] = getCircleX(startY, radius);
    	double endXCoor[] = getCircleX(endY, radius);
    	
    	int xcoordinateSide = (leftHandSide) ? 0 : 1;
    	
    	/*Log.d("dashee", "curY: "+startY);
    	Log.d("dashee", "x: "+startXCoor);
    	Log.d("dashee", "Recommended angle: "+this.getAngle((float) startXCoor, (float) startY));*/
        
    	float startAngle = (float) this.getAngle((float) startXCoor[xcoordinateSide], (float) startY);
        float endAngle = (float) this.getAngle((float) endXCoor[xcoordinateSide], (float) (endY));
        float sweepAngle = startAngle - endAngle;
        float[] returnArray = {startAngle, sweepAngle, (float) startXCoor[xcoordinateSide]};
        if(reverse){
        	returnArray[0] = endAngle;
        	returnArray[1] = -sweepAngle;
        	returnArray[2] = (float) endXCoor[xcoordinateSide];
        }
        return returnArray;
    }
    
    public void onScreenStateChanged (int screenState){
    	invalidate();
    }
    
    public double[] getCircleX(double y, double r)
    {
        double x = Math.sqrt(Math.abs(Math.pow(r, 2) - Math.pow(y-this.centerY, 2))); 
        //Log.d("dashee", "x1: "+Math.abs(x-this.centerX)+ " x2: "+Math.abs(-x-this.centerX));
        double[] returnArray = {Math.abs(x-this.centerX), Math.abs(-x-this.centerX)};
        return returnArray;
    }
   
   
   public double getAngle(float x, float y)
   {
       double angle1 = Math.atan2(this.centerY - this.centerY, this.centerX - (this.centerX + 10));
       double angle2 = Math.atan2(this.centerY - y, this.centerX - x);
       return -Math.toDegrees(angle1-angle2);
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
        //super.onDraw(canvas);
        
        //Always clear the canvas, seems needed if you switch off the display
        
        //Mid line right
        canvas.drawLine(this.centerX+this.steerArcRadius-80, this.centerY, this.centerX+this.steerArcRadius, this.centerY, steerLine);
        
        //Mid line left
        canvas.drawLine(this.centerX-this.steerArcRadius+80, this.centerY, this.centerX-this.steerArcRadius, this.centerY, steerLine);

        canvas.save();
        canvas.rotate(this.tilt, this.centerX, this.centerY);
        if(Math.ceil(this.tilt) == 100 || Math.floor(this.tilt) == 0){
        	canvas.drawPath(this.steerPath, steerLineLock);
        }else{
        	canvas.drawPath(this.steerPath, steerLine);
        }
        canvas.restore();
        
        int count  = 0;
        int cutOff = Math.round(this.powerPerc*12);
    	while(count <=11){
    		if(this.powerPaths[count] != null && count<cutOff){
    			canvas.drawPath(this.powerPaths[count], activePowerBar);
    		}else{
    			canvas.drawPath(this.powerPaths[count], inactivePowerBar);
    		}
    		count++;
    	}
    	
    	count = 0;
    	while(count <=11){
    		canvas.drawPath(this.batteryPaths[count], activeBatteryBar);    		
    		count++;
    	}
    	
        invalidate();
    }
    
    public void setTilt(float degrees){
    	tilt = degrees;
    }
    
    public void setPowerPerc(float powerPerc){
    	this.powerPerc = powerPerc;
    }
    
}
