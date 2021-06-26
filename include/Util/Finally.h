#ifndef EIHIRE_UTIL_FINALLY_INCLUDED
#define EIHIRE_UTIL_FINALLY_INCLUDED

#include <functional>

namespace Eihire::Util
{
    class Finally final
    {
    public:
        Finally(std::function<void()> f, bool exceptionHandling = true)
            : cleanUpFunction_{f},
              exceptionHandling_{exceptionHandling}
        {
        }

        ~Finally()
        {
            if (exceptionHandling_)
                try
                {
                    cleanUpFunction_();
                }
                catch (...)
                {
                    // ignore
                }
            else
                cleanUpFunction_();
        }

        // コピー禁止
        Finally(const Finally &) = delete;
        Finally &operator=(const Finally &) = delete;
        // ムーブ可
        Finally(Finally &&) = default;
        Finally &operator=(Finally &&) = default;

        bool isValid() const noexcept
        {
            return cleanUpFunction_.operator bool();
        }

    private:
        std::function<void()> cleanUpFunction_;
        bool exceptionHandling_;
    };
} // namespace Eihire::Util

#endif // EIHIRE_UTIL_FINALLY_INCLUDED
