#ifndef EIHIRE_CONFIG_Configuration_INCLUDED
#define EIHIRE_CONFIG_Configuration_INCLUDED

#include "PropertiesMap.h"

#include <vector>

namespace Eihire::Config {

    class Configuration {
    public:
        // シングルトンのConfigurationオブジェクトを返す
        static Configuration &getConfiguration();
        static Configuration &getConfiguration(const std::string &filePath);
        static Configuration &getConfiguration(const std::vector<std::string> &filePathList);

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

        // プロパティファイルを追加する
        void addPropertiesFile(const std::string &filePath);
        void addPropertiesFile(const std::vector<std::string> &filePathList);

        const std::vector<PropertiesMap> &propertiesMapList() const;

    private:
        Configuration();

        std::vector<PropertiesMap> propertiesMapList_;
        std::vector<std::string> filePathList_;
    };

} // namespace Eihire::Config

#endif // EIHIRE_CONFIG_Configuration_INCLUDED
