#ifndef EIHIRE_CONFIGURATION_PropertiesMap_INCLUDED
#define EIHIRE_CONFIGURATION_PropertiesMap_INCLUDED

#include <string>
#include <map>

namespace Eihire
{
    namespace Configuration
    {

        class PropertiesMap
        {
        public:
            PropertiesMap();
            ~PropertiesMap();
            PropertiesMap(std::string fileName);

            // コピー演算
            PropertiesMap(const PropertiesMap &);
            PropertiesMap &operator=(const PropertiesMap &);
            // ムーブ演算
            PropertiesMap(PropertiesMap &&);
            PropertiesMap &operator=(PropertiesMap &&);

            void load();
            std::string get(const std::string &key) const;
            void set(const std::string &key, const std::string &value);
            const std::string &fileName() const;
            const std::map<std::string, std::string> &properties() const;

        private:
            std::string fileName_;
            std::map<std::string, std::string> properties_;
        };

    } // namespace Configuration
} // namespace Eihire

#endif // EIHIRE_CONFIGURATION_PropertiesMap_INCLUDED
