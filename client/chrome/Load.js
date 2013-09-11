window.addEventListener("load", function() {

  var client = baseClient('udp');
  client.connect(
    '192.168.0.11', 2047,
    function() {
      console.log("Connected");
    }
  );

  var powerVal = 50;
  var steerVal = 50;
  var fallbackTime= 200; // Time till fallback enabled in ms
  var fallbackTimeout; // Actual timeout

  var steerElm = document.getElementById('steer');
  var powerElm = document.getElementById('power');
  
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
  
  powerElm.onchange=function(){
  	power(powerElm.value)
  };
  
  steerElm.onchange=function(){
    steer(steerElm.value);
  };

  //if no further commands fall back to 50
  function fallback(){
    clearTimeout(fallbackTimeout);
    fallbackTimeout = setTimeout(function(){
      steer(50);
      steerElm.value = 50;
      power(50);
      powerElm.value = 50;
    },fallbackTime);
  }

  function cursorSteer(steerVal){
    steer(steerVal);
    steerElm.value = steerVal;
    fallback();
  }

  function cursorPower(powerVal){
    power(powerVal);
    powerElm.value = powerVal;
    fallback();
  }

  // Move on cursor keys
  document.onkeydown = function(e) {
    e = e || window.event;
    switch(e.which || e.keyCode) {
      case 37: // left
      cursorSteer(0);
      break;

      case 38: // up
      cursorPower(40);
      break;

      case 39: // right
      cursorSteer(100);
      break;

      case 40: // down
      cursorPower(60);
      break;

      default: return; // exit this handler for other keys
    }
    e.preventDefault(); // prevent the default action (scroll / move caret)
  };

  // Disconnect current UDP connect and start new one with
  // new ip
  window.changeIP = function(ip){
    client.disconnect()
    client.connect(
      ip, 2047,
      function() {
        console.log("Connected");
      }
    );
  }

});

