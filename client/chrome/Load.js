window.addEventListener("load", function() {

	var client = baseClient('udp');
    client.connect(
    '192.168.0.11', 2047,
    function() {
      console.log("Connected");
    }
    );
    /*client.send(new Uint8Array([[17],[156]]).buffer, function(sendResult) {
      console.debug('send', sendResult);
    });*/

    function steer(steerVal){
      client.send(new Uint8Array([[17],[steerVal<<1]]).buffer, function(sendResult) {
        //console.debug('send', sendResult);
      });
    }

    function power(powerVal){
      client.send(new Uint8Array([[33],[powerVal<<1]]).buffer, function(sendResult) {
        //console.debug('send', sendResult);
      });
    }

    var powerElm = document.getElementById('power');
    powerElm.onchange=function(){
    	power(powerElm.value)
    };

	steerElm = document.getElementById('steer');
    steerElm.onchange=function(){
    	steer(steerElm.value);
    };

});