
// shim layer with setTimeout fallback
window.requestAnimFrame = (function(){
  return  window.requestAnimationFrame       ||
          window.webkitRequestAnimationFrame ||
          window.mozRequestAnimationFrame    ||
          function( callback ){
            window.setTimeout(callback, 1000 / 60);
          };
})();

window.addEventListener("load", function() {

  var socketId;
  var rotator;
  var packetCountReset = 1000; // Reset packet count after 1s
  var packetCount = []; // Store an array of packet counts per second
  var curPacketCount = 0; 
  var tempPacketCount = 0; 
  var samples=0;
  var prevTime = new Date().getTime();
  var curTime = new Date().getTime(); 
  var packetsPerSec = document.getElementById('packets-per-sec');
  var rotator = document.getElementById('rotater');

  var c=document.getElementById("packetMonitor");
  var ctx=c.getContext("2d");


  // UDP Server listen for packets on port 2047
  chrome.socket.create('udp', function(socketInfo) {
    socketId = socketInfo.socketId;
    chrome.socket.bind(socketId, '0.0.0.0', 2047, function(result) {
    	if (result != 0) {
        chrome.socket.destroy(socketId);
        me.handleError("Error on joinGroup(): ", result);
      } else {
        poll();
      }
    });
  });

  poll = function () {
    if (socketId) {
      chrome.socket.recvFrom(socketId, 1048576, function (result) {
        if (result.resultCode >= 0) {
          var view = arrayBufferToView(result.data);

          // Bitwise AND with 00000001 (1 in decimal) to zero the other command bits and if this is 1 we have a
          if((view[0] & 1) == 1){
          	
          	//console.log('Command '+view[0]);
          	// Bitwise AND with 00001110 (14) to zero the channel number, shift 1 as the first bit just tells us this is a command
              var command = (view[0] & 14) >> 1;

              // Bitwise AND the command byte with 11110000 (240 in decimal) to zero the command number
              // then shift 4 to find the channel number as that is the last 4 bits of the command.
              var channel = (view[0] & 240) >> 4;
              switch (command)
              {
                  case 0:
                  {
                      var target = (view[1] >> 1);

                      if(channel == 1){
                      		rotator.style.webkitTransform="rotate("+target+"deg)";
                      }
                      break;
                  }
                  case 1:
                      //dashee::Log::info(2, "setSpeed(%d)", (unsigned short int)channel);
                      break;
                  case 2:
                      //dashee::Log::info(2, "setAcceleration(%d)", (unsigned short int)channel);
                      break;
                  case 3:
                      /*dashee::Log::info(3, "pong");
                      if (!serverUDP.write("\x80"))
                          throw Exception_ServoController("Pong write failed");*/
                      break;
                  default:
                      //throw Exception_Servo("Invalid Command!");
                      break;
                      
              }
          }

          curTime = new Date().getTime();
          //Register a new packet
          if(curTime - prevTime < 1000){
            tempPacketCount++;
          }else{
            curPacketCount = tempPacketCount;
            packetsPerSec.innerHTML = curPacketCount; // Rough estimate
            samples++;
            tempPacketCount = 0;
            prevTime = curTime;
          }
          

          poll();
        } else {
          handleError("", result.resultCode);
          disconnect();
        }
      });
    }
  };

  disconnect = function (callback) {
    socketId = undefined;
    chrome.socket.destroy(socketId);
    this.onDisconnected();
    if (callback) {
      callback.call(this);
    }
  };

  handleError = function (additionalMessage, alternativeMessage) {
    var err = chrome.runtime.lastError;
    err = err && err.message || alternativeMessage;
    console.log(additionalMessage + err);
  };

  arrayBufferToView = function (arrayBuffer) {
    // UTF-16LE
    return new Uint8Array(arrayBuffer);
  };

  arrayBufferToString = function (arrayBuffer) {
    // UTF-16LE
    return String.fromCharCode.apply(String, new Uint8Array(arrayBuffer));
  };

  stringToArrayBuffer = function (string) {
    // UTF-16LE
    var buf = new ArrayBuffer(string.length * 2);
    var bufView = new Uint16Array(buf);
    for (var i = 0, strLen = string.length; i < strLen; i++) {
      bufView[i] = string.charCodeAt(i);
    }
    return buf;
  };

/*ctx.strokeStyle="#FF0000";
ctx.moveTo(0,200);
startTime = new Date().getTime();
lastSec = 0;

  graphPackets = function(){
    var curTime = new Date().getTime();
    var secondsPassed = Math.round((curTime - startTime) / 1000);
    if(secondsPassed != lastSec){
      ctx.lineTo(secondsPassed,200-curPacketCount);
      ctx.stroke();
    }
    lastSec = secondsPassed;
  }

  function animloop(){
    requestAnimFrame(animloop);
    graphPackets();
  };

  animloop();*/

});

