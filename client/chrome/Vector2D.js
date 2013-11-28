(function(){
    var vector2D = function(opts, c){
 
        var that = {};
        opts = opts || {};
        that.x = opts.x || 0;
        that.y = opts.y || 0;


        // Set new values
        that.set = function(x, y) {
            that.x = x;
            that.y = y;
        };


        /*****
        *
        *   length
        *
        *****/
        that.length = function() {
            return Math.sqrt(that.x*that.x + that.y*that.y);
        };


        that.normalize = function(){
        	var len = that.length();
        	if (len != 0.0)
        	{
        		that.x = (that.x / len);
        		that.y = (that.y / len);
        	}
        	else
        	{
        		that.x = (0.0);
        		that.y = (0.0);
        	}

        	return that;
        }

        /*****
        *
        *   dot
        *
        *****/
        that.dot = function(in_vector) {
            return that.x*in_vector.x + that.y*in_vector.y;
        };


        /*****
        *
        *   cross
        *
        *****/
        that.cross = function(in_vector) {
            return that.x*in_vector.y - that.y*in_vector.x;
        }


        /*****
        *
        *   unit
        *
        *****/
        that.unit = function() {
            return that.divide( that.length() );
        };


        /*****
        *
        *   unitEquals
        *
        *****/
        that.unitEquals = function() {
            that.divideEquals( that.length() );
            return that;
        };


        /*****
        *
        *   add
        *
        *****/
        that.add = function(in_vector) {
            var newVector = Vector2D({x:that.x + in_vector.x, y:that.y + in_vector.y});
            return newVector;
        };


        /*****
        *
        *   addEquals
        *
        *****/
        that.addEquals = function(in_vector) {
            that.x += in_vector.x;
            that.y += in_vector.y;

            return that;
        };


        /*****
        *
        *   subtract
        *
        *****/
        that.subtract = function(in_vector,log) {
            return Vector2D((that.x - in_vector.x), (that.y - in_vector.y));
        };


        /*****
        *
        *   subtractEquals
        *
        *****/
        that.subtractEquals = function(in_vector) {
            that.x -= in_vector.x;
            that.y -= in_vector.y;

            return that;
        };


        /*****
        *
        *   multiply
        *
        *****/
        that.multiply = function(scalar) {
            return Vector2D(that.x * scalar, that.y * scalar);
        };


        /*****
        *
        *   multiplyEquals
        *
        *****/
        that.multiplyEquals = function(scalar) {
            that.x *= scalar;
            that.y *= scalar;

            return that;
        };


        /*****
        *
        *   divide
        *
        *****/
        that.divide = function(scalar) {
            return Vector2D(that.x / scalar, that.y / scalar);
        };


        /*****
        *
        *   divideEquals
        *
        *****/
        that.divideEquals = function(scalar) {
            that.x /= scalar;
            that.y /= scalar;

            return that;
        };


        /*****
        *
        *   perp
        *
        *****/
        that.perp = function() {
            return Vector2D(-that.y, that.x);
        };


        /*****
        *
        *   perpendicular
        *
        *****/
        that.perpendicular = function(in_vector) {
            return that.subtract(that.project(in_vector));
        };


        /*****
        *
        *   project
        *
        *****/
        that.project = function(in_vector) {
            var percent = that.dot(in_vector) / that.dot(in_vector);

            return that.multiply(percent);
        };


        /*****
        *
        *   toString
        *
        *****/
        that.toString = function() {
            return "<"+that.x + "," + that.y+">";
        };


        /*****
        *
        *   fromPoints
        *
        *****/
        Vector2D.fromPoints = function(p1, p2) {
            return Vector2D(
                p2.x - p1.x,
                p2.y - p1.y
            );
        };


        return that;
      };
      
      Vector2D = vector2D;

})();