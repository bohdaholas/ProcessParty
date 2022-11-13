#include <iostream>
#include "process_party/process.h"

namespace ppp = process_party::process;

using namespace std;

int main() {
    int status_code = ppp::system("ls");
    cout << status_code << endl;
}