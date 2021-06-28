#include "Config/Configuration.h"
#include "Exception/Exception.h"

#include <iostream>

namespace Eihire::Config {

    namespace {

        void addAndLoad(std::vector<PropertiesMap> &propertiesMapList, const std::vector<std::string> &filePathList)
        {
            for (const auto &filePath : filePathList) {
                PropertiesMap p{filePath};
                propertiesMapList.push_back(p);
            }
            for (PropertiesMap &p : propertiesMapList) {
                p.load();
            }
        }

    } // namespace

    Configuration &Configuration::getConfiguration()
    {
        static Configuration *instance = new Configuration();
        return *instance;
    }

    Configuration &Configuration::getConfiguration(const std::string &filePath)
    {
        std::vector<std::string> vec{filePath};
        return getConfiguration(vec);
    }

    Configuration &Configuration::getConfiguration(const std::vector<std::string> &filePathList)
    {
        Configuration &config = getConfiguration();
        config.addPropertiesFile(filePathList);
        return config;
    }

    Configuration::Configuration() = default;

    Configuration::~Configuration() = default;

    std::string Configuration::find(const std::string &key) const
    {
        return find("", key);
    }

    std::string Configuration::find(const std::string &fileName, const std::string &key) const
    {
        for (const PropertiesMap &p : propertiesMapList_) {
            if (fileName != "") {
                if (p.fileName() == fileName) {
                    if (p.isContain(key))
                        return p.get(key);
                    return "";
                }
                else
                    continue;
            }

            if (p.isContain(key))
                return p.get(key);
            else
                continue;
        }
        return "";
    }

    std::string Configuration::get(const std::string &key) const
    {
        return get("", key);
    }

    std::string Configuration::get(const std::string &fileName, const std::string &key) const
    {
        if (fileName != "") {
            for (const PropertiesMap &p : propertiesMapList_) {
                if (p.fileName() == fileName)
                    return p.get(key);
                else
                    continue;
            }
            // 見つからなかった場合に強制的にout_of_range例外を送出
            return propertiesMapList_.at(propertiesMapList_.size()).properties().at(key);
        }

        for (const PropertiesMap &p : propertiesMapList_) {
            if (p.isContain(key))
                return p.get(key);
            else
                continue;
        }
        // 見つからなかった場合に強制的にout_of_range例外を送出
        return propertiesMapList_.at(0).properties().at(key);
    }

    void Configuration::addPropertiesFile(const std::string &filePath)
    {
        std::vector<std::string> vec{filePath};
        addPropertiesFile(vec);
    }

    void Configuration::addPropertiesFile(const std::vector<std::string> &filePathList)
    {
        std::vector<PropertiesMap> additionalList;
        addAndLoad(additionalList, filePathList);
        for (const auto &p : additionalList) {
            propertiesMapList_.push_back(p);
        }
        for (const auto &s : filePathList) {
            filePathList_.push_back(s);
        }
    }

    const std::vector<PropertiesMap> &Configuration::propertiesMapList() const
    {
        return propertiesMapList_;
    }

} // namespace Eihire::Config
