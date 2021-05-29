#ifndef EIHIRE_LOGGING_LOGGER_INCLUDED
#define EIHIRE_LOGGING_LOGGER_INCLUDED

#include <string>
#include <fstream>

namespace Eihire::Logging
{
    class Logger
    {
    public:
        enum class Level
        {
            TRACE = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };

        enum class Channel
        {
            CONSOLE,
            FILE
        };

        Logger(Level level, std::string name);
        Logger(Level level, Channel channel, std::string name);
        ~Logger();

        // コピー禁止
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
        // ムーブ禁止
        Logger(Logger &&) = delete;
        Logger &operator=(Logger &&) = delete;

        void fatal(const std::string &message);
        void error(const std::string &message);
        void warn(const std::string &message);
        void info(const std::string &message);
        void debug(const std::string &message);
        void trace(const std::string &message);

    private:
        Level level_;
        Channel channel_;
        std::string name_;
        std::ofstream ofs_;
    };

} // Eihire::Logging

#endif // EIHIRE_LOGGING_LOGGER_INCLUDED