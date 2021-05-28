#include "Configuration/Configuration.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Configuration;
using namespace Eihire::TestUtils;

// シングルトンのオブジェクト取得
TEST(ConfigurationTest, Configuration_getConfiguration_001)
{
    std::filesystem::path p = getTestDataPath();
    p.append("Eihire.properties");
    Configuration &config1 = Configuration::getConfiguration(p.generic_string());
    Configuration &config2 = Configuration::getConfiguration(p.generic_string());
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
    std::filesystem::path p = getTestDataPath();
    p.append("Eihire.properties");
    Configuration &config = Configuration::getConfiguration(p.generic_string());
    ASSERT_STREQ("あいうえお", config.get("1").c_str());
    ASSERT_STREQ("XYZ_@", config.get("2").c_str());
    ASSERT_STREQ("c++ programming", config.get("abcd").c_str());
    ASSERT_STREQ("abcdefghijklmnopqrstuvwxyz", config.get("004").c_str());
}

// 存在しないキーで値取得でout_of_range例外を投げる
TEST(ConfigurationTest, Configuration_get_002)
{
    std::filesystem::path p = getTestDataPath();
    p.append("Eihire.properties");
    Configuration &config = Configuration::getConfiguration(p.generic_string());
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
