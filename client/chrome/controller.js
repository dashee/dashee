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
        var curAutomation = automationForward();

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
            var serverBuffer = server.getBufferBytes();

            /*var commandsServer = {};
            commandsServer.steering = (serverBuffer[1]);
            commandsServer.throttle = (serverBuffer[2]);*/

            var commandsServer = curAutomation.update();         

            vehicle.update(commandsServer);
        }

        function animloop(){
            window.webkitRequestAnimationFrame(animloop);
            that.applyStep();
        };

        return that;
      };
      
      controller = mainControl();

})();