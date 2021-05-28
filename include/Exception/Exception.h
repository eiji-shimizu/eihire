#ifndef EIHIRE_EXCEPTION_Exception_INCLUDED
#define EIHIRE_EXCEPTION_Exception_INCLUDED

#include <stdexcept>

namespace Eihire::Exception
{
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
