#include "Hardware/Accelerometer/ADXL345.h"

using namespace dashee::test::Hardware;

/**
 * Initialize our accelerometer class
 */
void AccelerometerADXL345::setUp()
{
    this->accelerometer = new dashee::Hardware::AccelerometerADXL345();
}

/**
 * Test the default state of the loaded class. This must always assume that the 
 * `g` value is set to 0 from the default constructor.
 */
void AccelerometerADXL345::testConstructDefault()
{
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Point<double>(0.0f,0.0f,0.0f)
	);
}

/**
 * Test the construction when a I2C device is passed through. The only assertion
 * we run is that the i2c object should be not null as the relationship is 
 * aggregate.
 */
void AccelerometerADXL345::testConstructI2C()
{
    // Delete existing accelerometer from setUp
    delete this->accelerometer;

    // Create and destroy a AccelerometerADXL345 object with I2C
    dashee::I2C * i2c = new dashee::I2C(1, 0x53);
    this->accelerometer = new dashee::Hardware::AccelerometerADXL345(i2c);
    delete this->accelerometer;

    // Make sure that I2C was not deleted
    CPPUNIT_ASSERT(i2c != NULL);

    // Free and reset for tear down
    delete i2c;
    this->accelerometer = new dashee::Hardware::AccelerometerADXL345();
}

/**
 * Test setting the range and getting the range values back from the server.
 * The values that can be set are 2, 4, 8 and 16 anything else is invalid
 * which is testing in testInvalidRange();
 */
void AccelerometerADXL345::testSetAndGetRange()
{
    // Check the initial value
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 2);

    this->accelerometer->setRange(2);
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 2);

    this->accelerometer->setRange(4);
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 4);
    
    this->accelerometer->setRange(8);
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 8);
    
    this->accelerometer->setRange(16);
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 16);
}

/**
 * Test to see setting and getting the scale factor value. This does not test
 * the actual scaling.
 */
void AccelerometerADXL345::testSetAndGetScaleType()
{
    CPPUNIT_ASSERT(
	    this->accelerometer->getScaleType() 
	    == dashee::Hardware::AccelerometerADXL345::SCALE_G
	);

    this->accelerometer->setScaleType(
	    dashee::Hardware::AccelerometerADXL345::SCALE_RAW
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getScaleType() 
	    == dashee::Hardware::AccelerometerADXL345::SCALE_RAW
	);
    
    this->accelerometer->setScaleType(
	    dashee::Hardware::AccelerometerADXL345::SCALE_MS2
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getScaleType() 
	    == dashee::Hardware::AccelerometerADXL345::SCALE_MS2
	);
    
    this->accelerometer->setScaleType(
	    dashee::Hardware::AccelerometerADXL345::SCALE_G
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getScaleType() 
	    == dashee::Hardware::AccelerometerADXL345::SCALE_G
	);
}

/**
 * Test setting and getting the bandwidth, using enums instead of actual values
 */
void AccelerometerADXL345::testSetAndGetBandwidth()
{
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_800
	);

    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_0_10
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_0_10
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_0_20
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_0_20
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_0_39
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_0_39
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_0_78
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_0_78
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_1_56
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_1_56
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_3_13
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_3_13
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_6_25
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_6_25
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_12_5
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_12_5
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_25
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_25
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_50
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_50
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_100
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_100
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_200
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_200
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_400
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_400
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_800
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_800
	);

    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_1600
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_1600
	);

    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_3200
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_3200
	);
}

/**
 * Test the read function by calling read on the Accelerometer.
 *
 * Given our initial `g` state is `[0,0,0]` post update we should at least
 * get Z coordinate to be approximately 9.8 so we can safely assume that after
 * the first update of our accelerometer we no longer are `[0,0,0]` but 
 * somewhere approximately `[0,0,1.0]`. This is of course assuming that we are 
 * not accelerating in the X or Y.
 *
 * Another guess we can take in the test bed is to rely on the sensor level so 
 * the Z axis is registering atleast `1g`, and so we can tests for approximation
 * of Z axis where `0.5 >= Z axis < 1.5`. Change this as you may,
 *
 * I am not sure we can go further than the above simple testing otherwise 
 * unless ofcourse we can simulate the exact forces applied to our sensor.
 * 
 * Good luck with that!
 */
