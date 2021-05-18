#include "Configuration.h"

#include <iostream>

namespace Eihire
{
    namespace Configuration
    {
        namespace
        {
            void initializeImpl(std::vector<PropertiesMap> &propertiesMapList, const std::vector<std::string> &fileNameList)
            {
                for (const auto &fileName : fileNameList)
                {
                    PropertiesMap p{fileName};
                    propertiesMapList.push_back(p);
                }
                for (PropertiesMap &p : propertiesMapList)
                {
                    p.load();
                }
            }

        } // namespace

        Configuration::Configuration()
            : fileNameList_{"Eihire.properties"}
        {
            initialize();
        }

        Configuration::~Configuration()
        {
            // noop
        }

        Configuration::Configuration(const std::string &fileName)
            : fileNameList_{fileName}
        {
            initialize();
        }

        Configuration::Configuration(const std::vector<std::string> &fileNameList)
            : fileNameList_{fileNameList}
        {
            initialize();
        }

        std::string Configuration::get(const std::string &key) const
        {
            return get("", key);
        }

        std::string Configuration::get(const std::string &fileName, const std::string &key) const
        {
            for (const PropertiesMap &p : propertiesMapList_)
            {
                if (fileName != "")
                {
                    if (p.fileName() == fileName)
                        return p.get(key);
                    else
                        continue;
                }

                auto it = p.properties().find(key);
                if (it != p.properties().end())
                {
                    return it->second;
                }
                else
                    continue;
            }

            // 見つからなかった場合に強制的にout_of_range例外を送出
            return propertiesMapList_.at(0).properties().at(key);
        }

        const std::vector<PropertiesMap> &Configuration::propertiesMapList() const
        {
            return propertiesMapList_;
        }

        void Configuration::initialize()
        {
            initializeImpl(propertiesMapList_, fileNameList_);
        }

    } // Configuration
} // Eihire