#include "Logging/Logger.h"
#include "Configuration/Configuration.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Logging;
using namespace Eihire::Configuration;
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
    logger.trace("Logger_constructor_001:test message");
    logger.debug("Logger_constructor_001:test message");
    logger.info("Logger_constructor_001:test message");
    logger.warn("Logger_constructor_001:test message");
    logger.error("Logger_constructor_001:test message");
    logger.fatal("Logger_constructor_001:test message");
}

TEST_F(LoggerTest, Logger_channel_001)
{
    Logger logger(Logger::Level::DEBUG, Logger::Channel::CONSOLE, "testlog");
    logger.info("Logger_level_001:test message");
}

TEST_F(LoggerTest, Logger_channel_002)
{
    Logger logger(Logger::Level::DEBUG, Logger::Channel::FILE, "testlog");
    logger.info("Logger_channel_002:test message");
}

TEST_F(LoggerTest, Logger_level_001)
{
    Logger logger(Logger::Level::TRACE, Logger::Channel::FILE, "testlog");
    logger.trace("Logger_level_001:TRACE Level");
    logger.debug("Logger_level_001:TRACE Level");
    logger.info("Logger_level_001:TRACE Level");
    logger.warn("Logger_level_001:TRACE Level");
    logger.error("Logger_level_001:TRACE Level");
    logger.fatal("Logger_level_001:TRACE Level");

    logger.setLevel(Logger::Level::DEBUG);
    logger.trace("Logger_level_001:DEBUG Level");
    logger.debug("Logger_level_001:DEBUG Level");
    logger.info("Logger_level_001:DEBUG Level");
    logger.warn("Logger_level_001:DEBUG Level");
    logger.error("Logger_level_001:DEBUG Level");
    logger.fatal("Logger_level_001:DEBUG Level");

    logger.setLevel(Logger::Level::INFO);
    logger.trace("Logger_level_001:INFO Level");
    logger.debug("Logger_level_001:INFO Level");
    logger.info("Logger_level_001:INFO Level");
    logger.warn("Logger_level_001:INFO Level");
    logger.error("Logger_level_001:INFO Level");
    logger.fatal("Logger_level_001:INFO Level");

    logger.setLevel(Logger::Level::WARN);
    logger.trace("Logger_level_001:WARN Level");
    logger.debug("Logger_level_001:WARN Level");
    logger.info("Logger_level_001:WARN Level");
    logger.warn("Logger_level_001:WARN Level");
    logger.error("Logger_level_001:WARN Level");
    logger.fatal("Logger_level_001:WARN Level");

    logger.setLevel(Logger::Level::ERROR);
    logger.trace("Logger_level_001:ERROR Level");
    logger.debug("Logger_level_001:ERROR Level");
    logger.info("Logger_level_001:ERROR Level");
    logger.warn("Logger_level_001:ERROR Level");
    logger.error("Logger_level_001:ERROR Level");
    logger.fatal("Logger_level_001:ERROR Level");

    logger.setLevel(Logger::Level::FATAL);
    logger.trace("Logger_level_001:FATAL Level");
    logger.debug("Logger_level_001:FATAL Level");
    logger.info("Logger_level_001:FATAL Level");
    logger.warn("Logger_level_001:FATAL Level");
    logger.error("Logger_level_001:FATAL Level");
    logger.fatal("Logger_level_001:FATAL Level");
}
