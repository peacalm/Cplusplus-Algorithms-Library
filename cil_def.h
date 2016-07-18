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


#define FOR(i, a, b)          for (long long i = (long long)(a); i < (long long)(b); ++i)
#define ROF(i, a, b)          for (long long i = (long long)(b) - 1; i >= (long long)(a); --i)
#define rep(i, a, b)          for (long long i = (long long)(a); i < (long long)(b); ++i)
#define per(i, a, b)          for (long long i = (long long)(b) - 1; i >= (long long)(a); --i)
#define REP(i, n)             for (long long i = 0; i < (long long)(n); ++i)
#define PER(i, n)             for (long long i = (long long)(n) - 1; i >= 0; --i)
#define DO(n)                 for (int _iDO_ = int(n); _iDO_--;)
#define rush()                int _CASES_; scanf("%d", &_CASES_); for (; _CASES_--;)
#define cases()               int _CASES_; scanf("%d", &_CASES_); for (int iCase = 1; (iCase <= _CASES_ && printf("Case #%d:\n", iCase)); ++iCase)
#define sqr(x)                ((x) * (x))
#define cub(x)                ((x) * (x) * (x))
#define all(x)                (x).begin(), (x).end()
#define sortall(x)            sort((x).begin(), (x).end())
#define reverseall(x)         reverse((x).begin(), (x).end())
#define sz(x)                 ((int)(x).size())
#define eb                    emplace_back
#define pb                    push_back
#define pf                    push_front
#define ppb                   pop_back
#define ppf                   pop_front
#define mp                    make_pair
#define pbmp(a, b)            push_back(make_pair((a), (b)))
#define fi                    first
#define se                    second
#define ms(a, b)              memset((a), (b), sizeof(a))
#define cp(a, b)              memcpy((a), (b), sizeof(a))
#define IOSS0                 std::ios::sync_with_stdio(false);cin.tie(false);
#define whatis(x)             cout << #x << " = " << x << endl;
#define uniqueit(v)           (v).erase(unique((v).begin(), (v).end()), (v).end())
#define insertlb(v, a)        (v).insert(lower_bound((v).begin(), (v).end(), (a)), (a))
#define insertub(v, a)        (v).insert(upper_bound((v).begin(), (v).end(), (a)), (a))
#define PQ                    priority_queue
#define uset                  unordered_set
#define mset                  multiset
#define umap                  unordered_map
#define mmap                  multimap
typedef double                db;
typedef long double           ldb;
typedef unsigned char         uchar;
typedef unsigned short        ushort;
typedef unsigned int          uint;
typedef long long             ll;
typedef unsigned long long    ull;
typedef vector<bool>          VB;
typedef vector<VB>            VVB;
typedef vector<char>          VC;
typedef vector<VC>            VVC;
typedef vector<int>           VI;
typedef vector<VI>            VVI;
typedef vector<ll>            VLL;
typedef vector<VLL>           VVLL;
typedef vector<double>        VD;
typedef vector<VD>            VVD;
typedef vector<string>        VS;
typedef vector<VS>            VVS;
typedef pair<int, int>        PII;
typedef pair<ll, ll>          PLL;
typedef vector<PII>           VPII;
typedef vector<PLL>           VPLL;
typedef pair<int, PII>        PIPII;
typedef pair<ll, PLL>         PLPLL;
typedef pair<PII, int>        PPIII;
typedef pair<PLL, ll>         PPLLL;
typedef map<int, int>         MII;
typedef map<ll, ll>           MLL;
typedef map<db, db>           MDD;
typedef map<string, int>      MSI;
typedef map<int, string>      MIS;
typedef set<int>              SI;
typedef set<ll>               SLL;
typedef queue<int>            QI;
typedef queue<ll>             QLL;
typedef queue<PII>            QPII;
typedef deque<int>            DI;
typedef deque<ll>             DLL;
typedef deque<PII>            DPII;
const double                  eps = 1e-9;
const double                  pi = 3.14159265358979323846264338327950288419716939937510;
const int                     inf = 0x3f3f3f3f;
const int                     mod = 1000000007;
const int                     mod2 = 1000000006;
const long long               infll = 0x3f3f3f3f3f3f3f3fLL;
const int                     dx[8] = { 0, 1, 0, -1, -1, 1, 1, -1 };
const int                     dy[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };


/* eof */
#endif