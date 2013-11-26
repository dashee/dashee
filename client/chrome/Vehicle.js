(function(){
    // Parent class for vehicle will have magnitude and direction
    // Direction will be a vector, it should start facing "north."
    var vehicle = function(opts, c){
 
        var that = {};
        opts = opts || {};
        var position = Vector2D({x:500, y:500});
        var velocity = Vector2D({x:.1, y:.3});

        //given commands update your position
        that.update = function(commands){
            
            var rotator = document.getElementById('rotater');
            rotator.style.webkitTransform="rotate("+commands.steering+"deg)";
            that.adjustPosition();
            rotator.style.left = position.x+"px";
            rotator.style.top = position.y+"px";
        }

        // Given the current velocity adjust the vehicles position.
        that.adjustPosition = function(){
            position = position.add(velocity);
        }

        return that;
      };
      
      Vehicle = vehicle;

})();