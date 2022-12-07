#include <iostream>
#include <gtest/gtest.h>
#include <process_party/process.h>

constexpr int LS_NO_SUCH_DIR_ERR = 2;
constexpr int CAT_NO_SUCH_DIR_ERR = 1;

constexpr int NO_SUCH_CMD = 2;
constexpr int PING_INVALID_ARGS = 1;

using namespace std;
namespace ppp = process_party::process;

#if IS_WINDOWS
TEST(SystemCmd, OkStatusCode)
{
    // /c - Run Command and then terminate
    DWORD status_code = ppp::system("cmd.exe /c");
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

TEST(SystemCmd, ErrorStatusCode)
{
    DWORD status_code = ppp::system("some_command_which_doesnt_exist");
    ASSERT_EQ(NO_SUCH_CMD, status_code);
}

TEST(SystemExeArgs, OkStatusCode)
{
    std::vector<std::string> ping_args{"-n", "1", "127.0.0.1"};
    DWORD status_code = ppp::system("ping"s, ping_args);
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

TEST(SystemExeArgs, ErrorStatusCode)
{
    std::vector<std::string> ping_args{"-n", "1", "256.256.256.256"};
    DWORD status_code = ppp::system("ping"s, ping_args);
    ASSERT_EQ(PING_INVALID_ARGS, status_code);
}

TEST(SystemExeArgsPath, OkStatusCode)
{
    std::vector<std::string> ping_args{"-n", "1", "127.0.0.1"};
    auto ping_path = ppp::search_path("ping");
    DWORD status_code = ppp::system(ping_path, ping_args);
    ASSERT_STREQ("C:\\Windows\\system32\\ping.exe", (char *) ping_path.string().c_str());
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

TEST(SystemExeArgsPath, ErrorStatusCode)
{
    auto unknown_cmd_path = ppp::search_path("ndklawdnsm,da");
    DWORD status_code = ppp::system(unknown_cmd_path, vector<string>());
    ASSERT_STREQ("", (char *) unknown_cmd_path.c_str());
    ASSERT_NE(EXIT_SUCCESS, status_code);
}
#elif IS_LINUX
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
    std::vector<std::string> ping_args{"-c", "1", "127.0.0.1"};
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

TEST(SystemExeArgsPath, OkStatusCode)
{
    std::vector<std::string> ping_args{"-c", "1", "127.0.0.1"};
    auto ping_path = ppp::search_path("ping");
    int status_code = ppp::system(ping_path, ping_args);
    ASSERT_STREQ("/usr/bin/ping", ping_path.c_str());
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

TEST(SystemExeArgsPath, ErrorStatusCode)
{
    auto unknown_cmd_path = ppp::search_path("ndklawdnsm,da");
    int status_code = ppp::system(unknown_cmd_path);
    ASSERT_STREQ("", unknown_cmd_path.c_str());
    ASSERT_NE(EXIT_SUCCESS, status_code);
}
#elif IS_MACOS
#endif

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
