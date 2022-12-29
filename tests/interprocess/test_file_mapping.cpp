#include <fstream>
#include <gtest/gtest.h>
#include <process_party/interprocess.h>

using namespace std;
namespace ppip = process_party::interprocess;

class FileMappingFixture : public testing::Test {
public:
    FileMappingFixture();
    virtual ~FileMappingFixture();

    void SetUp() override; // runs before each test
    void TearDown() override; // runs after each test
protected:
    string filename = "/tmp/file.txt";
};

void FileMappingFixture::SetUp()
{
    string filename ="/tmp/file.txt";
    std::ofstream file(filename, std::ios_base::app);
    if (!file) {
        throw std::runtime_error("coudn't create a file for key association");
    }
    file.close();
}

void FileMappingFixture::TearDown()
{
    std::remove(filename.c_str());
    ASSERT_EQ(false, file_exists(filename));
}

TEST_F(FileMappingFixture, TestSingleArgConstructor) {
    ASSERT_EQ(true, file_exists(filename));
    ppip::file_mapping fm(filename);
    ASSERT_EQ(filename, fm.get_name());
    ASSERT_EQ(read_write, fm.get_mode());
}

TEST_F(FileMappingFixture, Test2ArgConstructor) {
    ASSERT_EQ(true, file_exists(filename));
    ppip::file_mapping fm(filename, read_only);
    ASSERT_EQ(filename, fm.get_name());
    ASSERT_EQ(read_only, fm.get_mode());
}

TEST_F(FileMappingFixture, Test3ArgConstructor) {
    ASSERT_EQ(true, file_exists(filename));
    ASSERT_NO_THROW(ppip::file_mapping fm(filename,
                                          read_only,
                            open_or_create));
}

TEST_F(FileMappingFixture, OpenOnlyWhenNotExist) {
    ASSERT_EQ(true, file_exists(filename));
    ppip::file_mapping::remove(filename);
    ASSERT_EQ(false, file_exists(filename));
    ASSERT_THROW(ppip::file_mapping fm(filename,
                                          read_only,
                            open_only), runtime_error);
}

TEST_F(FileMappingFixture, CreateOnlyWhenExist) {
    ASSERT_EQ(true, file_exists(filename));
    ASSERT_THROW(ppip::file_mapping fm(filename,
                                       read_only,
                         create_only), runtime_error);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
