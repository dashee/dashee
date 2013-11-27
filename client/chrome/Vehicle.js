(function(){
    // Parent class for vehicle will have magnitude and direction
    // Direction will be a vector, it should start facing "north."
    var vehicle = function(opts, c){
 
        var that = {};
        opts = opts || {};
        var position = Vector2D({x:250, y:250});
        var direction = Vector2D({x:.0, y:-1});
        
        var carOrientation = 270;
        var speed = 0.1;

        var frontLeftWheel = document.getElementById('wheel-1');
        var frontRightWheel = document.getElementById('wheel-2');
        var vehicleElement = document.getElementById('car');
        // Map between dashee steer values realistic wheel turns
        var steerMapping = rangeMapping(0,255,0,60);
        var steerRightMapping = rangeMapping(128,255,0,1.0);
        var steerLeftMapping = rangeMapping(0,128,-1.0,0);
        var powerMapping = rangeMapping(0,255,-3.5,3.5);

        //given commands update your position
        that.update = function(commands){
            turnWheels(commands);
            that.adjustPosition();
            speed = powerMapping(commands.throttle);
            if(speed<0.1 && speed>-0.1) speed =0;
            
            setTargetDirection();
            //console.log(position.x);
            vehicleElement.style.left = position.x+"px";
            vehicleElement.style.top = position.y+"px";
        }

        // Given the current velocity adjust the vehicles position.
        that.adjustPosition = function(){
            position = position.add(direction);
        }

        // Depending on the severity of the steer adjust the orientation
        // of the car, only if there forward thrust.`
        function applyThrottle(){

        }

        // Rotate the steering wheels to desired steer direction.
        function turnWheels(commands){
            //console.log(commands.steering-128);
            if(speed && commands.steering>136) carOrientation = carOrientation + steerRightMapping(commands.steering);
            if(speed && commands.steering<120) carOrientation = carOrientation + steerLeftMapping(commands.steering);
            
            vehicleElement.style.webkitTransform="rotate("+(carOrientation-90)+"deg)";
            
            var rotateWheelsBy = steerMapping(commands.steering)-30;
            frontLeftWheel.style.webkitTransform="rotate("+(rotateWheelsBy)+"deg)";
            frontRightWheel.style.webkitTransform="rotate("+(rotateWheelsBy)+"deg)";
        }

        // Throttle will move the car forward based on it's current
        // orientation.
        function applyThrottle(){

        }

        function setTargetDirection(){
           var radians = carOrientation * (Math.PI/180);
           var y = -speed * Math.sin(radians);
           var x = -speed * Math.cos(radians);
           direction.set(x,y);
           //console.log(" x: "+direction.x+" y: "+direction.y);
        }

        setTargetDirection();

        return that;
      };
      
      Vehicle = vehicle;

})();