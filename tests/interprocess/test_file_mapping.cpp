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

FileMappingFixture::FileMappingFixture()
{

}

FileMappingFixture::~FileMappingFixture()
{

}

TEST_F(FileMappingFixture, TestSingleArgConstructor) {
    ASSERT_EQ(true, file_exists(filename));
    ppip::file_mapping fm(filename);
    ASSERT_EQ(filename, fm.get_name());
    ASSERT_EQ(read_write, fm.get_mode());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
