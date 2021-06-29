#include "Util/Finally.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Util;
using namespace Eihire::TestUtils;

class FinallyTest : public ::testing::Test
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

TEST_F(FinallyTest, finally_move_constructor_001)
{
    int i = 0;
    {
        ASSERT_EQ(0, i);
        Finally f1{[&i]
                   { ++i; }};
        Finally f2{std::move(f1)};
        ASSERT_FALSE(f1.isValid());
        ASSERT_TRUE(f2.isValid());
        ASSERT_EQ(0, i);
    }
    ASSERT_EQ(1, i);
}

TEST_F(FinallyTest, finally_move_assign_001)
{
    int i = 2;
    {
        ASSERT_EQ(2, i);
        Finally f1{[&i]
                   { i += 5; }};
        Finally f2{[&i]
                   { ++i; }};
        f2 = std::move(f1);
        ASSERT_FALSE(f1.isValid());
        ASSERT_TRUE(f2.isValid());
        Finally f3{[&i]
                   { i = i * i; }};
        f1 = std::move(f3);
        ASSERT_FALSE(f3.isValid());
        ASSERT_TRUE(f1.isValid());
    }
    ASSERT_EQ(49, i);
}

TEST_F(FinallyTest, finally_001)
{
    int i = 0;
    ASSERT_EQ(0, i);
    {
        ASSERT_EQ(0, i);
        Finally f{[&i]
                  { i = 5; }};
        ASSERT_EQ(0, i);
    }
    ASSERT_EQ(5, i);
}

TEST_F(FinallyTest, finally_002)
{
    int i = 0;
    ASSERT_EQ(0, i);
    {
        ASSERT_EQ(0, i);
        Finally f1{[&i]
                   { i = 4; }};
        Finally f2{[&i]
                   { i = 5; }};
        ASSERT_EQ(0, i);
    }
    ASSERT_EQ(4, i);
}

TEST_F(FinallyTest, finally_003)
{
    int i = 0;
    ASSERT_EQ(0, i);
    {
        ASSERT_EQ(0, i);
        Finally f1{[&i]
                   { i = 4; }};
        Finally f2{[&i]
                   { i = 10; }};
        f1 = std::move(f2);
        ASSERT_EQ(0, i);
    }
    ASSERT_EQ(10, i);
}

TEST_F(FinallyTest, finally_004)
{
    int i = 0;
    ASSERT_EQ(0, i);
    {
        ASSERT_EQ(0, i);
        Finally f1{[&i]
                   { i = 4; }};
        Finally f2{[&i]
                   { i = 10; }};
        f2 = std::move(f1);
        ASSERT_EQ(0, i);
    }
    ASSERT_EQ(4, i);
}