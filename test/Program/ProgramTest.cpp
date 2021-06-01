#include "Program/Program.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Program;
using namespace Eihire::TestUtils;

class ProgramTest : public ::testing::Test
{
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
    Program &ins = Program::instance();
    ins.logger().E_TRACE("Program_instance_001:test message");
    ins.logger().E_DEBUG("Program_instance_001:test message");
    ins.logger().E_INFO("Program_instance_001:test message");
    ins.logger().E_WARN("Program_instance_001:test message");
    ins.logger().E_ERROR("Program_instance_001:test message");
    ins.logger().E_FATAL("Program_instance_001:test message");
}
