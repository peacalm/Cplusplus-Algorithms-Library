#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace cil {

template <typename T>
std::string tostr(const T& t) {
    std::ostringstream os;
    os << t;
    return os.str();
}

template <typename T>
void push_to_str_vec(std::vector<std::string>& strs, const T& t) {
    strs.push_back(tostr(t));
}
template <typename T, typename ...Args>
void push_to_str_vec(std::vector<std::string>& strs, const T& t, const Args&... args) {
    push_to_str_vec(strs, t);
    push_to_str_vec(strs, args...);
}

template <typename T, typename ...Args>
std::vector<std::string> tostrs(const T& t, const Args&... args) {
    std::vector<std::string> strs;
    push_to_str_vec(strs, t, args...);
    return strs;
};

template <typename ...Args>
std::string tostr_with_delim(const std::string& delim, const Args&... args) {
    std::vector<std::string> strs;
    push_to_str_vec(strs, args...);
    std::string ret;
    for (size_t i = 0; i < strs.size(); ++i) {
        if (i > 0) ret += delim;
        ret += strs[i];
    }
    return ret;
};

template <typename ...Args>
std::string tostr(const Args&... args) {
    return tostr_with_delim(" ", args...);
};

}  // namespace cil
