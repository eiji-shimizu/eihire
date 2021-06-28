#include "Logging/Logger.h"
#include "Config/Configuration.h"
#include "Exception/Exception.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace Eihire::Config;

namespace Eihire::Logging {

    const std::string Logger::PROPERTIES_FILE_NAME = "elog.properties";

    namespace {

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
        : level_{convertToLevel(Configuration::getConfiguration().find(PROPERTIES_FILE_NAME, "LOG_LEVEL"))},
          channel_{convertToChannel(Configuration::getConfiguration().find(PROPERTIES_FILE_NAME, "CHANNEL"))},
          name_{name},
          ofs_{},
          mt_{}
    {
        initialize();
    }

    Logger::Logger(const std::string &name, const Level level)
        : level_{level},
          channel_{convertToChannel(Configuration::getConfiguration().find(PROPERTIES_FILE_NAME, "CHANNEL"))},
          name_{name},
          ofs_{},
          mt_{}
    {
        initialize();
    }

    Logger::Logger(const std::string &name, const Level level, const Channel channel)
        : level_{level},
          channel_{channel},
          name_{name},
          ofs_{},
          mt_{}
    {
        initialize();
    }

    Logger::~Logger()
    {
        if (ofs_.is_open()) {
            ofs_.close();
        }
    }

    void Logger::setLevel(Level level)
    {
        level_ = level;
    }

    void Logger::fatal(const char *fileName, const char *functionName, uint64_t line, const std::string &message)
    {
        if (level_ <= Level::FATAL)
            write("FATAL", fileName, functionName, line, message);
    }
    void Logger::error(const char *fileName, const char *functionName, uint64_t line, const std::string &message)
    {
        if (level_ <= Level::ERROR)
            write("ERROR", fileName, functionName, line, message);
    }
    void Logger::warn(const char *fileName, const char *functionName, uint64_t line, const std::string &message)
    {
        if (level_ <= Level::WARN)
            write("WARN", fileName, functionName, line, message);
    }
    void Logger::info(const char *fileName, const char *functionName, uint64_t line, const std::string &message)
    {
        if (level_ <= Level::INFO)
            write("INFO", fileName, functionName, line, message);
    }
    void Logger::debug(const char *fileName, const char *functionName, uint64_t line, const std::string &message)
    {
        if (level_ <= Level::DEBUG)
            write("DEBUG", fileName, functionName, line, message);
    }
    void Logger::trace(const char *fileName, const char *functionName, uint64_t line, const std::string &message)
    {
        if (level_ <= Level::TRACE)
            write("TRACE", fileName, functionName, line, message);
    }

    void Logger::write(const std::string &level, const char *fileName, const char *functionName, uint64_t line, const std::string &message)
    {
        std::filesystem::path p{fileName};
        std::string fLevel = level;
        while (fLevel.length() < 5) {
            fLevel.append(" ");
        }
        std::ostringstream oss("");
        oss << fLevel << " ";
        oss << "file: " << p.filename().generic_string() << " " << functionName << " line: " << line << " ";
        oss << message;
        oss << " " << name_ << std::endl;

        switch (channel_) {
        case Channel::CONSOLE:
            flush(std::cout, oss.str());
            break;
        case Channel::FILE:
            flush(ofs_, oss.str());
            break;
        }
    }

    void Logger::initialize()
    {
        if (channel_ == Channel::FILE) {
            std::string outputFile = Configuration::getConfiguration().find(PROPERTIES_FILE_NAME, "OUTPUT_PATH");
            if (outputFile == "") {
                outputFile = Configuration::getConfiguration().find(PROPERTIES_FILE_NAME, "OUTPUT_FILE");
            }
            if (outputFile == "")
                outputFile = "eihireoutput.log";

            ofs_.open(outputFile, std::ios_base::out | std::ios_base::app);

            if (!ofs_) {
                std::ostringstream oss("");
                oss << "can't open file '" << outputFile << "'.";
                throw Exception::FileCannotOpenException(E_EXCEPTION_BASE_ARGS(oss.str()));
            }
        }
    }

    void Logger::flush(std::ostream &os, const std::string &message)
    {
        std::lock_guard<std::mutex> lock{mt_};
        os << message << std::flush;
    }

} // namespace Eihire::Logging
