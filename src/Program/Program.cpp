#include "Program/Program.h"
#include "Configuration/Configuration.h"

namespace Eihire::Program
{
    Program &Program::instance()
    {
        static Program *instance = new Program();
        return *instance;
    }

    Program &Program::initialize(const std::string configurationDirectoryPath)
    {
        std::filesystem::path p{configurationDirectoryPath};
        return initialize(p);
    }

    Program &Program::initialize(const std::filesystem::path configurationDirectoryPath)
    {
        std::filesystem::path p = configurationDirectoryPath;
        p.append(Eihire::Logging::Logger::PROPERTIES_FILE_NAME);
        Eihire::Configuration::Configuration::getConfiguration().addPropertiesFile(p.generic_string());
        return instance();
    }

    Program::Program() = default;
    Program::~Program() = default;

    Eihire::Logging::Logger &Program::logger()
    {
        static Eihire::Logging::Logger *logger = new Eihire::Logging::Logger("default");
        return *logger;
    }

} // namespace Eihire::Program
