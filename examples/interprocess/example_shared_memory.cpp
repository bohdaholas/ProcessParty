#include <iostream>
#include <cstring>
#include <process_party/interprocess.h>
#include <process_party/process.h>

namespace ppp = process_party::process;
namespace ppip = process_party::interprocess;

using namespace std;

int main(int argc, char **argv) {
    if (argc == 1) {
        ppip::shared_memory_object::remove("shm");
        ppip::shared_memory_object shm("shm",
                                       read_write,
                                       open_or_create);
        shm.truncate(getpagesize());
        ppip::mapped_region region(shm, 0, shm.get_size());
        std::memset(region.get_address(), 1, region.get_size());

        std::string s(argv[0]);
        s += " child ";
        if(0 != std::system(s.c_str()))
            return 1;
    } else {
        ppip::shared_memory_object shm("shm",
                                       read_write,
                                       open_or_create);
        shm.truncate(getpagesize());
        ppip::mapped_region region(shm, 0, shm.get_size());
        char *mem = static_cast<char *>(region.get_address());
        for (int i = 0; i < shm.get_size(); ++i) {
            if (mem[i] != 1)   {
                cout << "incorrent memory" << endl;
            }
        }
        cout << "memory is fine" << endl;
    }
}