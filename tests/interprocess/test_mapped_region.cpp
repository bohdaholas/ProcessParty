#include <iostream>
#include <gtest/gtest.h>
#include <process_party/interprocess.h>

using namespace std;
namespace ppip = process_party::interprocess;

TEST(SharedMemory, MapSharedMemory)
{
    ppip::shared_memory_object shm("file");
    shm.truncate(getpagesize());
    ppip::mapped_region mapped_region(shm, 0, shm.get_size());
    ASSERT_NE(nullptr, mapped_region.get_address());
    ASSERT_EQ(getpagesize(), mapped_region.get_size());
}

TEST(AnonymousSharedMemory, MapAnonymousSharedMemory)
{
    ppip::anonymous_shared_memory shm(getpagesize());
    ppip::mapped_region mapped_region(shm, 0, shm.get_size());
    ASSERT_NE(nullptr, mapped_region.get_address());
    ASSERT_EQ(getpagesize(), mapped_region.get_size());
}

TEST(File, MapFile)
{
    ppip::file_mapping fm("/tmp/file.txt");
    fm.truncate(getpagesize());
    ppip::mapped_region mapped_region(fm, 0, fm.get_size());
    ASSERT_NE(nullptr, mapped_region.get_address());
    ASSERT_EQ(getpagesize(), mapped_region.get_size());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
