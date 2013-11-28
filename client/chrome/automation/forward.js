(function(){
    // Automatically move the car forward
    var auto = function(opts){
 
        var that = automation();
        opts = opts || {};

        // Given the current the state of afairs
        // return dashee commands.
        that.update = function(){
            return {
                'throttle':255,
                'steering':50,
            };
        }

        return that;
    };
      
    automationForward = auto;

})();