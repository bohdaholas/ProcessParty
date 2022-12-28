#include <iostream>
#include<fstream>
#include<sstream>
#include <gtest/gtest.h>
#include <process_party/process.h>

using namespace std;
namespace ppp = process_party::process;

std::string read_file(std::string &filename) {
    ifstream file(filename.c_str());
    string content;
    if (file) {
        ostringstream ss;
        ss << file.rdbuf(); // reading data
        content = ss.str();
    }
    return content;
}

void write_to_file(std::string &filename, std::string &content) {
    ofstream file;
    file.open(filename);
    file << content;
    file.close();
}

TEST(FilenameRedirect, OutputTest) {
    std::string test_file = "test_out.txt";
    auto manager = process_party::process::redirection_manager{};
    manager.set_stdout(test_file);
    int status_code = ppp::system("echo Hello", manager);
    ASSERT_EQ(EXIT_SUCCESS, status_code);
    ASSERT_EQ(read_file(test_file), "Hello\n");
}

TEST(FilenameRedirect, ErrorTest) {
    std::string test_file = "test_out.txt";
    auto manager = process_party::process::redirection_manager{};
    manager.set_stderr(test_file);
    ppp::system("ls dir_which_not_exist", manager);
    ASSERT_EQ(read_file(test_file), "ls: cannot access 'dir_which_not_exist': No such file or directory\n");
}

TEST(FilenameRedirect, InputTest) {
    std::string input_file = "test_in.txt";
    std::string output_file = "test_out.txt";
    std::string input_content = "Two words";

    write_to_file(input_file, input_content);
    auto manager = process_party::process::redirection_manager{};
    manager.set_stdin(input_file);
    manager.set_stdout(output_file);
    int status_code = ppp::system("wc -w", manager);

    ASSERT_EQ(EXIT_SUCCESS, status_code);
    ASSERT_EQ(read_file(output_file), "2\n");
}

TEST(PointerRedirect, OutputTest) {
    std::string test_file = "test_out.txt";
    auto manager = process_party::process::redirection_manager{};
    FILE *fptr = fopen(test_file.c_str(), "w");
    manager.set_stdout(fptr);
    int status_code = ppp::system("echo Hello", manager);
    ASSERT_EQ(EXIT_SUCCESS, status_code);
    ASSERT_EQ(read_file(test_file), "Hello\n");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
