#include "Logging/Logger.h"
#include "Configuration/Configuration.h"
#include "Exception/Exception.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace Eihire::Configuration;

namespace Eihire::Logging
{
    const std::string Logger::PROPERTIES_FILE_NAME = "elog.properties";

    namespace
    {
        Logger::Level convertToLevel(const std::string &level)
        {
            if (level == "TRACE")
                return Logger::Level::TRACE;
            if (level == "DEBUG")
                return Logger::Level::DEBUG;
            if (level == "INFO")
                return Logger::Level::INFO;
            if (level == "WARN")
                return Logger::Level::WARN;
            if (level == "ERROR")
                return Logger::Level::ERROR;
            if (level == "FATAL")
                return Logger::Level::FATAL;

            // デフォルトはINFO
            return Logger::Level::INFO;
        }

        Logger::Channel convertToChannel(const std::string &channel)
        {
            if (channel == "CONSOLE")
                return Logger::Channel::CONSOLE;
            if (channel == "FILE")
                return Logger::Channel::FILE;

            // デフォルトはCONSOLE
            return Logger::Channel::CONSOLE;
        }

    } // namespace

    Logger::Logger(const std::string &name)
        : level_{convertToLevel(::Configuration::getConfiguration().find(PROPERTIES_FILE_NAME, "LOG_LEVEL"))},
          channel_{convertToChannel(::Configuration::getConfiguration().find(PROPERTIES_FILE_NAME, "CHANNEL"))},
          name_{name},
          ofs_{}
    {
        if (channel_ == Channel::FILE)
        {
            std::string outputFile = ::Configuration::getConfiguration().find(PROPERTIES_FILE_NAME, "OUTPUT_PATH");
            if (outputFile == "")
            {
                outputFile = ::Configuration::getConfiguration().find(PROPERTIES_FILE_NAME, "OUTPUT_FILE");
            }
            if (outputFile == "")
                outputFile = "eihireoutput.log";

            ofs_.open(outputFile, std::ios_base::out | std::ios_base::app);

            if (!ofs_)
            {
                std::ostringstream oss("");
                oss << "can't open file '" << outputFile << "'.";
                throw Exception::FileCannotOpenException(oss.str());
            }
        }
    }

    Logger::Logger(const Level level, const std::string &name)
        : level_{level},
          channel_{Channel::CONSOLE},
          name_{name},
          ofs_{}
    {
        // noop
    }

    Logger::Logger(const Level level, const Channel channel, const std::string &name)
        : level_{level},
          channel_{channel},
          name_{name},
          ofs_{}
    {
        if (channel_ == Channel::FILE)
        {
            ofs_.open("eihireoutput.log", std::ios_base::out | std::ios_base::app);
        }
    }

    Logger::~Logger()
    {
        if (ofs_.is_open())
        {
            ofs_.close();
        }
    }

    void Logger::setLevel(Level level)
    {
        level_ = level;
    }

    void Logger::fatal(const std::string &message)
    {
        if (level_ <= Level::FATAL)
            write("FATAL", message);
    }
    void Logger::error(const std::string &message)
    {
        if (level_ <= Level::ERROR)
            write("ERROR", message);
    }
    void Logger::warn(const std::string &message)
    {
        if (level_ <= Level::WARN)
            write("WARN", message);
    }
    void Logger::info(const std::string &message)
    {
        if (level_ <= Level::INFO)
            write("INFO", message);
    }
    void Logger::debug(const std::string &message)
    {
        if (level_ <= Level::DEBUG)
            write("DEBUG", message);
    }
    void Logger::trace(const std::string &message)
    {
        if (level_ <= Level::TRACE)
            write("TRACE", message);
    }

    void Logger::write(const std::string &level, const std::string &message)
    {
        std::ostringstream oss("");
        oss << "[" << level << "]:" << message << std::endl;

        // 出力先に応じて参照先を格納するポインタ
        std::ostream *pos = nullptr;
        if (channel_ == Channel::CONSOLE)
            pos = &std::cout;
        else if (channel_ == Channel::FILE)
            pos = &ofs_;

        *pos << oss.str();
    }

} // namespace Eihire::Logging