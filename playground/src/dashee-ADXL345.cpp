/**
 * For testing, taken from http://goo.gl/IohROG
 */

#include <iostream>
#include <dashee/common.h>
#include <dashee/Hardware/Accelerometer/ADXL345.h>

int main()
{
    dashee::Hardware::AccelerometerADXL345 a;

    while (true)
    {
	a.update();
	dashee::Point<float> temp = a.read();
	std::cout << 
	   temp.getX() << ", " <<
	   temp.getY() << ", " <<
	   temp.getZ() << 
	   std::endl;

	dashee::sleep(30000);
    }

    return 0;
}

