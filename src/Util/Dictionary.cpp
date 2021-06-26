#include "Util/Dictionary.h"

namespace Eihire::Util
{
    // using JSON = Dictionary<std::string, std::any>;
    Dictionary<std::string, std::any>::Dictionary() = default;
    Dictionary<std::string, std::any>::~Dictionary() = default;

    // コピー演算
    Dictionary<std::string, std::any>::Dictionary(const Dictionary &) = default;
    Dictionary<std::string, std::any> &Dictionary<std::string, std::any>::operator=(const Dictionary &) = default;
    // ムーブ演算
    Dictionary<std::string, std::any>::Dictionary(Dictionary &&) = default;
    Dictionary<std::string, std::any> &Dictionary<std::string, std::any>::operator=(Dictionary &&) = default;

    void Dictionary<std::string, std::any>::set(const std::string &key, const std::any &value)
    {
        auto result = elements_.insert(std::make_pair(key, value));
        if (!result.second)
        {
            elements_.at(key) = value;
        }
    }

} // namespace Eihire::Util
