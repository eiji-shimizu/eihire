#include "Util/Dictionary.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Util;
using namespace Eihire::TestUtils;

class DictionaryTest : public ::testing::Test
{
protected:
    // 試験開始時に一回だけ実行
    static void SetUpTestCase()
    {
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
    j.set("3", "THIRD");
    j.set("9", 99);
    JSON j2;
    j2 = j;
    ASSERT_EQ("THIRD", j.getString("3"));
    ASSERT_EQ("THIRD", j2.getString("3"));
    ASSERT_EQ(99, j.getInt("9"));
    ASSERT_EQ(99, j2.getInt("9"));
}