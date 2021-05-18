#ifndef EIHIRE_EXCEPTION_Exception_INCLUDED
#define EIHIRE_EXCEPTION_Exception_INCLUDED

#include <stdexcept>

namespace Eihire
{
    namespace Exception
    {
        class FileCannotOpenException : public std::runtime_error
        {
        public:
            FileCannotOpenException(const std::string &msg);
        };

    } // namespace Exception
} // namespace Eihire

#endif // EIHIRE_EXCEPTION_Exception_INCLUDED
