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
        throw ExceptionBase(E_EXCEPTION_BASE_ARGS("test message"), std::logic_error{"inner message"});
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

TEST_F(ExceptionTest, Exception_Base_003)
{
    ExceptionBase eb{E_EXCEPTION_BASE_ARGS("test"), std::runtime_error{"inner aaaa"}};
    // ExceptionBase eb{E_EXCEPTION_BASE_ARGS("test"), 1};
    // ExceptionBase eb{E_EXCEPTION_BASE_ARGS("test"), "abc"};
    std::cout << eb.what() << std::endl;
    try
    {
        try
        {
            try
            {
                try
                {
                    throw std::logic_error{"inner message"};
                }
                catch (const std::exception &e)
                {
                    throw ExceptionBase(E_EXCEPTION_BASE_ARGS("test message1"), e);
                }
            }
            catch (const std::exception &e)
            {
                throw ExceptionBase(E_EXCEPTION_BASE_ARGS("test message2"), e);
            }
        }
        catch (const std::exception &e)
        {
            throw ExceptionBase(E_EXCEPTION_BASE_ARGS("test message3"), e);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        const ExceptionBase *pe = dynamic_cast<const ExceptionBase *>(&e);
        if (pe != nullptr)
            eb = *pe;
    }
    std::cout << eb.what() << std::endl;
}

TEST_F(ExceptionTest, Exception_Base_004)
{
    try
    {
        try
        {
            try
            {
                try
                {
                    throw std::logic_error("inner message");
                }
                catch (const std::exception &e)
                {
                    throw ExceptionBase(E_EXCEPTION_BASE_ARGS("test message1"), e);
                }
            }
            catch (const std::exception &e)
            {
                throw;
            }
        }
        catch (const std::exception &e)
        {
            throw ExceptionBase(E_EXCEPTION_BASE_ARGS("test message3"), e);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

TEST_F(ExceptionTest, Exception_Base_005)
{
    // コピー代入テスト
    {
        ExceptionBase eb1{E_EXCEPTION_BASE_ARGS("eb1 test"), std::runtime_error{"inner runtime_error"}};
        std::cout << "eb1 : " << eb1.what() << std::endl;
        ExceptionBase from1{E_EXCEPTION_BASE_ARGS("from1 test"), std::logic_error{"inner logic_error"}};
        std::cout << "from1 : " << from1.what() << std::endl;
        ASSERT_STRNE(from1.what(), eb1.what());
        eb1 = from1;
        ASSERT_STREQ(from1.what(), eb1.what());
        std::cout << "from1 : " << from1.what() << std::endl;
        std::cout << "eb1 : " << eb1.what() << std::endl;

        eb1 = eb1;
        std::cout << "eb1 : " << eb1.what() << std::endl;
    }

    std::cout << std::endl;
    // ムーブ代入テスト
    {
        ExceptionBase eb2{E_EXCEPTION_BASE_ARGS("eb2 test"), std::runtime_error{"inner runtime_error"}};
        std::cout << "eb2 : " << eb2.what() << std::endl;
        ExceptionBase from2{E_EXCEPTION_BASE_ARGS("from2 test"), std::logic_error{"inner logic_error"}};
        std::cout << "from2 : " << from2.what() << std::endl;

        std::string temp{from2.what()};
        ASSERT_STRNE(from2.what(), eb2.what());
        eb2 = std::move(from2);
        ASSERT_STREQ("", from2.what());
        ASSERT_STREQ(temp.c_str(), eb2.what());
        std::cout << "eb2 : " << eb2.what() << std::endl;
        std::cout << "from2 : " << from2.what() << std::endl;

        eb2 = std::move(eb2);
        std::cout << "eb2 : " << eb2.what() << std::endl;
    }

    std::cout << std::endl;
    // コピーコンストラクトテスト
    {
        ExceptionBase from3{E_EXCEPTION_BASE_ARGS("from3 test"), std::logic_error{"inner logic_error"}};
        std::cout << "from3 : " << from3.what() << std::endl;
        ExceptionBase eb3{from3};
        ASSERT_STREQ(from3.what(), eb3.what());
        std::cout << "eb3 : " << eb3.what() << std::endl;
        std::cout << "from3 : " << from3.what() << std::endl;
    }

    std::cout << std::endl;
    // ムーブコンストラクトテスト
    {
        ExceptionBase from4{E_EXCEPTION_BASE_ARGS("from4 test"), std::logic_error{"inner logic_error"}};
        std::cout << "from4 : " << from4.what() << std::endl;
        std::string temp{from4.what()};
        ExceptionBase eb4{std::move(from4)};
        ASSERT_STREQ("", from4.what());
        ASSERT_STREQ(temp.c_str(), eb4.what());
        std::cout << "eb4 : " << eb4.what() << std::endl;
        std::cout << "from4 : " << from4.what() << std::endl;
    }

    std::cout << std::endl;
    // swapテスト
    {
        ExceptionBase a{E_EXCEPTION_BASE_ARGS("a test"), std::runtime_error{"inner runtime_error"}};
        ExceptionBase b{E_EXCEPTION_BASE_ARGS("b test"), std::runtime_error{"inner runtime_error"}};
        std::string tempA{a.what()};
        std::string tempB{b.what()};
        std::swap(a, b);
        ASSERT_STREQ(tempA.c_str(), b.what());
        ASSERT_STREQ(tempB.c_str(), a.what());
        std::cout << "a : " << a.what() << std::endl;
        std::cout << "b : " << b.what() << std::endl;

        std::swap(a, a);
        std::cout << "a : " << a.what() << std::endl;
    }
}

TEST_F(ExceptionTest, ParseException_001)
{
    try
    {
        try
        {
            try
            {
                try
                {
                    throw std::logic_error("inner message");
                }
                catch (const std::exception &e)
                {
                    throw ExceptionBase(E_EXCEPTION_BASE_ARGS("test message1"), e);
                }
            }
            catch (const std::exception &e)
            {
                throw ParseException(E_EXCEPTION_BASE_ARGS("parse error"), e);
            }
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

TEST_F(ExceptionTest, FileCannotOpenException_001)
{
    try
    {
        try
        {
            try
            {
                try
                {
                    throw FileCannotOpenException("inner message1");
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                    throw ParseException(E_EXCEPTION_BASE_ARGS("inner message2"), e);
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                throw FileCannotOpenException(E_EXCEPTION_BASE_ARGS("file can not open."));
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            throw FileCannotOpenException(E_EXCEPTION_BASE_ARGS("file can not open again."), e);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
