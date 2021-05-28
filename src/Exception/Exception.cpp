#include "Exception.h"

namespace Eihire::Exception
{
    FileCannotOpenException::FileCannotOpenException(const std::string &msg)
        : std::runtime_error(msg)
    {
    }

    ParseException::ParseException(const std::string &msg)
        : std::runtime_error(msg)
    {
    }

} // namespace Eihire::Exception
