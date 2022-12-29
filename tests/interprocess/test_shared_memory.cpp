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

TEST(BasicTests, Test2ArgsConstructor)
{
    ppip::shared_memory_object shm("my_shm2", write_only);
    ASSERT_EQ(write_only, shm.get_mode());
    // shared memory with the same name already exists
    ASSERT_THROW(ppip::shared_memory_object("my_shm2"), runtime_error);
}

TEST(BasicTests, Test3ArgsConstructor)
{
    // no shared memory at this point
    ASSERT_THROW(ppip::shared_memory_object shm("my_shm3",
                                                read_write,
                                                open_only),
                 runtime_error);
}

TEST(BasicTests, Truncate)
{
    ppip::shared_memory_object shm("my_shm4");
    ASSERT_EQ(0, shm.get_size());
    shm.truncate(getpagesize());
    ASSERT_EQ(getpagesize(), shm.get_size());
    ASSERT_THROW(shm.truncate(2 * getpagesize()), runtime_error);
}

TEST(BasicTests, RemoveAfter)
{
    ppip::shared_memory_object shm("my_shm5",
                                   read_write,
                                   open_or_create,
                                   true);
    ASSERT_THROW(ppip::shared_memory_object another_shm("my_shm5",
                                                read_write,
                         open_only),
                 runtime_error);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
