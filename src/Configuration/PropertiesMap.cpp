#include "PropertiesMap.h"
#include "Exception.h"

#include <fstream>
#include <sstream>
namespace Eihire
{
    namespace Configuration
    {

        PropertiesMap::PropertiesMap() = default;
        PropertiesMap::~PropertiesMap() = default;
        PropertiesMap::PropertiesMap(const PropertiesMap &) = default;
        PropertiesMap &PropertiesMap::operator=(const PropertiesMap &) = default;
        PropertiesMap::PropertiesMap(PropertiesMap &&) = default;
        PropertiesMap &PropertiesMap::operator=(PropertiesMap &&) = default;

        PropertiesMap::PropertiesMap(std::string fileName)
            : fileName_{fileName}
        {
            // noop
        }

        void PropertiesMap::load()
        {
            // TODO
            std::ifstream ifs((fileName_));
            if (!ifs)
            {
                std::ostringstream oss("");
                oss << "can't open file '" << fileName_ << "'.";
                throw Exception::FileCannotOpenException(oss.str());
            }
            // ファイル読み込み開始
            //ifs.exceptions(ifs.exceptions()|ios_base::)
            std::string line;
            while (ifs)
            {
                std::getline(ifs, line);
                std::ostringstream key("");
                std::ostringstream value("");
                bool flg = false;
                for (const char c : line)
                {
                    if (flg == false && c == '=')
                    {
                        flg = true;
                        continue;
                    }
                    if (flg)
                        value << c;
                    else
                        key << c;
                }

                // '='が見つからなかった場合は構文エラー
                if(!flg)
                {
                    // TODO: 例外を投げる
                }
                set(key.str(), value.str());
            }
        }

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

        const std::string &PropertiesMap::fileName() const
        {
            return fileName_;
        }

        const std::map<std::string, std::string> &PropertiesMap::properties() const
        {
            return properties_;
        }

    } // namespace Configuration
} // namespace Eihire
