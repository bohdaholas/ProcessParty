#include <iostream>
#include <gtest/gtest.h>
#include <process_party/process.h>

using namespace std;
namespace pp = process_party;

TEST(SystemCmd, OkStatusCode)
{
    auto p = pp::this_process::get_environment();
    int status_code = pp::process::system("ls");
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

TEST(SystemCmd, ErrorStatusCode)
{
    int status_code = pp::process::system("ls dir_which_not_exist");
//    ASSERT_EQ(LS_NO_SUCH_DIR_ERR, status_code);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
