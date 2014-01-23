/**
 * For testing, taken from http://goo.gl/IohROG
 */

#include <iostream>
#include <iomanip>
#include <dashee/common.h>
#include <dashee/Hardware/Accelerometer/ADXL345.h>

int main()
{
    dashee::Hardware::AccelerometerADXL345 a;
    a.setScaleType(dashee::Hardware::AccelerometerADXL345::SCALE_MS2);

    while (true)
    {
	a.update();
	dashee::Point<double> temp = a.read();
	std::cout << 
	   std::setfill(' ') << std::setw(10) << temp.getX() << ", " <<
	   std::setfill(' ') << std::setw(10) << temp.getY() << ", " <<
	   std::setfill(' ') << std::setw(10) << temp.getZ() << ", " <<
	   std::endl;

	dashee::sleep(10000);
    }

    return 0;
}

