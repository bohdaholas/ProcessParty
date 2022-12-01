#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <csignal>
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
}

process_party::process::environment::~environment() {
    for (char **line_c = raw_environment_map; *line_c; line_c++) {
        delete line_c;
    }
    delete raw_environment_map;
}

char **process_party::process::environment::get_raw() {
    size_t vars_count = count_vars();
    size_t i = 0;
    auto env = new char *[vars_count + 1];
    for (const auto &[key, value]: environment_map) {
        env[i] = (char *) calloc(PATH_MAX, sizeof(char));
        strcpy(env[i], (key + "=" + value).c_str());
        i++;
    }
    env[i] = nullptr;
    raw_environment_map = env;
    return env;
}

size_t process_party::process::environment::count_vars() {
    size_t vars_count;
    for (char **line_c = environ; *line_c; line_c++, vars_count++);
    return vars_count;
}

void
process_party::process::environment::set_env(const std::string &key, const std::string &value) {
    if (key.empty()) {
        throw std::runtime_error("Key variable is empty");
    }
    environment_map[key] = value;
}

void process_party::process::environment::add_to_env(const std::string &key,
                                                     const std::string &value) {
    if (key.empty()) {
        throw std::runtime_error("Key variable is empty");
    }

    if (!environment_map.count(key)) {
        environment_map[key] = value;
    } else {
        environment_map[key] += ":" + value;
    }
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
    boost::split(paths, path_content, boost::is_any_of(":"));
    return paths;
}
