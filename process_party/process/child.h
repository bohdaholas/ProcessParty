#ifndef PROCESS_PARTY_CHILD_H
#define PROCESS_PARTY_CHILD_H

#include <vector>

namespace process_party::process {
    class child {
    public:
        /*** Don't allow default constructors/destructors ***/
        child() = delete;
        ~child() = delete;

        child(const std::string &cmd, const std::vector<std::string> &args);
        bool running();
        void wait();
        int exit_code();
    };
}

#endif //PROCESS_PARTY_CHILD_H
