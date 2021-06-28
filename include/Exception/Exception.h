#ifndef EIHIRE_EXCEPTION_Exception_INCLUDED
#define EIHIRE_EXCEPTION_Exception_INCLUDED

#include <filesystem>
#include <stdexcept>
#include <string>
#include <type_traits>

#define E_EXCEPTION_BASE_ARGS(MESSAGE) (strrchr(__FILE__, std::filesystem::path::preferred_separator) ? strrchr(__FILE__, std::filesystem::path::preferred_separator) + 1 : __FILE__), __FUNCTION__, __LINE__, MESSAGE

namespace Eihire::Exception {

    class ExceptionBase : public std::exception {
    public:
        template <typename InnerException, typename = std::enable_if_t<std::is_base_of_v<std::exception, InnerException>>>
        ExceptionBase(const char *fileName,
                      const char *functionName,
                      uint64_t line,
                      const std::string &message,
                      const InnerException &inner)
            : messages_{getFormatMessage(fileName, functionName, line, message) + '\n' + inner.what()}
        {
        }

        ExceptionBase(const char *fileName,
                      const char *functionName,
                      uint64_t line,
                      const std::string &message)
            : messages_{getFormatMessage(fileName, functionName, line, message)}
        {
        }

        ExceptionBase(const std::string &message)
            : messages_{message}
        {
        }

        const char *what() const noexcept override
        {
            return messages_.c_str();
        }

    private:
        std::string getFormatMessage(const char *fileName,
                                     const char *functionName,
                                     uint64_t line,
                                     const std::string &message) const
        {
            return std::string{fileName} + " " + functionName + "(" + std::to_string(line) + ") " + message;
        }

        std::string messages_;
    };

    class FileCannotOpenException : public ExceptionBase {
    public:
        template <typename InnerException, typename = std::enable_if_t<std::is_base_of_v<std::exception, InnerException>>>
        FileCannotOpenException(const char *fileName,
                                const char *functionName,
                                uint64_t line,
                                const std::string &message,
                                const InnerException &inner)
            : ExceptionBase{fileName, functionName, line, prefix() + message, inner}
        {
        }

        FileCannotOpenException(const char *fileName,
                                const char *functionName,
                                uint64_t line,
                                const std::string &message)
            : ExceptionBase{fileName, functionName, line, prefix() + message}
        {
        }

        FileCannotOpenException(const std::string &message)
            : ExceptionBase{prefix() + message}
        {
        }

    private:
        std::string prefix() const
        {
            return "Eihire::Exception::FileCannotOpenException ";
        }
    };

    class ParseException : public ExceptionBase {
    public:
        template <typename InnerException, typename = std::enable_if_t<std::is_base_of_v<std::exception, InnerException>>>
        ParseException(const char *fileName,
                       const char *functionName,
                       uint64_t line,
                       const std::string &message,
                       const InnerException &inner)
            : ExceptionBase{fileName, functionName, line, prefix() + message, inner}
        {
        }

        ParseException(const char *fileName,
                       const char *functionName,
                       uint64_t line,
                       const std::string &message)
            : ExceptionBase{fileName, functionName, line, prefix() + message}
        {
        }

        ParseException(const std::string &message)
            : ExceptionBase{prefix() + message}
        {
        }

    private:
        std::string prefix() const
        {
            return "Eihire::Exception::ParseException ";
        }
    };

} // namespace Eihire::Exception

#endif // EIHIRE_EXCEPTION_Exception_INCLUDED
