#include "Exception/Exception.h"
#include "Logging/Logger.h"
#include "Util/Dictionary.h"

#include <cassert>
#include <iostream>
#include <sstream>

using namespace Eihire::Logging;

namespace Eihire::Util {

    namespace {

        template <typename T>
        bool isValidCast(const std::any &target)
        {
            try {
                T t = std::any_cast<T>(target);
                return true;
            }
            catch (...) {
                return false;
            }
        }

        bool typeValidation(const std::any &target)
        {
            // TODO: 仮の内容
            if (
                isValidCast<std::nullptr_t>(target) ||
                isValidCast<bool>(target) ||
                isValidCast<double>(target) ||
                isValidCast<int>(target) ||
                isValidCast<std::string>(target) ||
                isValidCast<JSON>(target)) {
                return true;
            }

            return false;
        }

        template <typename T, typename K>
        T getT(const std::map<K, std::any> &m, const K &key)
        {
            try {
                return std::any_cast<T>(m.at(key));
            }
            catch (const std::exception &e) {
                throw Eihire::Exception::ExceptionBase(E_EXCEPTION_BASE_ARGS(e.what()));
            }
            catch (...) {
                throw;
            }
        }

        const std::string DOUBLE_QUOTATION = R"(")";

        std::string formatJsonElementName(const std::string &name)
        {
            return DOUBLE_QUOTATION + name + DOUBLE_QUOTATION;
        }

        std::string formatJsonElementValue(const std::any &value)
        {
            if (value.type() == typeid(JSON)) {
            }
            return "";
        }

    } // namespace

    template class Dictionary<std::string, std::any>;

    JSON::JSON() = default;
    JSON::~JSON() = default;

    // コピー演算
    JSON::JSON(const JSON &) = default;
    JSON &JSON::operator=(const JSON &) = default;
    // ムーブ演算
    JSON::JSON(JSON &&) = default;
    JSON &JSON::operator=(JSON &&) = default;

    void JSON::set(const std::string &key, const std::any &value)
    {
        assert(typeValidation(value));
        Logger::getLogger<JSON>().E_DEBUG("here----------------------");
        JSON_BASE::set(key, value);
    }

    void JSON::set(const std::string &key, const char *value)
    {
        if (value == nullptr)
            set(key, std::any{nullptr});
        else
            set(key, std::any{std::string{value}});
    }

    JSON JSON::getObject(const std::string &key) const
    {
        return getT<JSON>(elements_, key);
    }

    int JSON::getInt(const std::string &key) const
    {
        return getT<int>(elements_, key);
    }

    double JSON::getDouble(const std::string &key) const
    {
        return getT<double>(elements_, key);
    }

    std::string JSON::getString(const std::string &key) const
    {
        return getT<std::string>(elements_, key);
    }

    bool JSON::getBool(const std::string &key) const
    {
        return getT<bool>(elements_, key);
    }

    std::nullptr_t JSON::getNull(const std::string &key) const
    {
        return getT<std::nullptr_t>(elements_, key);
    }

    std::string JSON::toString() const
    {
        std::ostringstream oss;
        oss << '{';
        for (const auto &p : elements()) {
            const std::string name = formatJsonElementName(p.first);
            const std::string value = formatJsonElementValue(p.second);
        }
        oss << '}';
        return "";
    }

    // 引数のjson文字列からJSONを生成して返すstaticファクトリ関数
    JSON JSON::createJSON(const std::string &jsonStr)
    {
        return JSON{};
    }

} // namespace Eihire::Util
