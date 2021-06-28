#ifndef EIHIRE_PROGRAM_Program_INCLUDED
#define EIHIRE_PROGRAM_Program_INCLUDED

#include "Config/Configuration.h"
#include "Logging/Logger.h"

#include <filesystem>
#include <string>

namespace Eihire::Program {

    class Program {
    public:
        static Program &instance();
        static Program &initialize(const std::string configurationDirectoryPath);
        static Program &initialize(const std::filesystem::path configurationDirectoryPath);

        // デフォルトで読み込む設定ファイル名(econf.properties)
        static const std::string DEFAULT_PROPERTIES_FILE_NAME;

        ~Program();

        // コピー禁止
        Program(const Program &) = delete;
        Program &operator=(const Program &) = delete;
        // ムーブ禁止
        Program(Program &&) = delete;
        Program &operator=(Program &&) = delete;

        // コンフィグへの参照を返す
        static Eihire::Config::Configuration &config();
        // デフォルトのロガーの参照を返す
        static Eihire::Logging::Logger &logger();

    private:
        Program();
        Program(const std::string configurationDirectoryPath);
        Program(const std::filesystem::path configurationDirectoryPath);
    };

} // namespace Eihire::Program

#endif // EIHIRE_PROGRAM_Program_INCLUDED
