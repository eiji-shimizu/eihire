#include "Logging/Logger.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Eihire::Logging
{
    Logger::Logger(Level level, std::string name)
        : level_{level},
          channel_{Channel::CONSOLE},
          name_{name},
          ofs_{}
    {
        // noop
    }

    Logger::Logger(Level level, Channel channel, std::string name)
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
        if (channel_ == Channel::FILE)
        {
            if (ofs_.is_open())
            {
                ofs_.close();
            }
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
