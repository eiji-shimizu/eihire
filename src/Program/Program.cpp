#include "Program/Program.h"
#include "Config/Configuration.h"

namespace Eihire::Program {

    const std::string Program::DEFAULT_PROPERTIES_FILE_NAME = "econf.properties";

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
        std::filesystem::path pLogConf = p;
        p.append(DEFAULT_PROPERTIES_FILE_NAME);
        pLogConf.append(Eihire::Logging::Logger::PROPERTIES_FILE_NAME);
        Eihire::Config::Configuration::getConfiguration().addPropertiesFile({p.generic_string(), pLogConf.generic_string()});
        return instance();
    }

    Program::Program() = default;
    Program::~Program() = default;

    Eihire::Config::Configuration &Program::config()
    {
        return Eihire::Config::Configuration::getConfiguration();
    }

    Eihire::Logging::Logger &Program::logger()
    {
        static Eihire::Logging::Logger *logger = new Eihire::Logging::Logger("default");
        return *logger;
    }

} // namespace Eihire::Program
