#ifndef EIHIRE_LOGGING_LOGGER_INCLUDED
#define EIHIRE_LOGGING_LOGGER_INCLUDED

#include <string>
#include <fstream>

#define E_FATAL(MESSAGE) fatal(__FILE__, __FUNCTION__, __LINE__, MESSAGE);
#define E_ERROR(MESSAGE) error(__FILE__, __FUNCTION__, __LINE__, MESSAGE);
#define E_WARN(MESSAGE) warn(__FILE__, __FUNCTION__, __LINE__, MESSAGE);
#define E_INFO(MESSAGE) info(__FILE__, __FUNCTION__, __LINE__, MESSAGE);
#define E_DEBUG(MESSAGE) debug(__FILE__, __FUNCTION__, __LINE__, MESSAGE);
#define E_TRACE(MESSAGE) trace(__FILE__, __FUNCTION__, __LINE__, MESSAGE);

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

        Logger(const std::string &name);
        Logger(const std::string &name, const Level level);
        Logger(const std::string &name, const Level level, const Channel channel);
        ~Logger();

        // コピー禁止
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
        // ムーブ禁止
        Logger(Logger &&) = delete;
        Logger &operator=(Logger &&) = delete;

        void setLevel(Level level);

        void fatal(const char *fileName, const char *functionName, uint64_t line, const std::string &message);
        void error(const char *fileName, const char *functionName, uint64_t line, const std::string &message);
        void warn(const char *fileName, const char *functionName, uint64_t line, const std::string &message);
        void info(const char *fileName, const char *functionName, uint64_t line, const std::string &message);
        void debug(const char *fileName, const char *functionName, uint64_t line, const std::string &message);
        void trace(const char *fileName, const char *functionName, uint64_t line, const std::string &message);

        // ログの設定ファイル名(elog.propertiesで固定)
        static const std::string PROPERTIES_FILE_NAME;

        template <typename T>
        static Logger &getLogger();

    private:
        void initialize();
        void write(const std::string &level, const char *fileName, const char *functionName, uint64_t line, const std::string &message);

        Level level_;
        Channel channel_;
        std::string name_;
        std::ofstream ofs_;
    };

    template <typename T>
    Logger &Logger::getLogger()
    {
        static Logger *instance = new Logger(typeid(T).name());
        return *instance;
    }

} // Eihire::Logging

#endif // EIHIRE_LOGGING_LOGGER_INCLUDED