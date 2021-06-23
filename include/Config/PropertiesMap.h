#ifndef EIHIRE_CONFIG_PropertiesMap_INCLUDED
#define EIHIRE_CONFIG_PropertiesMap_INCLUDED

#include <string>
#include <map>

namespace Eihire::Config
{
    class PropertiesMap
    {
    public:
        PropertiesMap();
        ~PropertiesMap();
        PropertiesMap(std::string filePath);

        // コピー演算
        PropertiesMap(const PropertiesMap &);
        PropertiesMap &operator=(const PropertiesMap &);
        // ムーブ演算
        PropertiesMap(PropertiesMap &&);
        PropertiesMap &operator=(PropertiesMap &&);

        void load();
        bool isContain(const std::string &key) const;
        std::string get(const std::string &key) const;
        void set(const std::string &key, const std::string &value);
        const std::string &fileName() const;
        const std::map<std::string, std::string> &properties() const;

    private:
        std::string filePath_;
        std::string fileName_;
        std::map<std::string, std::string> properties_;
    };

} // namespace Eihire::Config

#endif // EIHIRE_CONFIG_PropertiesMap_INCLUDED
