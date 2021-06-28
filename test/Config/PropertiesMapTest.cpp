#include "Config/PropertiesMap.h"
#include "Exception/Exception.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

#include <string>

using namespace Eihire::Config;
using namespace Eihire::Exception;
using namespace Eihire::TestUtils;

// プロパティファイル名が設定していない状態でのロード処理
TEST(PropertiesMapTest, PropertiesMap_load_001)
{
    PropertiesMap p;
    try {
        p.load();
    }
    catch (const FileCannotOpenException &e) {
        SUCCEED();
    }
    catch (const std::exception &e) {
        FAIL() << "We shouldn't get here.";
    }
}

// ロード処理
TEST(PropertiesMapTest, PropertiesMap_load_002)
{
    std::filesystem::path pt = getTestDataPath();
    pt.append("Eihire.properties");
    PropertiesMap p(pt.generic_string());
    p.load();
    SUCCEED();
}

// 値取得
TEST(PropertiesMapTest, PropertiesMap_get_001)
{
    std::filesystem::path pt = getTestDataPath();
    pt.append("Eihire.properties");
    PropertiesMap p(pt.generic_string());
    p.load();
    ASSERT_STREQ("あいうえお", p.get("eihire1").c_str());
    ASSERT_STREQ("XYZ_@", p.get("eihire2").c_str());
    ASSERT_STREQ("c++ programming", p.get("abcd").c_str());
    ASSERT_STREQ("abcdefghijklmnopqrstuvwxyz", p.get("eihire004").c_str());
}

// 存在しないキーで値取得
TEST(PropertiesMapTest, PropertiesMap_get_002)
{
    std::filesystem::path pt = getTestDataPath();
    pt.append("Eihire.properties");
    PropertiesMap p(pt.generic_string());
    p.load();
    try {
        p.get("002");
        p.get("#002");
        p.get("003");
        p.get("!003");
    }
    catch (const std::out_of_range &e) {
        SUCCEED();
    }
    catch (...) {
        FAIL() << "We shouldn't get here.";
    }
}