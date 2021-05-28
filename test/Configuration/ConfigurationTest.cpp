#include "Configuration/Configuration.h"

#include "gtest/gtest.h"

using namespace Eihire::Configuration;

const std::string TEST_DATA_DIR = "../../../test/testdata/";

// シングルトンのオブジェクト取得
TEST(ConfigurationTest, Configuration_getConfiguration_001)
{
    Configuration &config1 = Configuration::getConfiguration(TEST_DATA_DIR + "Eihire.properties");
    Configuration &config2 = Configuration::getConfiguration(TEST_DATA_DIR + "Eihire.properties");
    if (&config1 == &config2)
    {
        SUCCEED();
    }
    else
    {
        FAIL() << "We shouldn't get here.";
    }
}

// 値取得
TEST(ConfigurationTest, Configuration_get_001)
{
    Configuration &config = Configuration::getConfiguration(TEST_DATA_DIR + "Eihire.properties");
    ASSERT_STREQ("あいうえお", config.get("1").c_str());
    ASSERT_STREQ("XYZ_@", config.get("2").c_str());
    ASSERT_STREQ("c++ programming", config.get("abcd").c_str());
    ASSERT_STREQ("abcdefghijklmnopqrstuvwxyz", config.get("004").c_str());
}

// 存在しないキーで値取得でout_of_range例外を投げる
TEST(ConfigurationTest, Configuration_get_002)
{
    Configuration &config = Configuration::getConfiguration(TEST_DATA_DIR + "Eihire.properties");
    try
    {
        config.get("002");
        FAIL() << "We shouldn't get here.";
    }
    catch (const std::out_of_range &e)
    {
        SUCCEED();
    }
    catch (...)
    {
        FAIL() << "We shouldn't get here.";
    }

    try
    {
        config.get("#002");
        FAIL() << "We shouldn't get here.";
    }
    catch (const std::out_of_range &e)
    {
        SUCCEED();
    }
    catch (...)
    {
        FAIL() << "We shouldn't get here.";
    }

    try
    {
        config.get("003");
        FAIL() << "We shouldn't get here.";
    }
    catch (const std::out_of_range &e)
    {
        SUCCEED();
    }
    catch (...)
    {
        FAIL() << "We shouldn't get here.";
    }

    try
    {
        config.get("!003");
        FAIL() << "We shouldn't get here.";
    }
    catch (const std::out_of_range &e)
    {
        SUCCEED();
    }
    catch (...)
    {
        FAIL() << "We shouldn't get here.";
    }
}
