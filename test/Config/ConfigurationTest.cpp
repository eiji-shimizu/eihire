#include "Config/Configuration.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Config;
using namespace Eihire::TestUtils;

class ConfigurationTest : public ::testing::Test
{
protected:
    // 試験開始時に一回だけ実行
    static void SetUpTestCase()
    {
        std::filesystem::path p = getTestDataPath();
        p.append("Eihire.properties");
        Configuration::getConfiguration(p.generic_string());
    }

    // 試験終了時に一回だけ実行
    static void TearDownTestCase()
    {
    }

    // 各テストケース実行前に実行
    virtual void SetUp()
    {
    }

    // 各テストケース実行後に実行
    virtual void TearDown()
    {
    }
};

// シングルトンのオブジェクト取得
TEST_F(ConfigurationTest, Configuration_getConfiguration_001)
{
    Configuration &config1 = Configuration::getConfiguration();
    Configuration &config2 = Configuration::getConfiguration();
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
TEST_F(ConfigurationTest, Configuration_get_001)
{
    Configuration &config = Configuration::getConfiguration();
    ASSERT_STREQ("あいうえお", config.get("eihire1").c_str());
    ASSERT_STREQ("XYZ_@", config.get("eihire2").c_str());
    ASSERT_STREQ("c++ programming", config.get("abcd").c_str());
    ASSERT_STREQ("abcdefghijklmnopqrstuvwxyz", config.get("eihire004").c_str());
}

// 存在しないキーで値取得でout_of_range例外を投げる
TEST_F(ConfigurationTest, Configuration_get_002)
{
    Configuration &config = Configuration::getConfiguration();
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

// ファイル名を指定して値取得
TEST_F(ConfigurationTest, Configuration_get_003)
{
    Configuration &config = Configuration::getConfiguration();
    std::filesystem::path p = getTestDataPath();
    p = p.append("other.properties");
    config.addPropertiesFile(p.generic_string());

    ASSERT_STREQ("あいうえお", config.get("Eihire.properties", "eihire1").c_str());
    ASSERT_STREQ("XYZ_@", config.get("Eihire.properties", "eihire2").c_str());
    ASSERT_STREQ("c++ programming", config.get("Eihire.properties", "abcd").c_str());
    ASSERT_STREQ("abcdefghijklmnopqrstuvwxyz", config.get("Eihire.properties", "eihire004").c_str());

    ASSERT_STREQ("かきくけこ", config.get("other.properties", "other1").c_str());
    ASSERT_STREQ("here there everywhere", config.get("other.properties", "other2").c_str());
    ASSERT_STREQ("システム開発", config.get("other.properties", "other3").c_str());
    ASSERT_STREQ("ABCDEFG", config.get("other.properties", "other4").c_str());
}

// ファイル名を指定して存在しないキーで値取得
TEST_F(ConfigurationTest, Configuration_get_004)
{
    Configuration &config = Configuration::getConfiguration();
    std::filesystem::path p = getTestDataPath();
    p = p.append("other.properties");
    config.addPropertiesFile(p.generic_string());

    try
    {
        config.get("other.properties", "eihire1");
        FAIL() << "We shouldn't get here.";
    }
    catch (const std::out_of_range &e)
    {
        SUCCEED();
    }
    try
    {
        config.get("Eihire.properties", "other1");
        FAIL() << "We shouldn't get here.";
    }
    catch (const std::out_of_range &e)
    {
        SUCCEED();
    }
}
