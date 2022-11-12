#include <iostream>
#include <gtest/gtest.h>
#include <process_party/process.h>

constexpr int LS_NO_SUCH_DIR_ERR = 2;
constexpr int CAT_NO_SUCH_DIR_ERR = 1;

using namespace std;
namespace ppp = process_party::process;

TEST(SystemCmd, OkStatusCode)
{
    int status_code = ppp::system("ls");
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

TEST(SystemCmd, ErrorStatusCode)
{
    int status_code = ppp::system("ls dir_which_not_exist");
    ASSERT_EQ(LS_NO_SUCH_DIR_ERR, status_code);
}

TEST(SystemExeArgs, OkStatusCode)
{
    std::vector<std::string> ping_args{"-c", "1", "google.com"};
    int status_code = ppp::system("ping"s, ping_args);
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

TEST(SystemExeArgs, ErrorStatusCode)
{
    std::vector<std::string> cat_args{"/not_exist1",
                                       "/not_exist2"};
    int status_code = ppp::system("cat"s, cat_args);
    cout << status_code << endl;
    ASSERT_EQ(CAT_NO_SUCH_DIR_ERR, status_code);
}

// TODO: write test here using search path
TEST(SystemExeArgsPath, OkStatusCode)
{
}

TEST(SystemExeArgsPath, ErrorStatusCode)
{
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
