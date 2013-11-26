(function(){
    // Maintains state of world, updating objects step by step
    // according to user input and world factor such as friction and
    // collisions.
    var mainControl = function(opts, c){
 
        var that = {};
        opts = opts || {};



        /*var c=document.getElementById("stage");
        var ctx=c.getContext("2d");*/

        var server;
        var vehicle;

        window.addEventListener("load", function() {
            console.log(" --- Create UDP Server");
            server = UDPServer();
            vehicle = Vehicle();
            console.log(" --- Start Main Animation Loop");
            animloop();
        });

        // Update feedback on server commands and packet rate.
        function updateHudFields(){
            // @TODO use some MVC solution to update these values
            var packetsPerSec = document.getElementById('packets-per-sec');
            var throttleLabel = document.getElementById('throttle-val');
            var steerLabel = document.getElementById('steer-val');
            
        }

        var startTime = new Date().getTime();
        var lastSec = 0;

        that.applyStep = function(){
            var curTime = new Date().getTime();
            var secondsPassed = Math.round((curTime - startTime) / 1000);
            
            //Get current server commands
            var serverCommands = server.getCommands();

            vehicle.update(serverCommands);
        }

        function animloop(){
            window.webkitRequestAnimationFrame(animloop);
            that.applyStep();
        };

        return that;
      };
      
      mainControl = mainControl();

})();