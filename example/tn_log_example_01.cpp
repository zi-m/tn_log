#include <tn_log.h>


namespace tn_log_example_01
{

void test2()
{
    try
    {
        throw TN_RUNTIME_ERROR("something wrong");
    }
    catch(...)
    {
        TN_THROW_WITH_NESTED("test2 {}, {}", 23, 34);
    }
}

void test1()
{
    try
    {
        test2();
    }
    catch(...)
    {
        TN_THROW_WITH_NESTED("test1 {}, {}", 2, 3);
    }
}

int main(int argc, char* argv[])
{
    TN_log_init();

    try
    {
        test1();
    }
    catch(...)
    {
        TN_LOG_CURRENT_EXCEPTION_ERROR("main failed");
    }

    return 0;
}

}

int main(int argc, char* argv[])
{
    return tn_log_example_01::main(argc, argv);
}
