#include "Configuration/PropertiesMap.h"
#include "Exception/Exception.h"

#include <fstream>
#include <sstream>
#include <filesystem>
namespace Eihire::Configuration
{

    namespace
    {
        std::string getFileName(const std::string &filePath)
        {
            std::filesystem::path p{filePath};
            return p.filename().generic_string();
        }

    } // namespace

    PropertiesMap::PropertiesMap() = default;
    PropertiesMap::~PropertiesMap() = default;
    PropertiesMap::PropertiesMap(const PropertiesMap &) = default;
    PropertiesMap &PropertiesMap::operator=(const PropertiesMap &) = default;
    PropertiesMap::PropertiesMap(PropertiesMap &&) = default;
    PropertiesMap &PropertiesMap::operator=(PropertiesMap &&) = default;

    PropertiesMap::PropertiesMap(std::string filePath)
        : filePath_{filePath},
          fileName_{getFileName(filePath)}
    {
        // noop
    }

    void PropertiesMap::load()
    {
        std::ifstream ifs((filePath_));
        if (!ifs)
        {
            std::ostringstream oss("");
            oss << "can't open file '" << filePath_ << "'.";
            throw Exception::FileCannotOpenException(oss.str());
        }
        // ファイル読み込み開始
        // この文以降でifsがbad状態になった場合に例外をスローさせる
        ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);
        std::string line;
        while (ifs)
        {
            std::getline(ifs, line);
            if (line.length() <= 0)
            {
                continue;
            }
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
                    oss << "parse error file'" << filePath_ << "'.";
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

} // namespace Eihire::Configuration
