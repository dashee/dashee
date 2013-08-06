package com.confusedbrowser.androneee_remote;

import android.content.Context;
import android.graphics.*;
import android.util.Log;
import android.view.View;

/**
 * This is currently mapping out the HUD display
 * as of Shahmir's hud.fw.png, it should draw a central steer arc
 * which will move when the car is steering. To the left and right are gauges
 * reflecting power and battery.
 *
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class DrawHud extends View
{
    Context context;

    /*
     * Various paths to be defined onSizeChanged
     */
    Path steerPath = new Path();
    Path[] powerPaths = new Path[12];
    Path[] batteryPaths = new Path[12];
    Path powerOuterArc = new Path();
    Path batteryOuterArc = new Path();
    
    // Steer arc and oval are at the center of the design
    // other aspects are offset from it.
    float steerArcRadius;
    final RectF steerOval = new RectF();
    
    /*
     *  Track positions on the grid.
     */
    float centerX = 0.0f;
    float centerY = 0.0f;
    // Top and bottom of the gauge paths
    double gaugeTopY;
    double gaugeBottomY;
    double gaugeBarHieght;
    double gaugeBarGap;
    
    /*
     * Values to be updated to reflect app state
     */
    float tilt = 50.0f;
    float powerPerc = 0.0f;
    
    /*
     * Style elements go here
     */
    Paint steerLine;
    Paint steerLineLock;
    Paint activePowerBar;
    Paint inactivePowerBar;
    Paint activeBatteryBar;
    Paint powerArc;
    Paint batteryArc;
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
        steerLine.setStrokeWidth(2.0f);
        steerLine.setStyle(Paint.Style.STROKE);
        
        steerLineLock = new Paint();
        steerLineLock.setAntiAlias(true);
        steerLineLock.setColor(lockColor);
        steerLineLock.setAlpha(255);
        steerLineLock.setStrokeWidth(5.0f);
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
        
        powerArc = new Paint();
        powerArc.setAntiAlias(true);
        powerArc.setColor(0xD96D00);
        powerArc.setAlpha(255);
        powerArc.setStrokeWidth(3.0f);
        powerArc.setStyle(Paint.Style.STROKE);
        
        batteryArc = new Paint();
        batteryArc.setAntiAlias(true);
        batteryArc.setColor(0xFFFFFF);
        batteryArc.setAlpha(255);
        batteryArc.setStrokeWidth(3.0f);
        batteryArc.setStyle(Paint.Style.STROKE);

    }
    
    /**
     * Implementing this function gives access to the canvas width and height meaning
     * those calculation can be done as required (usually just once), instead of doing them
     * constantly in the draw.
     */
    protected void onSizeChanged (int w, int h, int oldw, int oldh){
    	// Noticed it sometimes runs with 0 values, not sure why.
    	if(w ==0 || h==0) return;
    	this.centerX = w/2;
    	this.centerY = h/2;
    	this.steerArcRadius = (h - h*0.08f) / 2.0f;
    	this.gaugeBottomY = h-Math.round(h*0.1);
    	this.gaugeBarHieght = Math.round(h*0.053);
    	this.gaugeBarGap = Math.round(h*0.015);
    	this.gaugeTopY = gaugeBottomY - (12*this.gaugeBarHieght) -(11*this.gaugeBarGap);
    	this.buildSteerPath(w, h);
    	this.addGaugePath(w, h, this.powerPaths, true);
    	this.addGaugePath(w, h, this.batteryPaths, false);
    	this.addLeftArc();
    	this.addRightArc();
    }
    
    /*
     * Put together the arc that is to rotate on steer.
     */
    private void buildSteerPath(int w, int h){
    	if (w == 0 || h==0) return;

    	float steerArcSweepAngle = 280.0f;
        float steerArcStartAngle = -180.0f;

        float p1x = (w/2) - this.steerArcRadius;
        float p1y = (h/2) - this.steerArcRadius;
        float p2x = (w/2) + this.steerArcRadius;
        float p2y = (h/2) + this.steerArcRadius;
        
        this.steerOval.set(p1x, p1y, p2x, p2y);
        this.steerPath.arcTo(this.steerOval, steerArcStartAngle, -steerArcSweepAngle, true);
    }
    
    /*
     * Power arc
     */
    private void addLeftArc(){
    	final RectF outerOval = new RectF();
    	float radius = this.steerArcRadius*1.393f;

        float p1x = this.centerX - radius;
        float p1y = this.centerY - radius;
        float p2x = this.centerX + radius;
        float p2y = this.centerY + radius;
        
        outerOval.set(p1x, p1y, p2x, p2y);
        float[] outerArcParams = this.getArcParams(this.gaugeBottomY, this.gaugeTopY, radius, false, true);
        Log.d("dashee", outerArcParams[0]+" , "+-outerArcParams[1]);
        this.powerOuterArc.arcTo(outerOval, outerArcParams[0], -outerArcParams[1], true);
    }
    
    
    /*
     * Battery arc
     */
    private void addRightArc(){
    	final RectF outerOval = new RectF();
    	float radius = this.steerArcRadius*1.393f;

        float p1x = this.centerX - radius;
        float p1y = this.centerY - radius;
        float p2x = this.centerX + radius;
        float p2y = this.centerY + radius;
        
        outerOval.set(p1x, p1y, p2x, p2y);
        float[] outerArcParams = this.getArcParams(this.gaugeBottomY, this.gaugeTopY, radius, false, false);
        Log.d("dashee", outerArcParams[0]+" , "+outerArcParams[1]);
        this.batteryOuterArc.arcTo(outerOval, outerArcParams[0],-outerArcParams[1], true);
    }
    
    /*
     * Put together the arc that is to rotate on steer.
     */
    private void addGaugePath(int w, int h, Path[] paths, boolean leftHandSide){
    	if (w == 0 || h==0) return;
    	final RectF innerOval = new RectF();
        final RectF outerOval = new RectF();
    	float innerRadius = steerArcRadius + steerArcRadius*0.16f;
    	float outerRadius = steerArcRadius + steerArcRadius*0.39f;
    	
    	//Log.d("dashee", "percHieght: "+h*0.1);
    	double curY = this.gaugeBottomY;
    	//Log.d("dashee", "rectSize: "+h*0.053);//38.0
    	double rectHeight = this.gaugeBarHieght;
    	//Log.d("dashee", "gap: "+ Math.round(h*0.015));//11
    	double gap = this.gaugeBarGap;
    	
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
    
    /*
     * Based on desired starY and endY and radius get the appropriate 'path.arcTo' parameters.
     * Uses getCircleX to find the x coordinates that intersect the centered circle, and then
     * the getAngle function calculated the start angle form the center. 
     */
    private float[] getArcParams(double startY, double endY, float radius, boolean reverse, boolean leftHandSide){
    	double startXCoor[] = getCircleX(startY, radius);
    	double endXCoor[] = getCircleX(endY, radius);
    	
    	int xcoordinateSide = (leftHandSide) ? 0 : 1;
        
    	float startAngle = (float) this.getAngle((float) startXCoor[xcoordinateSide], (float) startY);
        float endAngle = (float) this.getAngle((float) endXCoor[xcoordinateSide], (float) (endY));

        float sweepAngle = startAngle - endAngle;
        // If start angle is in 4th quarter and endAngle is in 3rd quarter
        // we will end up drawing almost a full circle want to avoid this
        // and sweep closest distance.
        if(startAngle < -270 && endAngle > -90){
        	sweepAngle = (sweepAngle + 360);
        }
        float[] returnArray = {startAngle, sweepAngle, (float) startXCoor[xcoordinateSide]};
        if(reverse){
        	returnArray[0] = endAngle;
        	returnArray[1] = -sweepAngle;
        	returnArray[2] = (float) endXCoor[xcoordinateSide];
        }
        return returnArray;
    }
    
    /*
     * Calculated the x coordinate of a circle with radius r at the center of the display
     * returns both coordinates as line will intersect 2 times.
     */
    private double[] getCircleX(double y, double r)
    {
        double x = Math.sqrt(Math.abs(Math.pow(r, 2) - Math.pow(y-this.centerY, 2))); 
        double[] returnArray = {Math.abs(x-this.centerX), Math.abs(-x-this.centerX)};
        return returnArray;
    }
   
    /*
     * Calculate the angle from the center of the screen to x, y. Starting at 3 O'Clock.
     * Always return a negative angle, e.g -90 at 12, -180 at 9, -270 at 6.
     */
    private double getAngle(float x, float y)
   {
       double angle1 = Math.atan2(this.centerY - this.centerY, this.centerX - (this.centerX + 10));
       double angle2 = Math.atan2(this.centerY - y, this.centerX - x);
       return -Math.toDegrees(angle1-angle2);
   }
    
    /**
     * Draw our hud paths and apply appropriate paints
     * 
     * @param Canvas canvas - The canvas object to draw on.
     */
    protected void onDraw(Canvas canvas)
    {
        
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
        
        /* Draw Power arcs */
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
    	
    	canvas.drawPath(this.powerOuterArc, powerArc);
    	
    	count = 0;
    	while(count <=11){
    		canvas.drawPath(this.batteryPaths[count], activeBatteryBar);    		
    		count++;
    	}
    	
    	canvas.drawPath(this.batteryOuterArc, batteryArc);
    	
        invalidate();
    }
    
    public void setTilt(float degrees){
    	tilt = degrees;
    }
    
    public void setPowerPerc(float powerPerc){
    	this.powerPerc = powerPerc;
    }
    
}
