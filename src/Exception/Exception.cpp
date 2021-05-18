#include "Exception.h"

namespace Eihire
{
    namespace Exception
    {
        FileCannotOpenException::FileCannotOpenException(const std::string &msg)
            : std::runtime_error(msg)
        {
        }

    } // namespace Exception
} // namespace Eihire
