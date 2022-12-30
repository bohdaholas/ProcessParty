#include <iostream>
#include "process_party/process.h"

namespace ppp = process_party::process;

using namespace std;

int main() {
    ppp::system("ls");

    auto redirection = process_party::process::redirection_manager{};
    redirection.set_stdout("test.txt");
    ppp::system("ls", redirection);
}
