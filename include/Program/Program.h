#ifndef EIHIRE_PROGRAM_Program_INCLUDED
#define EIHIRE_PROGRAM_Program_INCLUDED

#include "Logging/Logger.h"

#include <string>
#include <filesystem>

namespace Eihire::Program
{
    class Program
    {
    public:
        static Program &instance();
        static Program &initialize(const std::string configurationDirectoryPath);
        static Program &initialize(const std::filesystem::path configurationDirectoryPath);

        ~Program();

        // コピー禁止
        Program(const Program &) = delete;
        Program &operator=(const Program &) = delete;
        // ムーブ禁止
        Program(Program &&) = delete;
        Program &operator=(Program &&) = delete;

        static Eihire::Logging::Logger &logger();

    private:
        Program();
        Program(const std::string configurationDirectoryPath);
        Program(const std::filesystem::path configurationDirectoryPath);
    };

} // namespace Eihire::Program

#endif // EIHIRE_PROGRAM_Program_INCLUDED
