#include <iostream>
#include <gtest/gtest.h>
#include <process_party/process.h>

using namespace std;
namespace ppp = process_party::process;

TEST(SpawnCmd, spawn)
{
    int status_code = ppp::spawn("ls");
    // always returns EXIT_SUCCESS as it's initial values of status_code
    // it is not changed because parent doesn't call wait() on the child
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
