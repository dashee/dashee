/**
 * For testing, taken from http://goo.gl/IohROG
 */

#include <iostream>
#include <dashee/common.h>
#include <dashee/Hardware/Accelerometer/ADXL345.h>

int main()
{
    dashee::Hardware::AccelerometerADXL345 a;
    a.setScaleType(dashee::Hardware::AccelerometerADXL345::SCALE_G);

    while (true)
    {
	a.update();
	dashee::Point<double> temp = a.read();
	std::cout << 
	   temp.getX() << ", " <<
	   temp.getY() << ", " <<
	   temp.getZ() << 
	   std::endl;

	dashee::sleep(30000);
    }

    return 0;
}

