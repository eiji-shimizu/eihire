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
            std::ifstream ifs((fileName_));
            if (!ifs)
            {
                std::ostringstream oss("");
                oss << "can't open file '" << fileName_ << "'.";
                throw Exception::FileCannotOpenException(oss.str());
            }
            // ファイル読み込み開始
            // この文以降でifsがbad状態になった場合に例外をスローさせる
            ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
            std::string line;
            while (ifs)
            {
                std::getline(ifs, line);
                std::ostringstream key("");
                std::ostringstream value("");
                bool isComment = false;
                bool flg = false;
                for (const char c : line)
                {
                    if (c == '#' || c == '!')
                    {
                        isComment = true;
                        break;
                    }
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

                if (!isComment)
                {
                    // コメント行でないのに'='が見つからなかった場合は構文エラー
                    if (!flg)
                    {
                        std::ostringstream oss("");
                        oss << "parse error file'" << fileName_ << "'.";
                        throw Exception::ParseException(oss.str());
                    }
                    set(key.str(), value.str());
                }
            }
        }

        bool PropertiesMap::isContain(const std::string &key) const
        {
            auto it = properties_.find(key);
            return it != properties_.end();
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
