#include <iostream>
#include <gtest/gtest.h>
#include <process_party/process.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

constexpr int LS_NO_SUCH_DIR_ERR = 2;
constexpr int CAT_NO_SUCH_DIR_ERR = 1;

constexpr int NO_SUCH_CMD = 2;

using namespace std;
namespace ppp = process_party::process;

#if IS_WINDOWS
TEST(SystemCmd, OkStatusCode)
{
    DWORD status_code = ppp::system("cmd.exe /c dir");
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

TEST(SystemCmd, ErrorStatusCode)
{
    char path[1000];
    string s;

    s = filesystem::current_path().string();
    cout << s << endl << endl;

    GetSystemDirectoryA(path, 1000);
    s = path;
    cout << s << endl << endl;

    GetWindowsDirectoryA(path, 1000);
    s = path;
    cout << s << endl << endl;

    s = getenv("PATH");
    std::vector<std::filesystem::path> paths;
    boost::split(paths, s, boost::is_any_of(";"));
    for (const auto &item: paths) {
        cout << item.string() << endl;
    }
//    DWORD status_code = ppp::system("cmd.exe /c some_command_which_doesnt_exist");
//    ASSERT_EQ(LS_NO_SUCH_DIR_ERR, status_code);
}

TEST(SystemExeArgs, OkStatusCode)
{
    std::vector<std::string> ping_args{"-n", "1", "127.0.0.1"};
    DWORD status_code = ppp::system("cmd /c ping"s, ping_args);
    ASSERT_EQ(EXIT_SUCCESS, status_code);
}

TEST(SystemExeArgs, ErrorStatusCode)
{
    std::vector<std::string> ping_args{"incorrect_arg"};
    DWORD status_code = ppp::system("ping"s, ping_args);
    ASSERT_NE(EXIT_SUCCESS, status_code);
}

TEST(SystemExeArgsPath, OkStatusCode)
{
    std::vector<std::string> ping_args{"-n", "1", "127.0.0.1"};
    auto ping_path = ppp::search_path("ping");
    DWORD status_code = ppp::system(ping_path, ping_args);
    ASSERT_STREQ("/usr/bin/ping", (char *) ping_path.c_str());
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
