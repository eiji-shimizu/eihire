#ifndef Eihire_Util_Dictionary_INCLUDED
#define Eihire_Util_Dictionary_INCLUDED

#include <string>
#include <map>
#include <any>

namespace Eihire::Util
{
    template <typename K, typename V>
    class Dictionary;

    template <>
    class Dictionary<std::string, std::any>;
    using JSON = Dictionary<std::string, std::any>;

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

        bool isContain(const K &key) const
        {
            auto it = elements_.find(key);
            return it != elements_.end();
        }

        V get(const K &key) const
        {
            return elements_.at(key);
        }

        void set(const K &key, const V &value)
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

    template <>
    class Dictionary<std::string, std::any>
    {
    public:
        Dictionary();
        ~Dictionary();

        // コピー演算
        Dictionary(const Dictionary &);
        Dictionary &operator=(const Dictionary &);
        // ムーブ演算
        Dictionary(Dictionary &&);
        Dictionary &operator=(Dictionary &&);

        bool isContain(const std::string &key) const;
        std::any get(const std::string &key) const;
        void set(const std::string &key, const std::any &value);
        const std::map<std::string, std::any> &elements() const;

        

    private:
        std::map<std::string, std::any> elements_;
    };

} // namespace Eihire::Util

#endif // Eihire_Util_Dictionary_INCLUDED