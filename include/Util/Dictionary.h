#ifndef Eihire_Util_Dictionary_INCLUDED
#define Eihire_Util_Dictionary_INCLUDED

#include <string>
#include <map>
#include <vector>
#include <any>

namespace Eihire::Util
{
    template <typename K, typename V>
    class Dictionary
    {
    public:
        Dictionary() = default;
        ~Dictionary() = default;

        // コピー演算
        Dictionary(const Dictionary &) = default;
        Dictionary &operator=(const Dictionary &) = default;
        // ムーブ演算
        Dictionary(Dictionary &&) = default;
        Dictionary &operator=(Dictionary &&) = default;

        virtual bool isContain(const K &key) const
        {
            auto it = elements_.find(key);
            return it != elements_.end();
        }

        virtual V get(const K &key) const
        {
            return elements_.at(key);
        }

        virtual void set(const K &key, const V &value)
        {
            auto result = elements_.insert(std::make_pair(key, value));
            if (!result.second)
            {
                elements_.at(key) = value;
            }
        }

        const std::map<K, V> &elements() const
        {
            return elements_;
        }

    protected:
        std::map<K, V> elements_;
    };

    using JSON_BASE = Dictionary<std::string, std::any>;

    class JSON : public JSON_BASE
    {
    public:
        JSON();
        ~JSON();

        // コピー演算
        JSON(const JSON &);
        JSON &operator=(const JSON &);
        // ムーブ演算
        JSON(JSON &&);
        JSON &operator=(JSON &&);

        void set(const std::string &key, const std::any &value) override;

        // overrideではない valueがconst char*であった場合にstringに変換してセットする
        void set(const std::string &key, const char *value);

        JSON getObject(const std::string &key) const;
        std::vector<std::any> getArray(const std::string &key) const;
        int getInt(const std::string &key) const;
        double getDouble(const std::string &key) const;
        std::string getString(const std::string &key) const;
        bool getBool(const std::string &key) const;
        std::nullptr_t getNull(const std::string &key) const;

        std::string toString() const;

        static JSON createJSON(const std::string &jsonStr);
    };

} // namespace Eihire::Util

#endif // Eihire_Util_Dictionary_INCLUDED