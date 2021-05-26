#include "PropertiesMap.h"
#include "Exception.h"

#include "gtest/gtest.h"

using namespace Eihire::Configuration;
using namespace Eihire::Exception;

// プロパティファイル名が設定していない状態でのロード処理
TEST(PropertiesMapTest, PropertiesMap_load_001)
{
    PropertiesMap p;
    try
    {
        p.load();
    }
    catch (const FileCannotOpenException &e)
    {
        SUCCEED();
    }
    catch (const std::exception &e)
    {
        FAIL() << "We shouldn't get here.";
    }
}

// ロード処理
TEST(PropertiesMapTest, PropertiesMap_load_002)
{
    PropertiesMap p("Eihire.properties");
    p.load();
    SUCCEED();
}

// 値取得
TEST(PropertiesMapTest, PropertiesMap_get_001)
{
    PropertiesMap p("Eihire.properties");
    p.load();
    ASSERT_STREQ("あいうえお", p.get("1").c_str());
    ASSERT_STREQ("XYZ_@", p.get("2").c_str());
    ASSERT_STREQ("c++ programming", p.get("abcd").c_str());
    ASSERT_STREQ("abcdefghijklmnopqrstuvwxyz", p.get("004").c_str());
}

// 存在しないキーで値取得
TEST(PropertiesMapTest, PropertiesMap_get_002)
{
    PropertiesMap p("Eihire.properties");
    p.load();
    try
    {
        p.get("002");
        p.get("#002");
        p.get("003");
        p.get("!003");
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