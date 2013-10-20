#include "Config.h"

/**
 * Start up and set the configuration
 */ 
void dashee::test::Config::setUp()
{
    this->config = new dashee::Config();
}

/**
 * Set key values and test ther validation.
 *
 * This will test setting, then getting, and also
 * ensure that the size of the config class stays consistent
 * with the values that are set.
 *
 * This function will also test overwrite behaviour. When overwrite
 * is disabled setting a new value must not overwrite an existing value
 */
void dashee::test::Config::testSetAndGet()
{
    // Set two key values and test there return
    this->config->set("myfirstkey", "Hello world");
    CPPUNIT_ASSERT(strcmp(this->config->get("myfirstkey"), "Hello world") == 0);
    this->config->set("myfirstkey", "Hello earth");
    CPPUNIT_ASSERT(strcmp(this->config->get("myfirstkey"), "Hello earth") == 0);
    this->config->set("myfirstkey", "Hello Ladies", false);
    CPPUNIT_ASSERT(strcmp(this->config->get("myfirstkey"), "Hello earth") == 0);

    // Ensure a second key works just as well
    this->config->set("mysecondkey", "Hello Universe!");
    CPPUNIT_ASSERT(strcmp(this->config->get("mysecondkey"), "Hello Universe!") == 0);
    this->config->set("mysecondkey", "Hello earth");
    CPPUNIT_ASSERT(strcmp(this->config->get("mysecondkey"), "Hello earth") == 0);
    this->config->set("mysecondkey", "Hello Ladies", false);
    CPPUNIT_ASSERT(strcmp(this->config->get("mysecondkey"), "Hello earth") == 0);

    // test a value that is not set and has no default, should
    // return NULL. If ia default is provided ensure the default works
    CPPUNIT_ASSERT(this->config->get("keythatisnotset") == NULL);
    CPPUNIT_ASSERT(strcmp(this->config->get("keythatisnotset", "Hello Mars"), "Hello Mars") == 0);
}

/**
 * 
 */
void dashee::test::Config::testSetAndGetInt()
{
    // Test int when set as a int
    this->config->set("mynumber", 1986);
    CPPUNIT_ASSERT(this->config->getInt("mynumber") == 1986);
    this->config->set("mynumber", 1991);
    CPPUNIT_ASSERT(this->config->getInt("mynumber") == 1991);
    this->config->set("mynumber", 2013, false);
    CPPUNIT_ASSERT(this->config->getInt("mynumber") == 1991);
    this->config->set("mynumber", 1001);
    CPPUNIT_ASSERT(this->config->getInt("mynumber") == 1001);


    // Test int when set as a string
    this->config->set("mynumberstring", "10");
    CPPUNIT_ASSERT(this->config->getInt("mynumberstring") == 10);
    this->config->set("mynumberstring", "50");
    CPPUNIT_ASSERT(this->config->getInt("mynumberstring") == 50);
    this->config->set("mynumberstring", "999", false);
    CPPUNIT_ASSERT(this->config->getInt("mynumberstring") == 50);

    // Test values which are not set
    CPPUNIT_ASSERT(this->config->getUInt("numbernotset") == 0);
    CPPUNIT_ASSERT(this->config->getUInt("numbernotset", 27) == 27);
}

/**
 * Set the key values as integers and test thier validation.
 */
void dashee::test::Config::testSetAndGetUnsignedInt()
{
    // Test int when set as a int
    this->config->set("mynumber", 1986u);
    CPPUNIT_ASSERT(this->config->getInt("mynumber") == 1986u);
    this->config->set("mynumber", 1991u);
    CPPUNIT_ASSERT(this->config->getInt("mynumber") == 1991u);
    this->config->set("mynumber", 2013u, false);
    CPPUNIT_ASSERT(this->config->getInt("mynumber") == 1991u);
    this->config->set("mynumber", 1001u);
    CPPUNIT_ASSERT(this->config->getInt("mynumber") == 1001u);


    // Test int when set as a string
    this->config->set("mynumberstring", "10");
    CPPUNIT_ASSERT(this->config->getUInt("mynumberstring") == 10u);
    this->config->set("mynumberstring", "50");
    CPPUNIT_ASSERT(this->config->getUInt("mynumberstring") == 50u);
    this->config->set("mynumberstring", "999", false);
    CPPUNIT_ASSERT(this->config->getUInt("mynumberstring") == 50u);

    // Test values which are not set
    CPPUNIT_ASSERT(this->config->getUInt("numbernotset") == 0u);
    CPPUNIT_ASSERT(this->config->getUInt("numbernotset", 27u) == 27u);
}

