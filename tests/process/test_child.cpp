#include <iostream>
#include <gtest/gtest.h>
#include <process_party/process.h>

constexpr int LS_NO_SUCH_DIR_ERR = 2;
constexpr int CAT_NO_SUCH_DIR_ERR = 1;

using namespace std;
namespace ppp = process_party::process;

#if IS_WINDOWS
TEST(ChildCmd, OkStatusCode)
{
    ppp::child c("ls");
    c.wait();
    ASSERT_EQ(EXIT_SUCCESS, c.get_exit_code());
}

TEST(ChildCmd, ErrorStatusCode)
{
    ppp::child c("ls dir_which_not_exist");
    c.wait();
    ASSERT_EQ(LS_NO_SUCH_DIR_ERR, c.get_exit_code());
}

TEST(ChildCmdDetach, OkStatusCode)
{
    ppp::child c("ls");
    c.detach();
    ASSERT_EQ(EXIT_SUCCESS, c.get_exit_code());
}

TEST(ChildExeArgs, OkStatusCode)
{
    std::vector<std::string> ping_args{"-c", "3", "google.com"};
    ppp::child c("ping"s, ping_args);
    // ping pings 3 times so he should be running
    ASSERT_EQ(true, c.running());
    c.wait();
    ASSERT_EQ(EXIT_SUCCESS, c.get_exit_code());
    // ping certainly finished its execution because we called wait()
    cout << "second check" << endl;
    ASSERT_EQ(false, c.running());
}

TEST(ChildExeArgs, ErrorStatusCode)
{
    std::vector<std::string> cat_args{"/not_exist1",
                                      "/not_exist2"};
    ppp::child c("cat"s, cat_args);
    c.wait();
    ASSERT_EQ(CAT_NO_SUCH_DIR_ERR, c.get_exit_code());
}

TEST(ChildExeArgsPath, OkStatusCode)
{
    std::vector<std::string> ping_args{"-c", "1", "127.0.0.1"};
    auto ping_path = ppp::search_path("ping");
    ppp::child c(ping_path, ping_args);
    c.wait();
//    ASSERT_STREQ("/usr/bin/ping", ping_path.c_str());
    ASSERT_EQ(EXIT_SUCCESS, c.get_exit_code());
}

TEST(ChildExeArgsPath, ErrorStatusCode)
{
    auto unknown_cmd_path = ppp::search_path("ndklawdnsm,da");
//    ppp::child c(unknown_cmd_path);
//    c.wait();
//    ASSERT_STREQ("", unknown_cmd_path.c_str());
//    ASSERT_NE(EXIT_SUCCESS, c.get_exit_code());
}

TEST(TerminateChild, KillChild)
{
    std::vector<std::string> ping_args{"-c", "10", "127.0.0.1"};
    ppp::child c("ping"s, ping_args);
    ASSERT_EQ(true, c.running());
    c.terminate();
    c.wait();
    ASSERT_EQ(SIGTERM, c.get_exit_code());
    ASSERT_EQ(false, c.running());
}
#elif IS_LINUX
TEST(ChildCmd, OkStatusCode)
{
    ppp::child c("ls");
    c.wait();
    ASSERT_EQ(EXIT_SUCCESS, c.get_exit_code());
}

TEST(ChildCmd, ErrorStatusCode)
{
    ppp::child c("ls dir_which_not_exist");
    c.wait();
    ASSERT_EQ(LS_NO_SUCH_DIR_ERR, c.get_exit_code());
}

TEST(ChildCmdDetach, OkStatusCode)
{
    ppp::child c("ls");
    c.detach();
    ASSERT_EQ(EXIT_SUCCESS, c.get_exit_code());
}

TEST(ChildExeArgs, OkStatusCode)
{
    std::vector<std::string> ping_args{"-c", "3", "google.com"};
    ppp::child c("ping"s, ping_args);
    // ping pings 3 times so he should be running
    ASSERT_EQ(true, c.running());
    c.wait();
    ASSERT_EQ(EXIT_SUCCESS, c.get_exit_code());
    // ping certainly finished its execution because we called wait()
    cout << "second check" << endl;
    ASSERT_EQ(false, c.running());
}

TEST(ChildExeArgs, ErrorStatusCode)
{
    std::vector<std::string> cat_args{"/not_exist1",
                                       "/not_exist2"};
    ppp::child c("cat"s, cat_args);
    c.wait();
    ASSERT_EQ(CAT_NO_SUCH_DIR_ERR, c.get_exit_code());
}

TEST(ChildExeArgsPath, OkStatusCode)
{
    std::vector<std::string> ping_args{"-c", "1", "127.0.0.1"};
    auto ping_path = ppp::search_path("ping");
    ppp::child c(ping_path, ping_args);
    c.wait();
    ASSERT_STREQ("/usr/bin/ping", ping_path.c_str());
    ASSERT_EQ(EXIT_SUCCESS, c.get_exit_code());
}

TEST(ChildExeArgsPath, ErrorStatusCode)
{
    auto unknown_cmd_path = ppp::search_path("ndklawdnsm,da");
    ppp::child c(unknown_cmd_path);
    c.wait();
    ASSERT_STREQ("", unknown_cmd_path.c_str());
    ASSERT_NE(EXIT_SUCCESS, c.get_exit_code());
}

TEST(TerminateChild, KillChild)
{
    std::vector<std::string> ping_args{"-c", "10", "127.0.0.1"};
    ppp::child c("ping"s, ping_args);
    ASSERT_EQ(true, c.running());
    c.terminate();
    c.wait();
    ASSERT_EQ(SIGTERM, c.get_exit_code());
    ASSERT_EQ(false, c.running());
}
#elif IS_MACOS
#endif

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
