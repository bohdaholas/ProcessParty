#include <iostream>
#include <gtest/gtest.h>
#include <process_party/interprocess.h>

using namespace std;
namespace ppip = process_party::interprocess;

TEST(BasicTests, TestSingleArgConstructor)
{
    ppip::shared_memory_object shm("my_shm");
    ASSERT_EQ("my_shm", shm.get_name());
    // 0 is initial size for shared memory
    ASSERT_EQ(0, shm.get_size());
    ASSERT_EQ(NOT_DEFINED, shm.get_shared_block_id());
    ASSERT_EQ(read_write, shm.get_mode());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
