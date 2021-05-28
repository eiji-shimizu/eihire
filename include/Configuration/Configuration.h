#ifndef EIHIRE_CONFIGURATION_Configuration_INCLUDED
#define EIHIRE_CONFIGURATION_Configuration_INCLUDED

#include "PropertiesMap.h"

#include <vector>

namespace Eihire::Configuration
{
    class Configuration
    {
    public:
        // シングルトンのConfigurationオブジェクトを返す
        static Configuration &getConfiguration();
        static Configuration &getConfiguration(const std::string &fileName);
        static Configuration &getConfiguration(const std::vector<std::string> &fileNameList);

        ~Configuration();

        // コピー禁止
        Configuration(const Configuration &) = delete;
        Configuration &operator=(const Configuration &) = delete;
        // ムーブ禁止
        Configuration(Configuration &&) = delete;
        Configuration &operator=(Configuration &&) = delete;

        // 引数のkeyに対応する設定値を探しその値を返す
        // 無い場合は空文字列を返す
        std::string find(const std::string &key) const;
        // 第1引数でプロパティファイル名を指定して,第2引数のkeyに対応する設定値を返す
        // 無い場合は空文字列を返す
        std::string find(const std::string &fileName, const std::string &key) const;

        // 引数のkeyに対応する設定値を探しその値を返す
        // 無い場合は例外を投げる
        std::string get(const std::string &key) const;
        // 第1引数でプロパティファイル名を指定して,第2引数のkeyに対応する設定値を返す
        // 無い場合は例外を投げる
        std::string get(const std::string &fileName, const std::string &key) const;

        const std::vector<PropertiesMap> &propertiesMapList() const;

    private:
        Configuration(const std::vector<std::string> &fileNameList);
        void initialize();

        std::vector<PropertiesMap> propertiesMapList_;
        std::vector<std::string> fileNameList_;
    };

} // namespace Eihire::Configuration

#endif // EIHIRE_CONFIGURATION_Configuration_INCLUDED
