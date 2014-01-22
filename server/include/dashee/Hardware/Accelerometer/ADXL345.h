/**
 * @file include/dashee/Hardware/Accelerometer/ADXL345.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_HARDWARE_ACCELEROMETER_ADXL345_H_
#define DASHEE_HARDWARE_ACCELEROMETER_ADXL345_H_

#include <math.h>
#include <dashee/constants.h>
#include <dashee/I2C.h>
#include <dashee/Hardware/Accelerometer.h>
#include <dashee/Hardware/Exception/Accelerometer/ADXL345.h>

namespace dashee
{
    namespace Hardware
    {
	class AccelerometerADXL345;
    }
}

/**
 * Control interface for the ADXL345 chip.
 *
 * You can find out in detail about the chip at http://goo.gl/RyfX6J where it 
 * holds all the information about the register. This class does not provide all
 * the functionality help by the chip, only those which is used by our system.
 * Feel free to add your own.
 *
 * Usage:
 *
 *     Coordinate<float> g;
 *     AccelerometerADXL345 accelerometer;
 *     accelerometer.setRange(2);
 *     accelerometer.setBandwithRate(
 *         AccelerometerADXL345::BandwidthRate::BW_200
 *     );
 *
 *     while(true)
 *     {
 *         accelerometer.update();
 *         g = accelerometer.read();
 *     }
 */
class dashee::Hardware::AccelerometerADXL345 
    : public dashee::Hardware::Accelerometer
{
private:

    /**
     * The buffer used by update. Easier to initialize it once, rather than 
     * initialize and resize it every time update is called.
     */
    std::vector<unsigned char> dataBuffer;

    /**
     * Variable set to true by our AccelerometerADXL345 which takes in an I2C 
     * device.
     *
     * This variable is a flag that helps destructor delete the I2C variable, if
     * it was generated internally by this class. Otherwise it is the callers
     * responsibility to delete I2C.
     */
    bool isI2CAllocatedInternally;

    // Generic initializers collated in a generic init function
    void init();

    // Calculate the values of X and Y to pitch
    void toRadians();

    // Convert the values of X and Y to degrees
    void toDegrees();
    
    // Disable Copy and Assignment construction
    AccelerometerADXL345(const AccelerometerADXL345 & rhs);
    AccelerometerADXL345& operator=(const AccelerometerADXL345 & rhs);

protected:

    /**
     * Interface to control our device.
     */ 
    dashee::I2C * i2c;

public:
    
    /**
     * The different frequency rate for the sensor stick which the stick
     * understands. 
     *
     * The convention is `BW_RATIONAL_IRRATIONAL`, so `BW_0_10`
     * represents `0.10 Hz` in some cases BW_3200 represents `3200 Hz`
     */
    enum BandwidthRate
    {
	BW_0_10 = 0,
	BW_0_20 = 1,
	BW_0_39 = 2,
	BW_0_78 = 3,
	BW_1_56 = 4,
	BW_3_13 = 5,
	BW_6_25 = 6,
	BW_12_5 = 7,
	BW_25 = 8,
	BW_50 = 9,
	BW_100 = 10,
	BW_200 = 11,
	BW_400 = 12,
	BW_800 = 13,
	BW_1600 = 14,
	BW_3200 = 15
    };

    /**
     * This enum represents how our g values are scaled after update. It is 
     * helpful to allow a use to read values in RAW(as they are in the senor), 
     * G(Number of G's on the sensor) or MS2 (short for meters per second 
     * squared). The scale can be represented as:
     *
     *  - RAW - this->g * 1.0
     *  - G = this->g * SCALE
     *  - MS2 = this->g * SCALE * GRAVITY
     */
    enum ScaleType
    {
	SCALE_RAW,
	SCALE_G,
	SCALE_MS2,
	SCALE_RADIANS,
	SCALE_DEGREES
    };

    /**
     * The scale type used currently.
     */
    ScaleType scale;

    /**
     * The scale value used to convert register values into `g` value.
     *
     * The accelerometer has a constant scale which is used on the raw value
     * to represent the scale of the `G`. How is this generated:
     *
     * Say you set your range to `+/-4g`, this give us a total of `8g` range, 
     * and to scale this we divide the total by `2^bitrange`. Where `bitrange` 
     * is the range of bits a data register represents. The `bitrange` can be 
     * found on http://goo.gl/RyfX6J which are the following:
     *
     *     +/- | totalrange | bits-range
     *     2g  | 4g         | 10
     *     4g  | 8g         | 11
     *     8g  | 16g        | 12
     *     16g | 32g        | 13
     *
     * So applying the above formula we get `0.00390625` for each of the ranges.
     *
     * Example formula with range set to `+/-4g` or `0x01` in the 
     * `DATA_FORMAT:Range` register:
     *
     *    (4 * 2) / (2 ^ 11)
     *    = 8 / 2048
     *    = 0.00390625
     */
    static const double SCALE;

    /**
     * The constant use to convert G into m/s^2 value. The number here is 
     * derived from SCALE * GRAVITY
     */
    static const double MS2SCALE;

    /**
     * The BW_RATE address.
     */
    const static unsigned char REGISTER_BW_RATE = 0x2C;

    /**
     * The DATA_REGISTER address.
     */
    const static unsigned char REGISTER_DATA_FORMAT = 0x31;

    /**
     * The DATA values
     */
    const static unsigned char REGISTER_DATAX0 = 0x32;
    const static unsigned char REGISTER_DATAX1 = 0x33;
    const static unsigned char REGISTER_DATAY0 = 0x34;
    const static unsigned char REGISTER_DATAY1 = 0x35;
    const static unsigned char REGISTER_DATAZ0 = 0x36;
    const static unsigned char REGISTER_DATAZ1 = 0x37;

    // Construct
    AccelerometerADXL345();
    AccelerometerADXL345(dashee::I2C * i2c);

    // Set and Get Range
    void setRange(const unsigned short int);
    unsigned short int getRange() const;

    // Set and Get Scale Factor
    void setScaleType(const ScaleType scale);
    ScaleType getScaleType() const;

    // Set and Get Bandwidth
    void setBandwidthRate(const BandwidthRate rate);
    BandwidthRate getBandwidthRate() const;

    // Update the sensor
    void update();

    // Destruct
    virtual ~AccelerometerADXL345();
};

#endif