void AccelerometerADXL345::testReadAndUpdate()
{
    // Once updated the value of the accelerometer will not be the
    // constructed one, and run it twice just to be sure
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    != dashee::Point<double>(0.0,0.0,0.0)
	);
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    != dashee::Point<double>(0.0,0.0,0.0)
	);

    // We are on earth so lets assume we are experiencing approximately 1g 
    // pointing down, and pretty stable in X, and Y plane, therefore we can 
    // test for approximate range values. The test here might change according
    // to the sensor, as different sensors are calibrated differently.
    //
    // Another thing to make sure is to run it a few times before confirming the
    // test has passed.
    //
    // The values here are represented as values that came out of the sensor
    for (size_t x = 0; x < 500; ++x)
    {

	dashee::Point<double> gVector = this->accelerometer->read();
	
	// Good for debugging
	/*
	dashee::Log::info(
		1, 
		"Val %f, %f, %f", 
		gVector.getX(), 
		gVector.getY(), 
		gVector.getZ()
	    );
	*/

	CPPUNIT_ASSERT(gVector.getX() > -0.1);
	CPPUNIT_ASSERT(gVector.getX() < 0.1);
	CPPUNIT_ASSERT(gVector.getY() > -0.1);
	CPPUNIT_ASSERT(gVector.getY() < 0.1);
	CPPUNIT_ASSERT(gVector.getZ() > 0.80);
	CPPUNIT_ASSERT(gVector.getZ() < 1.15);
	dashee::sleep(1000);
    }
}

/**
 * Test to ensure that our scaling is good.
 */
void AccelerometerADXL345::testReadAndUpdateScaled()
{
    size_t iterateTimes = 500;
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_800
	);

    this->accelerometer->setScaleType(
	    dashee::Hardware::AccelerometerADXL345::SCALE_RAW
	);

    for (size_t x = 0; x < iterateTimes; ++x)
    {
	this->accelerometer->update();
	dashee::Point<double> gVector = this->accelerometer->read();

	/*
	// Good for debugging
	dashee::Log::info(
		1, 
		"Val %f, %f, %f", 
		gVector.getX(), 
		gVector.getY(), 
		gVector.getZ()
	    );
	*/
	CPPUNIT_ASSERT(gVector.getX() > -30.0 && gVector.getX() < 30.0);
	CPPUNIT_ASSERT(gVector.getY() > -30.0 && gVector.getY() < 30.0);
	CPPUNIT_ASSERT(gVector.getZ() > 200.0 && gVector.getZ() < 280.0);

	dashee::sleep(1000);
    }
    
    this->accelerometer->setScaleType(
	    dashee::Hardware::AccelerometerADXL345::SCALE_MS2
	);

    for (size_t x = 0; x < iterateTimes; ++x)
    {
	this->accelerometer->update();
	dashee::Point<double> gVector = this->accelerometer->read();

	/*
	// Good for debugging
	dashee::Log::info(
		1, 
		"Val %f, %f, %f", 
		gVector.getX(), 
		gVector.getY(), 
		gVector.getZ()
	    );
	*/

	CPPUNIT_ASSERT(gVector.getX() > -1.0);
	CPPUNIT_ASSERT(gVector.getX() < 1.5);
	CPPUNIT_ASSERT(gVector.getY() > -1.0);
	CPPUNIT_ASSERT(gVector.getY() < 1.0);
	CPPUNIT_ASSERT(gVector.getZ() > 8.5);
	CPPUNIT_ASSERT(gVector.getZ() < 10.0);
	dashee::sleep(1000);
    }
}

/**
 * Null pointers to the I2C construct are not allowed
 */
void AccelerometerADXL345::testInvalidI2C()
{
    dashee::I2C * i2c = NULL;
    dashee::Hardware::AccelerometerADXL345 * temp 
	= new dashee::Hardware::AccelerometerADXL345(i2c);
    temp->update(); // Dummy so it does not complain about unused
}

/**
 * The accelerometer throws a custom exception when the range value is an 
 * invalid value sent to setRange()
 */
void AccelerometerADXL345::testInvalidRange()
{
    // This should throw dashee::Hardware::ExceptionAccelerometerADXL345
    this->accelerometer->setRange(7);
}

/**
 * An invalid bandwidth range should throw an exception
 */
void AccelerometerADXL345::testInvalidBandwidth()
{
    this->accelerometer->setBandwidthRate(
	    static_cast<dashee::Hardware::AccelerometerADXL345::BandwidthRate>
	    (2000)
	);
}

/**
 * Delete the pointer to the accelerometer
 */
void AccelerometerADXL345::tearDown()
{
    delete this->accelerometer;
}