/**
 * Set and Get float values
 */
void dashee::test::Config::testSetAndGetFloat()
{
    // Test int when set as a int
    this->config->set("mynumber", 1986.3432f);
    CPPUNIT_ASSERT(this->config->getFloat("mynumber") == 1986.3432f);
    this->config->set("mynumber", 1991.1238f);
    CPPUNIT_ASSERT(this->config->getFloat("mynumber") == 1991.1238f);
    this->config->set("mynumber", 2013.1236f, false);
    CPPUNIT_ASSERT(this->config->getFloat("mynumber") == 1991.1238f);
    this->config->set("mynumber", 1001.98f);
    CPPUNIT_ASSERT(this->config->getFloat("mynumber") == 1001.98f);

    // Test int when set as a string
    this->config->set("mynumberstring", "10.238");
    CPPUNIT_ASSERT(this->config->getFloat("mynumberstring") == 10.238f);
    this->config->set("mynumberstring", "50.9389");
    CPPUNIT_ASSERT(this->config->getFloat("mynumberstring") == 50.9389f);
    this->config->set("mynumberstring", "999.435", false);
    CPPUNIT_ASSERT(this->config->getFloat("mynumberstring") == 50.9389f);

    // Test values which are not set
    CPPUNIT_ASSERT(this->config->getFloat("numbernotset") == 0.0f);
    CPPUNIT_ASSERT(this->config->getFloat("numbernotset", 27.65f) == 27.65f);
}

/**
 *
 */
void dashee::test::Config::testReadConfig()
{

}

/**
 *
 */
void dashee::test::Config::testReadConfigWithErrors()
{

}

/**
 * Simple test to ensure that the size returned
 * is correct in all set and get cases.
 */
void dashee::test::Config::testSize()
{
    CPPUNIT_ASSERT(this->config->size() == 0);

    // Set two key values and test there return
    this->config->set("myfirstkey", "Hello world");
    this->config->set("mysecondkey", "Hello Universe!");
    CPPUNIT_ASSERT(this->config->size() == 2);

    // Overwrite an existing value and test the return
    this->config->set("myfirstkey", "Hello earth");
    CPPUNIT_ASSERT(this->config->size() == 2);

    // Test with Overwriting disabled
    this->config->set("myfirstkey", "Hello Ladies", false);
    this->config->set("mythirdkey", "Hello Gentelmen", false);
    CPPUNIT_ASSERT(this->config->size() == 3);

    // test a value that is not set and has no default, should
    // return NULL.
    this->config->get("keythatisnotset");
    CPPUNIT_ASSERT(this->config->size() == 3);

    // test a value that is not set but has a default
    this->config->get("keythatisnotset", "Hello Mars");
    CPPUNIT_ASSERT(this->config->size() == 3);
}

/**
 * A test to ensure that cleanup is done properly
 * and the size reflects this.
 */
void dashee::test::Config::testCleanUp()
{
    config->clear();
    CPPUNIT_ASSERT(this->config->size() == 0);

    this->config->set("myfirstkey", "Hello world");
    this->config->set("mysecondkey", "Hello Universe!");
    CPPUNIT_ASSERT(this->config->size() == 2);

    config->clear();
    CPPUNIT_ASSERT(this->config->size() == 0);
}

/**
 * Cheack invalid key throws an exception
 */
void dashee::test::Config::testInvalidKeyException()
{
    this->config->set("hello world", "tonigh");
}

/**
 * Clean up
 */
void dashee::test::Config::tearDown()
{
    delete config;
}
