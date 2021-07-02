#ifndef EIHIRE_EXCEPTION_Exception_INCLUDED
#define EIHIRE_EXCEPTION_Exception_INCLUDED

#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

#define E_EXCEPTION_BASE_ARGS(MESSAGE) (strrchr(__FILE__, std::filesystem::path::preferred_separator) ? strrchr(__FILE__, std::filesystem::path::preferred_separator) + 1 : __FILE__), __FUNCTION__, __LINE__, MESSAGE

namespace Eihire::Exception {

    template <typename T>
    std::enable_if_t<std::is_base_of_v<std::exception, T>, const std::string>
    getAllMessages(const T &e)
    {
        std::ostringstream oss{};
        oss << e.what();
        if (dynamic_cast<const std::nested_exception *>(&e) != nullptr) {
            oss << std::endl
                << getAllMessages((dynamic_cast<const std::nested_exception &>(e).nested_ptr()));
        }
        return oss.str();
    }

    inline const std::string getAllMessages(const std::exception_ptr &rp)
    {
        if (!rp)
            return "";
        std::ostringstream oss{};
        try {
            std::rethrow_exception(rp);
        }
        catch (const std::exception &e) {
            oss << e.what();
            if (dynamic_cast<const std::nested_exception *>(&e) != nullptr) {
                oss << std::endl
                    << getAllMessages((dynamic_cast<const std::nested_exception &>(e).nested_ptr()));
            }
        }
        catch (...) {
            return "";
        }
        return oss.str();
    }

    class ExceptionBase : public std::runtime_error {
    public:
        ExceptionBase(const char *fileName,
                      const char *functionName,
                      uint64_t line,
                      const std::string &message)
            : std::runtime_error{getFormatMessage(fileName, functionName, line, message)}
        {
        }

        ExceptionBase(const std::string &message)
            : std::runtime_error{message}
        {
        }

        const char *what() const noexcept override
        {
            return std::runtime_error::what();
        }

    private:
        std::string getFormatMessage(const char *fileName,
                                     const char *functionName,
                                     uint64_t line,
                                     const std::string &message) const
        {
            return std::string{fileName} + " " + functionName + "(" + std::to_string(line) + ") " + message;
        }
    };

    class FileCannotOpenException : public ExceptionBase {
    public:
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
