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
    this->config->set("my-second-key", "Hello Universe!");
    CPPUNIT_ASSERT(
            strcmp(this->config->get("my-second-key"), "Hello Universe!") == 0
        );
    this->config->set("my-second-key", "Hello earth");
    CPPUNIT_ASSERT(
            strcmp(this->config->get("my-second-key"), "Hello earth") == 0
        );
    this->config->set("my-second-key", "Hello Ladies", false);
    CPPUNIT_ASSERT(
            strcmp(this->config->get("my-second-key"), "Hello earth") == 0
        );

    // test a value that is not set and has no default, should
    // return NULL. If ia default is provided ensure the default works
    CPPUNIT_ASSERT(
            this->config->get("keythatisnotset") == NULL
        );
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("keythatisnotset", "Hello Mars"), 
                "Hello Mars"
            ) == 0
        );

    // Ensure that dashes work in the system
    this->config->set("dashed-key-value", "soo dashing");
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("dashed-key-value"), 
                "soo dashing"
            ) == 0
        );

    // Ensure that hyphens work in the system
    this->config->set("dashed_key_value", "soo hyphenated");
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("dashed_key_value"), 
                "soo hyphenated"
            ) == 0
        );
    
    // Ensure that ending number keys work in the system
    this->config->set("numbervalue7", "soo lucky");
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("numbervalue7"), 
                "soo lucky"
            ) == 0
        );
    this->config->set("numbervalue314", "soo pi");
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("numbervalue314"), 
                "soo pi"
            ) == 0
        );

    // Ensure number and hyphens work together
    this->config->set("crazy_key-value1234", "soo crazy");
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("crazy_key-value1234"), 
                "soo crazy"
            ) == 0
        );
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
 * Test the setting of the key, and testing weather or not the isSetKey function
 * behaves acoordingly
 */
void dashee::test::Config::testIsKeySet()
{
    CPPUNIT_ASSERT(this->config->isKeySet("boobies") == false);
    this->config->set("testing", "sadfasfasffasd");
    CPPUNIT_ASSERT(this->config->isKeySet("testing") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("boobies") == false);
}

/**
 * 
 */
