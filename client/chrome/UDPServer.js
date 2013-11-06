
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
  var throttleLabel = document.getElementById('throttle-val');
  var steerLabel = document.getElementById('steer-val');
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
      chrome.socket.recvFrom(socketId, 2048576, function (result) {
        if (result.resultCode >= 0) {
          var bytes = arrayBufferToView(result.data);
          var steeringValue = (bytes[1]);
          steerLabel.innerHTML = steeringValue;
          var throttleValue = (bytes[2]);
          throttleLabel.innerHTML = throttleValue;
          rotator.style.webkitTransform="rotate("+steeringValue+"deg)";
  
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
          
          chrome.socket.sendTo(socketId, stringToArrayBuffer('k'), result.address, result.port, function(){});
          
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

