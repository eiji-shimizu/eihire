#include "Logging/Logger.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Logging;
using namespace Eihire::TestUtils;

class LoggerTest : public ::testing::Test
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

//
TEST_F(LoggerTest, Logger_info_001)
{
    Logger logger(Logger::Level::INFO, Logger::Channel::FILE, "testlog");
    logger.info("test abcdefghijklmnopqrstuvwxyz");
    SUCCEED();
}