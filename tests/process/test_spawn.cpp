#include <iostream>
#include <gtest/gtest.h>
#include <process_party/process.h>

using namespace std;
namespace ppp = process_party::process;

// spawn() always returns EXIT_SUCCESS
// because parent doesn't call wait() on the child

#if IS_WINDOWS
TEST(SpawnCmd, spawn)
{
//    DWORD status_code = ppp::spawn("cmd.exe /c dir");
    DWORD status_code = ppp::spawn("cmd.exe");
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}
#elif IS_LINUX
TEST(SpawnCmd, spawn)
{
    int status_code = ppp::spawn("ls");
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}
#elif IS_MACOS
#endif

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
