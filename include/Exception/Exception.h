#ifndef EIHIRE_EXCEPTION_Exception_INCLUDED
#define EIHIRE_EXCEPTION_Exception_INCLUDED

#include <stdexcept>
#include <string>
#include <filesystem>
#include <type_traits>

#define E_EXCEPTION_BASE_ARGS(MESSAGE, INNER_EXCEPTION) (strrchr(__FILE__, std::filesystem::path::preferred_separator) ? strrchr(__FILE__, std::filesystem::path::preferred_separator) + 1 : __FILE__), __FUNCTION__, __LINE__, MESSAGE, INNER_EXCEPTION

namespace Eihire::Exception
{
    class ExceptionBase : public std::exception
    {
    public:
        template <typename InnerException, typename = std::enable_if_t<std::is_base_of_v<std::exception, InnerException>>>
        ExceptionBase(const char *fileName,
                      const char *functionName,
                      uint64_t line,
                      const std::string &message,
                      const InnerException &inner)
            : messages_{getFormatMessage(fileName, functionName, line, message) + '\n' + inner.what()}
        {
            // static_assert(std::is_base_of_v<std::exception, InnerException> == true, "Parameter type InnerException is required derived from std::exception");
        }

        const char *what() const noexcept override
        {
            return messages_.c_str();
        }

        // コピー演算
        ExceptionBase(const ExceptionBase &) = default;
        ExceptionBase &operator=(const ExceptionBase &) = default;
        // ムーブ演算
        ExceptionBase(ExceptionBase &&) = default;
        ExceptionBase &operator=(ExceptionBase &&) = default;

    protected:
        virtual std::string getFormatMessage(const char *fileName,
                                             const char *functionName,
                                             uint64_t line,
                                             const std::string &message) const
        {
            return std::string{fileName} + " " + functionName + "(" + std::to_string(line) + ") " + message;
        }

    private:
        std::string messages_;
    };

    class FileCannotOpenException : public std::runtime_error
    {
    public:
        FileCannotOpenException(const std::string &msg);
    };

    class ParseException : public std::runtime_error
    {
    public:
        ParseException(const std::string &msg);
    };

} // namespace Eihire::Exception

#endif // EIHIRE_EXCEPTION_Exception_INCLUDED
