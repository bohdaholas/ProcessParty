#include <gtest/gtest.h>
#include <fstream>
#include <process_party/interprocess.h>

using namespace std;
namespace ppip = process_party::interprocess;

TEST(BasicTests, TestSingleArgConstructor)
{
    string filename ="/tmp/file.txt";
    std::ofstream file(filename, std::ios_base::app);
    if (!file) {
        throw std::runtime_error("coudn't create a file for key association");
    }
    file.close();

    ppip::file_mapping fm(filename);
//    ASSERT_EQ("my_shm", shm.get_name());
//    // 0 is initial size for shared memory
//    ASSERT_EQ(0, shm.get_size());
//    ASSERT_EQ(NOT_DEFINED, shm.get_shared_block_id());
//    ASSERT_EQ(read_write, shm.get_mode());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
