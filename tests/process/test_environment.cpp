#include <iostream>
#include <gtest/gtest.h>
#include <process_party/process.h>

using namespace std;
namespace pp = process_party;

TEST(TestEnvironment, BasicTests)
{
    auto env = pp::this_process::get_environment();
    ASSERT_EQ(true, !env.empty());
    ASSERT_LE(0, env.count_vars());
    env.get_raw();
    env.clear_env();
    ASSERT_EQ(true, env.empty());
    ASSERT_EQ(0, env.count_vars());
}

TEST(TestEnvironment, SetGetAdd)
{
    auto env = pp::this_process::get_environment();
    env.set_env("PATH", "/home");
    ASSERT_STREQ("/home", env.get_env("PATH").c_str());
    ASSERT_EQ(false, env.is_env_present("some_var"));
    ASSERT_THROW(env.get_env("some_var"), std::runtime_error);
    env.add_to_env("PATH", "/tmp");
    string path = "/home"s + ENV_DELIM + "/tmp"s;
    ASSERT_STREQ(path.c_str(), env.get_env("PATH").c_str());
}

TEST(TestEnvironment, Path)
{
    auto path = pp::this_process::path();
    ASSERT_NE(0, path.size());
    ASSERT_NE(0, pp::this_process::get_id());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
