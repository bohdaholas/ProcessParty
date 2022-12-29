#include <iostream>
#include <cstring>
#include <process_party/interprocess.h>
#include <process_party/process.h>

namespace ppp = process_party::process;
namespace ppip = process_party::interprocess;

using namespace std;

int main(int argc, char **argv) {
    if (argc == 1) {
        ppip::file_mapping::remove("/tmp/file.txt");
        ppip::file_mapping fm("/tmp/file.txt",
                                       read_write,
                                       open_or_create);
        fm.truncate(10 * getpagesize());
        ppip::mapped_region region(fm, 0, fm.get_size());
        std::printf("%p", region.get_address());
        std::memset(region.get_address(), 1, region.get_size());
        region.flush();

        std::string s(argv[0]);
        s += " child ";
        if(0 != std::system(s.c_str()))
            return 1;
    } else {
        ppip::file_mapping fm("/tmp/file.txt",
                                       read_write,
                                       open_or_create);
        fm.truncate(getpagesize());
        ppip::mapped_region region(fm, 0, fm.get_size());
        char *mem = static_cast<char *>(region.get_address());
        for (int i = 0; i < fm.get_size(); ++i) {
            if (mem[i] != 1)   {
                cout << "incorrent memory" << endl;
            }
        }
        cout << "memory is fine" << endl;
    }
}