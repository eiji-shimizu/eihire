#include "Logging/Logger.h"
#include "Config/Configuration.h"
#include "Util/Finally.h"
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
    Logger logger("testlog", Logger::Level::DEBUG, Logger::Channel::CONSOLE);
    logger.E_INFO("Logger_level_001:test message");
}

TEST_F(LoggerTest, Logger_channel_002)
{
    Logger logger("testlog", Logger::Level::DEBUG, Logger::Channel::FILE);
    logger.E_INFO("Logger_channel_002:test message");
}

TEST_F(LoggerTest, Logger_level_001)
{
    Logger logger("testlog", Logger::Level::TRACE, Logger::Channel::FILE);
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

TEST_F(LoggerTest, Logger_getLogger_001)
{
    Logger &logger1 = Logger::getLogger<Configuration>();
    Logger &logger2 = Logger::getLogger<Eihire::Util::Finally>();
    Logger &logger3 = Logger::getLogger<Configuration>();
    Logger &logger4 = Logger::getLogger<std::string>();
    Logger &logger5 = Logger::getLogger<std::string>();
    Logger &logger6 = Logger::getLogger<Eihire::Util::Finally>();

    ASSERT_EQ(&logger1, &logger3);
    ASSERT_EQ(&logger2, &logger6);
    ASSERT_EQ(&logger4, &logger5);
    ASSERT_NE(&logger1, &logger2);
    ASSERT_NE(&logger2, &logger4);
    ASSERT_NE(&logger4, &logger1);
}