void dashee::test::Config::testReadConfig()
{
    std::stringstream ss;
    ss << Config::directoryPath << "/config.conf";
    this->config->read(ss.str().c_str());
    
    //this->config->print();

    CPPUNIT_ASSERT(this->config->isKeySet("key") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("space_key") == true);
    
    CPPUNIT_ASSERT(this->config->isKeySet("leading_space_key1") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("leading_space_key2") == true);

    CPPUNIT_ASSERT(this->config->isKeySet("double_quote_string") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("double_quote_string_space") == true);
    CPPUNIT_ASSERT(
            this->config->isKeySet("double_quote_missing_lead") == false
        );
    CPPUNIT_ASSERT(
            this->config->isKeySet("double_quote_missing_trail1") == true
        );
    CPPUNIT_ASSERT(
            this->config->isKeySet("double_quote_missing_trail2") == true
        );
    CPPUNIT_ASSERT(
            this->config->isKeySet("double_quote_and_single_quote") == true
        );
    CPPUNIT_ASSERT(this->config->isKeySet("double_quote_toomany1") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("double_quote_toomany2") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("double_quote_toomany3") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("double_quote_escape1") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("double_quote_escape2") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("double_quote_escape3") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("double_quote_escape4") == false);

    CPPUNIT_ASSERT(this->config->isKeySet("single_quote_string") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("single_quote_string_space") == true);
    CPPUNIT_ASSERT(
            this->config->isKeySet("single_quote_missing_lead") == false
        );
    CPPUNIT_ASSERT(
            this->config->isKeySet("single_quote_missing_trail1") == true
        );
    CPPUNIT_ASSERT(
            this->config->isKeySet("single_quote_missing_trail2") == true
        );
    CPPUNIT_ASSERT(
            this->config->isKeySet("single_quote_and_double_quote") == true
        );
    CPPUNIT_ASSERT(this->config->isKeySet("single_quote_toomany1") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("single_quote_toomany2") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("single_quote_toomany3") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("single_quote_escape1") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("single_quote_escape2") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("single_quote_escape3") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("single_quote_escape4") == false);
    
    CPPUNIT_ASSERT(this->config->isKeySet("escape1") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("escape2") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("escape3") == true);
    
    CPPUNIT_ASSERT(this->config->isKeySet("quotes_mismatches_double") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("quotes_mismatches_single") == true);
    
    CPPUNIT_ASSERT(this->config->isKeySet("overwritten") == true);
    
    CPPUNIT_ASSERT(this->config->isKeySet("big_value") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("big_value_with_quotes") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("big_value_overlimit") == false);
    CPPUNIT_ASSERT(
            this->config->isKeySet("big_value_overlimit_with_quotes") == false
        );
    
    CPPUNIT_ASSERT(this->config->isKeySet("number1") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("number2") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("number3") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("number4") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("number5") == true);
    
    CPPUNIT_ASSERT(this->config->isKeySet("pi1") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("pi2") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("pi3") == false);
    CPPUNIT_ASSERT(this->config->isKeySet("pi4") == false);
    
    CPPUNIT_ASSERT(this->config->isKeySet("1234") == false);
    CPPUNIT_ASSERT(this->config->isKeySet("-key") == false);
    CPPUNIT_ASSERT(this->config->isKeySet("key-") == false);
    CPPUNIT_ASSERT(this->config->isKeySet("key_no_equalsign") == false);
    CPPUNIT_ASSERT(this->config->isKeySet("invalid key with space") == false);
    CPPUNIT_ASSERT(
            this->config->isKeySet(
                "big_keybig_key_toobigtoobigtoobigtoobigtoobigendendend"
            ) == false
        );
    CPPUNIT_ASSERT(this->config->isKeySet("key_no_value") == false);
    CPPUNIT_ASSERT(this->config->isKeySet("double--dash") == false);
    CPPUNIT_ASSERT(this->config->isKeySet("double__underscore") == false);
    CPPUNIT_ASSERT(this->config->isKeySet("double_-mix") == false);
  
    CPPUNIT_ASSERT(this->config->isKeySet("really-crazy_VALID-value1") == true);
    CPPUNIT_ASSERT(this->config->isKeySet("really-crazy_VALID-value2") == true);

    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("key"), 
                "value"
            ) == 0
        );

    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("space_key"), 
                "value"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("leading_space_key1"), 
                "should work"
            ) == 0
        );
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("leading_space_key2"), 
                "why"
            ) == 0
        );
    
    // DOUBLE QUOTES
    CPPUNIT_ASSERT(
            strcmp(this->config->get("double_quote_string"), "value") == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(this->config->get("double_quote_string_space"), "value") == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("double_quote_missing_trail1"), 
                "value\""
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("double_quote_missing_trail2"), 
                "value\"ladies\""
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("double_quote_and_single_quote"), 
                "lad'i'es"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("double_quote_toomany1"), 
                "va"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("double_quote_toomany2"), 
                "va"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("double_quote_toomany3"), 
                "va"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(this->config->get("double_quote_escape1"), "va\"lu\"e") == 0
        );
    CPPUNIT_ASSERT(
            strcmp(this->config->get("double_quote_escape2"), "value") == 0
        );
    CPPUNIT_ASSERT(
            strcmp(this->config->get("double_quote_escape3"), "va\\lue") == 0
        );
    
    // SINGLE QUOTE
    CPPUNIT_ASSERT(
            strcmp(this->config->get("single_quote_string"), "value") == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(this->config->get("single_quote_string_space"), "value") == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("single_quote_missing_trail1"), 
                "value'"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("single_quote_missing_trail2"), 
                "value'ladies'"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("single_quote_and_double_quote"), 
                "lad\"i\"es"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("single_quote_toomany1"), 
                "va"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("single_quote_toomany2"), 
                "va"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("single_quote_toomany3"), 
                "va"
            ) == 0
        );
    
    CPPUNIT_ASSERT(
            strcmp(this->config->get("single_quote_escape1"), "va'lu'e") == 0
        );
    CPPUNIT_ASSERT(
            strcmp(this->config->get("single_quote_escape2"), "value") == 0
        );
    CPPUNIT_ASSERT(
            strcmp(this->config->get("single_quote_escape3"), "va\\lue") == 0
        );
    
    // ESCAPE
    CPPUNIT_ASSERT(strcmp(this->config->get("escape1"), "va\nlue") == 0);
    CPPUNIT_ASSERT(strcmp(this->config->get("escape2"), "va\\") == 0);
    CPPUNIT_ASSERT(strcmp(this->config->get("escape3"), "va\\lue") == 0);
    
    // QUOTES MISMATCH
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("quotes_mismatches_double"), 
                "val'ue"
            ) == 0
        );
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("quotes_mismatches_single"), 
                "val\"ue"
            ) == 0
        );

    // BIG VALUES
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("big_value"), 
                "hello to the world of tomorrow topguns!"
            ) == 0
        );
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("big_value_with_quotes"), 
                "hello to the world of tomorrow topguns!"
            ) == 0
        );
    
    // OVERWRITES
    CPPUNIT_ASSERT(strcmp(this->config->get("overwritten"), "second") == 0);
    
    // NUMBER
    CPPUNIT_ASSERT(strcmp(this->config->get("number1"), "0") == 0);
    CPPUNIT_ASSERT(strcmp(this->config->get("number2"), "-0") == 0);
    CPPUNIT_ASSERT(strcmp(this->config->get("number3"), "123") == 0);
    
    CPPUNIT_ASSERT(strcmp(this->config->get("pi1"), "3.141592653589") == 0);
    CPPUNIT_ASSERT(strcmp(this->config->get("pi2"), "-3.141592653589") == 0);
 
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("really-crazy_VALID-value1"), 
                "This is my \" value so dont bother"
            ) == 0
        );
 
    CPPUNIT_ASSERT(
            strcmp(
                this->config->get("really-crazy_VALID-value2"), 
                "This is my non quoted \" value so    dont bother"
            ) == 0
        );

    CPPUNIT_ASSERT(this->config->size() == 43);
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
 * Cheack invalid key throws an exception
 */
void dashee::test::Config::testInvalidKeyExceptionPreDash()
{
    this->config->set("-hello world", "tonigh");
}

/**
 * Cheack invalid key throws an exception
 */
void dashee::test::Config::testInvalidKeyExceptionPostDash()
{
    this->config->set("hello world-", "tonigh");
}

/**
 * Cheack invalid key throws an exception
 */
void dashee::test::Config::testInvalidKeyExceptionPreHyphen()
{
    this->config->set("_hello world", "tonigh");
}

/**
 * Cheack invalid key throws an exception
 */
void dashee::test::Config::testInvalidKeyExceptionPostHyphen()
{
    this->config->set("hello world_", "tonigh");
}

/**
 * Cheack invalid key throws an exception
 */
void dashee::test::Config::testInvalidKeyExceptionPreNumber()
{
    this->config->set("1hello world", "tonigh");
}

/**
 * Clean up
 */
void dashee::test::Config::tearDown()
{
    delete config;
}

// Default the variable to nothing
char * dashee::test::Config::directoryPath = NULL;
