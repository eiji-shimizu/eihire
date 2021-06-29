#include "Program/Program.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Program;
using namespace Eihire::TestUtils;

class ProgramTest : public ::testing::Test {
protected:
    // 試験開始時に一回だけ実行
    static void SetUpTestCase()
    {
        Program::initialize(getTestDataPath());
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

TEST_F(ProgramTest, Program_instance_001)
{
    Program &insA = Program::instance();
    Program &insB = Program::instance();
    if (&insA == &insB) {
        SUCCEED();
    }
    else {
        FAIL() << "We shouldn't get here.";
    }
}

TEST_F(ProgramTest, Program_config_001)
{
    Program &ins = Program::instance();
    ASSERT_STREQ("あいうえお", ins.config().get("key1").c_str());
    ASSERT_STREQ("XYZ_@", ins.config().get("key2").c_str());
    ASSERT_STREQ("c++ programming", ins.config().get("key3").c_str());
    ASSERT_STREQ("abcdefghijklmnopqrstuvwxyz", ins.config().get("key4").c_str());
}

TEST_F(ProgramTest, Program_logger_001)
{
    Program &ins = Program::instance();
    ins.logger().E_TRACE("Program_instance_001:test message");
    ins.logger().E_DEBUG("Program_instance_001:test message");
    ins.logger().E_INFO("Program_instance_001:test message");
    ins.logger().E_WARN("Program_instance_001:test message");
    ins.logger().E_ERROR("Program_instance_001:test message");
    ins.logger().E_FATAL("Program_instance_001:test message");
}
