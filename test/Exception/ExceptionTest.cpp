#include "Exception/Exception.h"
#include "TestUtils.h"

#include "gtest/gtest.h"

using namespace Eihire::Exception;
using namespace Eihire::TestUtils;

class ExceptionTest : public ::testing::Test
{
protected:
    // 試験開始時に一回だけ実行
    static void SetUpTestCase()
    {
    }

    // 試験終了時に一回だけ実行
    static void TearDownTestCase()
    {
    }

    // 各テストケース実行前に実行
    virtual void SetUp()
    {
    }

    // 各テストケース実行後に実行
    virtual void TearDown()
    {
    }
};

TEST_F(ExceptionTest, Exception_Base_001)
{
    try
    {
        throw ExceptionBase("fileName", "function", 100, "test message", std::logic_error{"inner message"});
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

TEST_F(ExceptionTest, Exception_Base_002) 
{
    try
    {
        throw ExceptionBase(E_EXCEPTION_BASE_ARGS("test message", std::logic_error{"inner message"}));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
