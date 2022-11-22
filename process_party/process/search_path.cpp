#include <iostream>
#include <process_party/process/search_path.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

using std::cout, std::cerr, std::endl;
namespace fs = std::filesystem;

fs::path process_party::process::search_path(const std::string &cmd) {
    std::vector<std::string> path_dirs;
    std::string path = getenv("PATH");
    boost::algorithm::split(path_dirs, path, boost::is_any_of(":"));
    for (const auto &dir: path_dirs) {
        std::string cmd_path = dir + "/" + cmd;
        if (access(cmd_path.c_str(), F_OK) == 0) {
            return {cmd_path};
        }
    }
    return {};
}

