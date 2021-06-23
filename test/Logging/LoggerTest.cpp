#include "Logging/Logger.h"
#include "Config/Configuration.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Logging;
using namespace Eihire::Config;
using namespace Eihire::TestUtils;

class LoggerTest : public ::testing::Test
{
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

TEST_F(LoggerTest, Logger_constructor_001)
{
    Logger logger("testlog");
    logger.E_TRACE("Logger_constructor_001:test message");
    logger.E_DEBUG("Logger_constructor_001:test message");
    logger.E_INFO("Logger_constructor_001:test message");
    logger.E_WARN("Logger_constructor_001:test message");
    logger.E_ERROR("Logger_constructor_001:test message");
    logger.E_FATAL("Logger_constructor_001:test message");
}

TEST_F(LoggerTest, Logger_channel_001)
{
    Logger logger(Logger::Level::DEBUG, Logger::Channel::CONSOLE, "testlog");
    logger.E_INFO("Logger_level_001:test message");
}

TEST_F(LoggerTest, Logger_channel_002)
{
    Logger logger(Logger::Level::DEBUG, Logger::Channel::FILE, "testlog");
    logger.E_INFO("Logger_channel_002:test message");
}

TEST_F(LoggerTest, Logger_level_001)
{
    Logger logger(Logger::Level::TRACE, Logger::Channel::FILE, "testlog");
    logger.E_TRACE("Logger_level_001:TRACE Level");
    logger.E_DEBUG("Logger_level_001:TRACE Level");
    logger.E_INFO("Logger_level_001:TRACE Level");
    logger.E_WARN("Logger_level_001:TRACE Level");
    logger.E_ERROR("Logger_level_001:TRACE Level");
    logger.E_FATAL("Logger_level_001:TRACE Level");

    logger.setLevel(Logger::Level::DEBUG);
    logger.E_TRACE("Logger_level_001:DEBUG Level");
    logger.E_DEBUG("Logger_level_001:DEBUG Level");
    logger.E_INFO("Logger_level_001:DEBUG Level");
    logger.E_WARN("Logger_level_001:DEBUG Level");
    logger.E_ERROR("Logger_level_001:DEBUG Level");
    logger.E_FATAL("Logger_level_001:DEBUG Level");

    logger.setLevel(Logger::Level::INFO);
    logger.E_TRACE("Logger_level_001:INFO Level");
    logger.E_DEBUG("Logger_level_001:INFO Level");
    logger.E_INFO("Logger_level_001:INFO Level");
    logger.E_WARN("Logger_level_001:INFO Level");
    logger.E_ERROR("Logger_level_001:INFO Level");
    logger.E_FATAL("Logger_level_001:INFO Level");

    logger.setLevel(Logger::Level::WARN);
    logger.E_TRACE("Logger_level_001:WARN Level");
    logger.E_DEBUG("Logger_level_001:WARN Level");
    logger.E_INFO("Logger_level_001:WARN Level");
    logger.E_WARN("Logger_level_001:WARN Level");
    logger.E_ERROR("Logger_level_001:WARN Level");
    logger.E_FATAL("Logger_level_001:WARN Level");

    logger.setLevel(Logger::Level::ERROR);
    logger.E_TRACE("Logger_level_001:ERROR Level");
    logger.E_DEBUG("Logger_level_001:ERROR Level");
    logger.E_INFO("Logger_level_001:ERROR Level");
    logger.E_WARN("Logger_level_001:ERROR Level");
    logger.E_ERROR("Logger_level_001:ERROR Level");
    logger.E_FATAL("Logger_level_001:ERROR Level");

    logger.setLevel(Logger::Level::FATAL);
    logger.E_TRACE("Logger_level_001:FATAL Level");
    logger.E_DEBUG("Logger_level_001:FATAL Level");
    logger.E_INFO("Logger_level_001:FATAL Level");
    logger.E_WARN("Logger_level_001:FATAL Level");
    logger.E_ERROR("Logger_level_001:FATAL Level");
    logger.E_FATAL("Logger_level_001:FATAL Level");
}
