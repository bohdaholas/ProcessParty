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
    env.clear_env();
    ASSERT_EQ(true, env.empty());
    ASSERT_EQ(0, env.count_vars());
}

TEST(TestEnvironment, LaunchProgram)
{

}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
