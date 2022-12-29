#include <process_party/common.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include "environment.h"

using std::cout, std::cerr, std::endl;

process_party::process::environment::environment() {
    for (char **line_c = environ; *line_c; line_c++) {
        std::string key, value;
        std::string line = *line_c;

        size_t delimiter_it = line.find('=');

        key = line.substr(0, delimiter_it);
        value = line.substr(delimiter_it + 1, line.size());
        environment_map[key] = value;
    }
    raw_environment_map = nullptr;
}

process_party::process::environment::~environment() {
    clear_env();
    delete raw_environment_map;
}

char **process_party::process::environment::get_raw() {
    if (raw_environment_map != nullptr) {
        return raw_environment_map;
    }

    size_t vars_count = count_vars();
    size_t i = 0;
    auto env = new char *[vars_count + 1];
    for (const auto &[key, value]: environment_map) {
        std::stringstream assignment_ss;
        assignment_ss << key << "=" << value;
        env[i] = new char[PATH_MAX];
        memset(env[i], 0, PATH_MAX);
        std::string res = assignment_ss.str();
        strcpy(env[i], res.c_str());
        i++;
    }
    env[i] = nullptr;
    raw_environment_map = env;
    return env;
}

size_t process_party::process::environment::count_vars() {
    return environment_map.size();
}

void
process_party::process::environment::set_env(const std::string &key,
                                             const std::string &value) {
    if (key.empty()) {
        throw std::runtime_error("Key variable is empty");
    }
    environment_map[key] = value;
}

bool process_party::process::environment::is_env_present(const std::string &key) {
    return environment_map.count(key);
}

std::string process_party::process::environment::get_env(const std::string &key) {
    if (is_env_present(key)) {
        return environment_map[key];
    }
    throw std::runtime_error("Key is not present");
}

void process_party::process::environment::add_to_env(const std::string &key,
                                                     const std::string &value) {
    if (key.empty()) {
        throw std::runtime_error("Key variable is empty");
    }
    if (!is_env_present(key)) {
        throw std::runtime_error("Key is not present");
    }
    environment_map[key] += ENV_DELIM + value;
}

void process_party::process::environment::clear_env() {
    environment_map.clear();
    if (raw_environment_map == nullptr) {
        return;
    }
    for (char **line_c = raw_environment_map; *line_c != nullptr; line_c += 1) {
        delete[] *line_c;
    }
    raw_environment_map = nullptr;
}

bool process_party::process::environment::empty() {
    return count_vars() == 0;
}

int process_party::this_process::get_id() {
    return getpid();
}

process_party::process::environment
process_party::this_process::get_environment() {
    return {};
}

std::vector<std::filesystem::path> process_party::this_process::path() {
    auto path_content = getenv("PATH");
    std::vector<std::filesystem::path> paths;
    boost::split(paths, path_content, boost::is_any_of(ENV_DELIM));
    return paths;
}
