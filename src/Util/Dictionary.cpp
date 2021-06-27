#include "Util/Dictionary.h"
#include "Exception/Exception.h"

namespace Eihire::Util
{
    namespace
    {

        template <typename T, typename K>
        T getT(const std::map<K, std::any> &m, const K &key)
        {
            try
            {
                return std::any_cast<T>(m.at(key));
            }
            catch (const std::exception &e)
            {
                throw Eihire::Exception::ExceptionBase(E_EXCEPTION_BASE_ARGS(""), e);
            }
            catch (...)
            {
                throw;
            }
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
        JSON_BASE::set(key, value);
    }

    void JSON::set(const std::string &key, const char *value)
    {
        JSON_BASE::set(key, std::string{value});
    }

    int JSON::getInt(const std::string &key)
    {
        return getT<int>(elements_, key);
    }

    std::string JSON::getString(const std::string &key)
    {
        return getT<std::string>(elements_, key);
    }

} // namespace Eihire::Util
