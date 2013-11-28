// Handles mapping between ranges of numbers
// e.g. range1 1..10 range2 1..100 mapping(5) would return 59.

(function(){
       
       var mapping = function(leftMin, leftMax, rightMin, rightMax){
           //Figure out how 'wide' each range is
           var leftSpan = leftMax - leftMin;
           var rightSpan = rightMax - rightMin;
           return function(value){
              //Convert the left range into a 0-1 range (float)
              var valueScaled = (value - leftMin) / (leftSpan);
              //Convert the 0-1 range into a value in the right range.
              return rightMin + (valueScaled * rightSpan); 
           }
       };
       
       rangeMapping = mapping;
       
})();