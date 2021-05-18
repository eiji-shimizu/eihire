#ifndef EIHIRE_CONFIGURATION_Configuration_INCLUDED
#define EIHIRE_CONFIGURATION_Configuration_INCLUDED

#include "PropertiesMap.h"

#include <vector>

namespace Eihire
{
    namespace Configuration
    {

        class Configuration
        {
        public:
            Configuration();
            ~Configuration();
            Configuration(const std::string &fileName);
            Configuration(const std::vector<std::string> &fileNameList);

            // コピー禁止
            Configuration(const Configuration &) = delete;
            Configuration &operator=(const Configuration &) = delete;
            // ムーブ禁止
            Configuration(Configuration &&) = delete;
            Configuration &operator=(Configuration &&) = delete;

            std::string get(const std::string &key) const;
            std::string get(const std::string &fileName, const std::string &key) const;
            const std::vector<PropertiesMap> &propertiesMapList() const;

        private:
            void initialize();

            std::vector<PropertiesMap> propertiesMapList_;
            std::vector<std::string> fileNameList_;
        };

    } // namespace Configuration
} // namespace Eihire

#endif // EIHIRE_CONFIGURATION_Configuration_INCLUDED
