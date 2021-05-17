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

            // コピー禁止
            PropertiesMap(const PropertiesMap &) = delete;
            PropertiesMap &operator=(const PropertiesMap &) = delete;
            // ムーブ禁止
            PropertiesMap(PropertiesMap &&) = delete;
            PropertiesMap &operator=(PropertiesMap &&) = delete;

            std::string get(const std::string &key) const;
            void set(const std::string &key, const std::string &value);
            const std::map<std::string, std::string> &properties() const;

        private:
            std::map<std::string, std::string> properties_;
        };

    } // namespace Configuration
} // namespace Eihire
