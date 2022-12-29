#include <iostream>
#include <gtest/gtest.h>
#include <process_party/interprocess.h>

using namespace std;
namespace ppip = process_party::interprocess;

TEST(BasicTests, TestSingleArgConstructor)
{
    ppip::anonymous_shared_memory shm(1000);
    ASSERT_EQ(1000, shm.get_size());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
