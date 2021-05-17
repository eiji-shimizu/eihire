#include "PropertiesMap.h"

namespace Eihire
{
    namespace Configuration
    {

        PropertiesMap::PropertiesMap() = default;
        PropertiesMap::~PropertiesMap() = default;

        std::string PropertiesMap::get(const std::string &key) const
        {
            return properties_.at(key);
        }

        void PropertiesMap::set(const std::string &key, const std::string &value)
        {
            std::pair<std::string, std::string> e{key, value};
            auto result = properties_.insert(std::make_pair(key, value));
            if (!result.second)
            {
                properties_.at(key) = value;
            }
        }

        const std::map<std::string, std::string> &PropertiesMap::properties() const
        {
            return properties_;
        }

    } // namespace Configuration
} // namespace Eihire
