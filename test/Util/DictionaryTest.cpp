#include "Util/Dictionary.h"
#include "Config/Configuration.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Util;
using namespace Eihire::Config;
using namespace Eihire::TestUtils;

class DictionaryTest : public ::testing::Test {
protected:
    // 試験開始時に一回だけ実行
    static void SetUpTestCase()
    {
        std::filesystem::path p = getTestDataPath();
        p.append("elog.properties");
        Configuration &config = Configuration::getConfiguration();
        config.addPropertiesFile(p.generic_string());
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

TEST_F(DictionaryTest, Dictionary_001)
{
    Dictionary<int, std::string> d;
    d.set(1, "ONE");
    d.set(2, "TWO");
    d.set(3, "THREE");
    d.set(2, "SECOND");

    ASSERT_EQ("ONE", d.get(1));
    ASSERT_EQ("SECOND", d.get(2));
    ASSERT_EQ("THREE", d.get(3));

    Dictionary<std::string, std::string> sd;
    sd.set("1", "ONE");
    sd.set("2", "TWO");
    sd.set("3", "THREE");

    JSON j;
    j.set("3", std::string{"THIRD"});
    // j.set("9", 99);
    // JSON j2;
    // j2 = j;
    // ASSERT_EQ("THIRD", j.getString("3"));
    // ASSERT_EQ("THIRD", j2.getString("3"));
    // ASSERT_EQ(99, j.getInt("9"));
    // ASSERT_EQ(99, j2.getInt("9"));
}

TEST_F(DictionaryTest, JSON_setT_001)
{
    JSON j;
    j.set("int", 99);
    j.set("double", 3.14);
    j.set("string", "あいうえお");
    j.set("bool", true);
    j.set("null", nullptr);
    j.set("json", JSON{});
    //j.set("float", float{0.9});
    //j.set("array", std::vector{1, 2, 3});

    ASSERT_EQ(99, j.getInt("int"));
    ASSERT_DOUBLE_EQ(3.14, j.getDouble("double"));
    ASSERT_STREQ("あいうえお", j.getString("string").c_str());
    ASSERT_TRUE(j.getBool("bool"));
    ASSERT_EQ(nullptr, j.getNull("null"));

    // for(auto& p : j.elements())
    // {
    //     std::cout << p.second.type().name() << std::endl;
    // }
}