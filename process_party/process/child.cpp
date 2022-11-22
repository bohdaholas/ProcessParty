#include <iostream>
#include <process_party/process/child.h>

using std::cout, std::cerr, std::endl;

process_party::process::child::child(const std::string &cmd,
                                     const std::vector<std::string> &args) {

}

bool process_party::process::child::running() {
    return false;
}

void process_party::process::child::wait() {

}

int process_party::process::child::exit_code() {
    return 0;
}
