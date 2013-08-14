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
    Path[] powerPathsInner = new Path[12];
    Path[] batteryPathsInner = new Path[12];
    Path powerOuterArc = new Path();
    Path batteryOuterArc = new Path();
    
    // Steer arc is  at the center of the design
    // other aspects are offset from it.
    float steerArcRadius;
    float innerGaugeRadius;
	float innerGaugeRadius2;
	float outerGaugeRadius;
	
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
    float lockLineWidth;
    
    /*
     * Values to be updated to reflect app state
     */
    float tilt = 50.0f;
    float powerPerc = 0.0f;
    
    /*
     * Style elements go here
     */
    Paint steerLine;
    Paint horizonLine;
    Paint steerLineLock;
    Paint activePowerBar;
    Paint inactiveBarInset;
    Paint activeBarPowerInset;
    Paint activeBatteryInset;
    Paint inactivePowerBar;
    Paint activeBatteryBar;
    Paint powerArc;
    Paint batteryArc;
    int lineColor = 0x666666;
    int horizonLineColor = 0x333333;
    int lockColor = 0xD93600;
    int activeBarColor = 0xD96D00;
    int inactiveBarColor = 0x20202F;
    int activeBattery = 0xEEEEEE;
    int inactiveBarInsetColor = 0x444450;
    int activePowerInsetColor = 0xDF8429;
    int activeBatterInsetColor = 0xC8C8C8;

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
        
        
        horizonLine = new Paint();
        horizonLine.setAntiAlias(true);
        horizonLine.setColor(horizonLineColor);
        horizonLine.setAlpha(255);
        horizonLine.setStrokeWidth(2.0f);
        horizonLine.setStyle(Paint.Style.STROKE);
        
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
        
        inactiveBarInset = new Paint();
        inactiveBarInset.setAntiAlias(true);
        inactiveBarInset.setColor(inactiveBarInsetColor);
        inactiveBarInset.setAlpha(255);
        inactiveBarInset.setStyle(Paint.Style.FILL);
        
        activeBarPowerInset = new Paint();
        activeBarPowerInset.setAntiAlias(true);
        activeBarPowerInset.setColor(activePowerInsetColor);
        activeBarPowerInset.setAlpha(255);
        activeBarPowerInset.setStyle(Paint.Style.FILL);
        
        activeBatteryInset = new Paint();
        activeBatteryInset.setAntiAlias(true);
        activeBatteryInset.setColor(activeBatterInsetColor);
        activeBatteryInset.setAlpha(255);
        activeBatteryInset.setStyle(Paint.Style.FILL);
        
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
    protected void onSizeChanged (int canvasWidth, int canvasHeight, int oldw, int oldh){
    	// Noticed it sometimes runs with 0 values, not sure why.
    	if(canvasWidth ==0 || canvasHeight==0) return;
    	
    	this.centerX = canvasWidth/2;
    	this.centerY = canvasHeight/2;
    	
    	this.steerArcRadius = (canvasHeight - canvasHeight*0.08f) / 2.0f;
    	//Now three other arc Points on the diagram are percentage increases on the steerArc
    	this.innerGaugeRadius = this.steerArcRadius*1.16f; // 16% bigger
    	this.innerGaugeRadius2 = this.steerArcRadius*1.31f; // 31% bigger
    	this.outerGaugeRadius = this.steerArcRadius*1.39f; // 39% bigger
    	
    	this.lockLineWidth = Math.round(canvasWidth*0.08);
    	this.gaugeBottomY = canvasHeight-Math.round(canvasHeight*0.1);
    	this.gaugeBarHieght = Math.round(canvasHeight*0.053);
    	this.gaugeBarGap = Math.round(canvasHeight*0.015);
    	this.gaugeTopY = gaugeBottomY - (12*this.gaugeBarHieght) -(11*this.gaugeBarGap);
    	
    	// Start Building Our HUD paths.
    	this.buildSteerPath();
    	this.addGaugePath(this.powerPaths, true, this.innerGaugeRadius, this.outerGaugeRadius);
    	this.addGaugePath(this.powerPathsInner, true, this.innerGaugeRadius2, this.outerGaugeRadius);
    	this.addGaugePath(this.batteryPaths, false, this.innerGaugeRadius, this.outerGaugeRadius);
    	this.addGaugePath(this.batteryPathsInner, false, this.innerGaugeRadius2, this.outerGaugeRadius);
    	this.addArc(this.powerOuterArc, true);
    	this.addArc(this.batteryOuterArc, false);
    }
    
    /*
     * Put together the arc that is to rotate on steer.
     */
    private void buildSteerPath(){
    	float steerArcSweepAngle = 280.0f;
        float steerArcStartAngle = -180.0f;
        
        float p1x = this.centerX - this.steerArcRadius;
        float p1y = this.centerY - this.steerArcRadius;
        float p2x = this.centerX + this.steerArcRadius;
        float p2y = this.centerY + this.steerArcRadius;
        
        this.steerOval.set(p1x, p1y, p2x, p2y);
        this.steerPath.arcTo(this.steerOval, steerArcStartAngle, -steerArcSweepAngle, true);
    }
    
    /*
     * Build the outer long arcs on either side of the hud.
     */
    private void addArc(Path inPath, boolean leftHandSide){
    	final RectF outerOval = new RectF();
    	float radius = this.steerArcRadius*1.39f;

        float p1x = this.centerX - radius;
        float p1y = this.centerY - radius;
        float p2x = this.centerX + radius;
        float p2y = this.centerY + radius;
        
        outerOval.set(p1x, p1y, p2x, p2y);
        float[] outerArcParams = this.getArcParams(this.gaugeBottomY, this.gaugeTopY, radius, false, leftHandSide);
        inPath.arcTo(outerOval, outerArcParams[0], -outerArcParams[1], true);
    }
    
    /*
     * Put togther a collection of arc-ed bar paths, with an innerArc and outerArc
     */
    private void addGaugePath(Path[] paths, boolean leftHandSide, float innerRadius, float outerRadius){
    	final RectF innerOval = new RectF();
        final RectF outerOval = new RectF();
    	
    	//Log.d("dashee", "percHieght: "+h*0.1);
    	double curY = this.gaugeBottomY;
    	//Log.d("dashee", "rectSize: "+0.053);//38.0
    	double rectHeight = this.gaugeBarHieght;
    	//Log.d("dashee", "gap: "+ Math.round(0.015));//11
    	double gap = this.gaugeBarGap;
    	
    	float p1x = this.centerX - innerRadius;
        float p1y = this.centerY - innerRadius;
        float p2x = this.centerX + innerRadius;
        float p2y = this.centerY + innerRadius;
        
        float outerP1x = this.centerX - outerRadius;
        float outerP1y = this.centerY - outerRadius;
        float outerP2x = this.centerX + outerRadius;
        float outerP2y = this.centerY + outerRadius;
        
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
    	boolean leftLock = Math.floor(this.tilt) == 0;
    	boolean rightLock = Math.ceil(this.tilt) == 100;
        
    	//Mid line right
    	if(rightLock)
    		canvas.drawLine(this.centerX+this.steerArcRadius-this.lockLineWidth,
    				this.centerY, this.centerX+this.steerArcRadius, this.centerY, steerLineLock);
    	else
    		canvas.drawLine(this.centerX+this.steerArcRadius-this.lockLineWidth, this.centerY,
    				this.centerX+this.steerArcRadius, this.centerY, horizonLine);
        
        //Mid line left
    	if(leftLock)
    		canvas.drawLine(this.centerX-this.steerArcRadius+this.lockLineWidth, this.centerY,
    				this.centerX-this.steerArcRadius, this.centerY, steerLineLock);
    	else
    		canvas.drawLine(this.centerX-this.steerArcRadius+this.lockLineWidth, this.centerY,
    				this.centerX-this.steerArcRadius, this.centerY, horizonLine);
    	
        canvas.save();
        canvas.rotate(this.tilt, this.centerX, this.centerY);
        if(rightLock || leftLock){
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
    			canvas.drawPath(this.powerPathsInner[count], activeBarPowerInset);
    		}else{
    			canvas.drawPath(this.powerPaths[count], inactivePowerBar);
    			canvas.drawPath(this.powerPathsInner[count], inactiveBarInset);
    		}
    		canvas.drawPath(this.batteryPaths[count], activeBatteryBar);
    		canvas.drawPath(this.batteryPathsInner[count], activeBatteryInset);
    		count++;
    	}
    	
    	canvas.drawPath(this.powerOuterArc, powerArc);
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
