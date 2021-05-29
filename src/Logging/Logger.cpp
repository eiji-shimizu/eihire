#include "Logging/Logger.h"

#include <iostream>
#include <fstream>

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

    void Logger::fatal(const std::string &message)
    {
    }
    void Logger::error(const std::string &message)
    {
    }
    void Logger::warn(const std::string &message)
    {
    }
    void Logger::info(const std::string &message)
    {
        ofs_ << message << std::endl;
    }
    void Logger::debug(const std::string &message)
    {
    }
    void Logger::trace(const std::string &message)
    {
    }

} // namespace Eihire::Logging
