#ifndef EIHIRE_TESTUTILS_INCLUDED
#define EIHIRE_TESTUTILS_INCLUDED

#include <filesystem>

namespace Eihire::TestUtils
{
    // カレントディレクトリからディレクトリ階層を遡りeihireディレクトリまで上る
    // そしてeihire/test/testdataのパスを返す
    // eihireディレクトリが見つからなかった場合は例外を投げる
    std::filesystem::path getTestDataPath();

} // namespace Eihire::TestUtils

#endif // EIHIRE_TESTUTILS_INCLUDED
