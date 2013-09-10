var baseClient = function(socketMode) {
  var NoAddressException = "No Address";
  var NotConnectedException = "Not Connected";

  var socket = chrome.socket || chrome.experimental.socket;
  var address;
  var socketInfo;
  var connected = false;
  var callbacks = [];
  var that = {};

  that.connect = function(inAddress, port, callback, responseHandler) {
    if(!!inAddress == false) throw NoAddressException;

    address = inAddress;
    port = port || this.defaultPort;
    console.debug('creating socket', socketMode, address, port);
    socket.create(socketMode, {}, function(_socketInfo) {
      socketInfo = _socketInfo;
      socket.connect(socketInfo.socketId, address, port, function(connectResult) {
        console.debug('connectResult', connectResult);
        connected = (connectResult == 0);
        socket.ondata = function(result) {
          if (callbacks.length > 0) {
            callbacks.shift()(result);           
          }
        };
        that.poll();
        callback(connected);
      });
    });
  };

  that.poll = function() {
    if(!!address == false) throw NoAddressException; 
    if(connected == false) throw NotConnectedException;
    socket.read(socketInfo.socketId, function(result) {
      if (result.resultCode > 0) {
        socket.ondata(result);
      }
      that.poll();
    });
  };

  that.send = function(data, callback) {
    callback = callback || function() {};
    if(!!address == false) throw NoAddressException; 
    if(connected == false) throw NotConnectedException; 
    socket.write(socketInfo.socketId, data, function(sendResult) {
      callback(sendResult);
    });
  };

  that.receive = function(callback) {
    if(!!address == false) throw NoAddressException; 
    if(connected == false) throw NotConnectedException;
    callbacks.push(callback);
  };

  that.disconnect = function() {
    if(!!address == false) throw NoAddressException; 
    if(connected == false) throw NotConnectedException; 
    socket.disconnect(socketInfo.socketId);
    socket.destroy(socketInfo.socketId);
    connected = false;
  };
  return that;
};


    var client = new baseClient('udp');
    client.connect(
    '192.168.0.11', 2047,
    function() {
      console.log("Connected");
    }
    );
    client.send(new Uint8Array([[17],[156]]).buffer, function(sendResult) {
      console.debug('send', sendResult);
    });

    function steer(steerVal){
      client.send(new Uint8Array([[17],[steerVal<<1]]).buffer, function(sendResult) {
        console.debug('send', sendResult);
      });
    }

    function power(powerVal){
      client.send(new Uint8Array([[33],[powerVal<<1]]).buffer, function(sendResult) {
        console.debug('send', sendResult);
      });
    }


