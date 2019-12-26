#pragma once

#include <array>
#include <deque>
#include <forward_list>
#include <initializer_list>
#include <list>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace cil {

// =============================================================================
// declaration
// -----------------------------------------------------------------------------

template <typename T>
std::string tostr(const T& t);

template <typename T, typename U>
std::string tostr(const std::pair<T, U>& t);

template <typename T, size_t N>
std::string tostr(const std::array<T, N>& t);

template <typename T>
std::string tostr(const std::deque<T>& t);

template <typename T>
std::string tostr(const std::forward_list<T>& t);

template <typename T>
std::string tostr(const std::initializer_list<T>& t);

template <typename T>
std::string tostr(const std::list<T>& t);

template <typename T, typename U>
std::string tostr(const std::map<T, U>& t);

template <typename T>
std::string tostr(const std::set<T>& t);

template <typename T, typename U>
std::string tostr(const std::unordered_map<T, U>& t);

template <typename T>
std::string tostr(const std::unordered_set<T>& t);

template <typename T>
std::string tostr(const std::vector<T>& t);



template <typename T, typename ...Args>
void push_to_str_vec(std::vector<std::string>& strs, const T& t, const Args&... args);

template <typename T, typename ...Args>
std::vector<std::string> tostrs(const T& t, const Args&... args);

template <typename ...Args>
std::string tostr_with_delim(const std::string& delim, const Args&... args);

template <typename ...Args>
std::string tostr(const Args&... args);


// =============================================================================
// implementations
// -----------------------------------------------------------------------------

template <typename ForwardIterator>
std::string __item_single_container_to_str(
        ForwardIterator b, ForwardIterator e,
        const std::string& l, const std::string& r, const std::string& d) {
    std::string ret{l};
    ForwardIterator it = b;
    while (it != e) {
        if (it != b) ret += d;
        ret += tostr(*it);
        ++it;
    }
    ret += r;
    return ret;
}

template <typename ForwardIterator>
std::string __item_pair_container_to_str(
        ForwardIterator b, ForwardIterator e,
        const std::string& l, const std::string& r, const std::string& d) {
    std::string ret{l};
    ForwardIterator it = b;
    while (it != e) {
        if (it != b) ret += d;
        ret += tostr(it->first) + ": " + tostr(it->second);
        ++it;
    }
    ret += r;
    return ret;
}

template <typename T>
std::string tostr(const T& t) {
    std::ostringstream os;
    os << t;
    return os.str();
}

template <typename T, typename U>
std::string tostr(const std::pair<T, U>& t) {
    return "(" + tostr(t.first) + ", " + tostr(t.second) + ")";
};

template <typename T, size_t N>
std::string tostr(const std::array<T, N>& t) {
    return __item_single_container_to_str(t.begin(), t.end(), "[", "]", ", ");
};

template <typename T>
std::string tostr(const std::deque<T>& t) {
    return __item_single_container_to_str(t.begin(), t.end(), "[", "]", ", ");
};

template <typename T>
std::string tostr(const std::forward_list<T>& t) {
    return __item_single_container_to_str(t.begin(), t.end(), "[", "]", ", ");
};

template <typename T>
std::string tostr(const std::initializer_list<T>& t) {
    return __item_single_container_to_str(t.begin(), t.end(), "[", "]", ", ");
};

template <typename T>
std::string tostr(const std::list<T>& t) {
    return __item_single_container_to_str(t.begin(), t.end(), "[", "]", ", ");
};

template <typename T, typename U>
std::string tostr(const std::map<T, U>& t) {
    return __item_pair_container_to_str(t.begin(), t.end(), "{", "}", ", ");
}

template <typename T>
std::string tostr(const std::set<T>& t) {
    return __item_single_container_to_str(t.begin(), t.end(), "{", "}", ", ");
}

template <typename T, typename U>
std::string tostr(const std::unordered_map<T, U>& t) {
    return __item_pair_container_to_str(t.begin(), t.end(), "{", "}", ", ");
}

template <typename T>
std::string tostr(const std::unordered_set<T>& t) {
    return __item_single_container_to_str(t.begin(), t.end(), "{", "}", ", ");
}

template <typename T>
std::string tostr(const std::vector<T>& t) {
    return __item_single_container_to_str(t.begin(), t.end(), "[", "]", ", ");
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
    return tostr_with_delim(", ", args...);
};


}  // namespace cil
