#ifndef EIHIRE_EXCEPTION_Exception_INCLUDED
#define EIHIRE_EXCEPTION_Exception_INCLUDED

#include <stdexcept>
#include <string>
#include <filesystem>

#define E_EXCEPTION_BASE_ARGS(MESSAGE, INNER_EXCEPTION) (strrchr(__FILE__, std::filesystem::path::preferred_separator) ? strrchr(__FILE__, std::filesystem::path::preferred_separator) + 1 : __FILE__), __FUNCTION__, __LINE__, MESSAGE, INNER_EXCEPTION

namespace Eihire::Exception
{
    template <typename InnerException>
    class ExceptionBase : public std::runtime_error
    {
    public:
        ExceptionBase(const char *fileName,
                      const char *functionName,
                      uint64_t line,
                      const std::string &message,
                      const InnerException &inner)
            : std::runtime_error{std::string{fileName} + " " + functionName + "(" + std::to_string(line) + ") " + message},
              inner_(inner)
        {
        }

    private:
        const InnerException inner_;
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
