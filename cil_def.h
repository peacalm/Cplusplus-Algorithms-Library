/*
 * cil-def header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-7-16
 */

#ifndef __CIL_DEF_H__
#define __CIL_DEF_H__

#include "cil_config.h"
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#ifdef __cpp11
#include <array>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#endif
#include <algorithm>
#include <bitset>
#include <functional>
#include <iterator>
#include <memory>
#include <numeric>
#include <string>
#include <typeinfo>
#include <utility>
#ifdef __cpp11
#include <initializer_list>
#include <random>
#include <type_traits>
#endif

#define FOR(i, a, b)                 for (long long i = (long long)(a); i < (long long)(b); ++i)
#define ROF(i, a, b)                 for (long long i = (long long)(b) - 1; i >= (long long)(a); --i)
#define rep(i, a, b)                 for (long long i = (long long)(a); i < (long long)(b); ++i)
#define per(i, a, b)                 for (long long i = (long long)(b) - 1; i >= (long long)(a); --i)
#define REP(i, n)                    for (long long i = 0; i < (long long)(n); ++i)
#define PER(i, n)                    for (long long i = (long long)(n) - 1; i >= 0; --i)
#if                                  defined(__GNUC__) || defined(__GNUG__)
#define ECH(i, c)                    for (__typeof(c.begin()) i = c.begin(), e = c.end(); i != e; ++i)
#define HCE(i, c)                    for (__typeof(c.rbegin()) i = c.rbegin(), e = c.rend(); i != e; ++i)
#else
#define ECH(i, c)                    for (auto i = c.begin(), e = c.end(); i != e; ++i)
#define HCE(i, c)                    for (auto i = c.rbegin(), e = c.rend(); i != e; ++i)
#endif
#define DO(n)                        for (int _iDO_ = int(n); _iDO_--;)
#define rush()                       int _CASES_; scanf("%d", &_CASES_); for (; _CASES_--;)
#define cases()                             int _CASES_; scanf("%d", &_CASES_); for (int iCase = 1; (iCase <= _CASES_ && printf("Case #%d:\n", iCase)); ++iCase)
#define sqr(x)                       ((x) * (x))
#define cub(x)                       ((x) * (x) * (x))
#define all(x)                       (x).begin(), (x).end()
#define sortall(x)                   sort((x).begin(), (x).end())
#define reverseall(x)                reverse((x).begin(), (x).end())
#define sz(x)                        ((int)(x).size())
#define eb                           emplace_back
#define pb                           push_back
#define pf                           push_front
#define ppb                          pop_back
#define ppf                          pop_front
#define mp                           make_pair
#define pbmp(a, b)                   push_back(make_pair((a), (b)))
#define fi                           first
#define se                           second
#define ms(a, b)                     memset((a), (b), sizeof(a))
#define cp(a, b)                     memcpy((a), (b), sizeof(a))
#define IOSS0                        std::ios::sync_with_stdio(false);cin.tie(false);
#define whatis(x)                    cout << #x << " = " << x << endl;
#define uniqueit(v)                  (v).erase(unique((v).begin(), (v).end()), (v).end())
#define insertlb(v, a)               (v).insert(lower_bound((v).begin(), (v).end(), (a)), (a))
#define insertub(v, a)               (v).insert(upper_bound((v).begin(), (v).end(), (a)), (a))
#define PQ                           priority_queue
#define uset                         unordered_set
#define mset                         multiset
#define umap                         unordered_map
#define mmap                         multimap
typedef double                       db;
typedef long double                  ldb;
typedef unsigned char                uchar;
typedef unsigned short               ushort;
typedef unsigned int                 uint;
typedef long long                    ll;
typedef unsigned long long           ull;
typedef std::vector<bool>            VB;
typedef std::vector<VB>              VVB;
typedef std::vector<char>            VC;
typedef std::vector<VC>              VVC;
typedef std::vector<int>             VI;
typedef std::vector<VI>              VVI;
typedef std::vector<ll>              VLL;
typedef std::vector<VLL>             VVLL;
typedef std::vector<double>          VD;
typedef std::vector<VD>              VVD;
typedef std::vector<std::string>     VS;
typedef std::vector<VS>              VVS;
typedef std::pair<int, int>          PII;
typedef std::pair<ll, ll>            PLL;
typedef std::vector<PII>             VPII;
typedef std::vector<PLL>             VPLL;
typedef std::pair<int, PII>          PIPII;
typedef std::pair<ll, PLL>           PLPLL;
typedef std::pair<PII, int>          PPIII;
typedef std::pair<PLL, ll>           PPLLL;
typedef std::map<int, int>           MII;
typedef std::map<ll, ll>             MLL;
typedef std::map<db, db>             MDD;
typedef std::map<std::string, int>   MSI;
typedef std::map<int, std::string>   MIS;
typedef std::set<int>                SI;
typedef std::set<ll>                 SLL;
typedef std::queue<int>              QI;
typedef std::queue<ll>               QLL;
typedef std::queue<PII>              QPII;
typedef std::deque<int>              DI;
typedef std::deque<ll>               DLL;
typedef std::deque<PII>              DPII;
const double                         eps = 1e-9;
const double                         pi = 3.14159265358979323846264338327950288419716939937510;
const int                            inf = 0x3f3f3f3f;
const int                            mod = 1000000007;
const int                            mod2 = 1000000006;
const long long                      infll = 0x3f3f3f3f3f3f3f3fLL;
const int                            dx[8] = { 0, 1, 0, -1, -1, 1, 1, -1 };
const int                            dy[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };



/* eof */
#endif
