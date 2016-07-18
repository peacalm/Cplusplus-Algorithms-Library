/*
 * palindromic-tree header
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-27
 */

#ifndef __PALINDROMIC_TREE_H__
#define __PALINDROMIC_TREE_H__
#include <cassert>
#include <cstring>
#include <string>
using std::string;

template<int MAX_STR_LEN = 1000000, int CHAR_SET_SIZE = 26> class palindromic_tree {
	char str[MAX_STR_LEN]; // record original string, also used to find palindromic substrings if needed
	int n; // tail index of str
	// each of the struct node represents a palindrome
	struct palindrome {
		int len; // length of this palindrome
		int link; // links to the max one of right-side-fixed palindromic substring
		int dup; // time of occurence of this palindrome in original string
		int next[CHAR_SET_SIZE]; // children nodes, palindromes formed by add a char to both head and tail of this palindrome
		char *addr; // used to get palindrome string
		string get_str() const{ return len <= 0 ? "[node for help]" : string(addr, len); }
	};
	palindrome p[MAX_STR_LEN];
	int pcnt; // number of nodes, size of this tree
	int last; // id of last palindrome node added
	// add a new palindrome node, return it's id
	int add_node(int _len, int _link = 0, int _dup = 0) {
		p[pcnt].len = _len;
		p[pcnt].link = _link;
		p[pcnt].dup = _dup;
		memset(p[pcnt].next, 0, sizeof(p[pcnt].next));
		p[pcnt].addr = str + n - _len;
		return pcnt++;
	}
	// get the father node, who adds a char to both it's head and tail can form current palindrome node
	int get_father(int u) {
		while (str[n - 1] != str[n - p[u].len - 2]) u = p[u].link;
		return u;
	}
public:
	palindromic_tree() { init(); }
	void init() {
		n = 0;
		str[n++] = -1; // add a char not in char-set to avoid specially judge
		pcnt = 0;
		// it is specially designed the first two node, to avoid specially judge
		// node-0'length equals to 0, links to 1
		// node-1'length equals to -1, links to self, and its next array all pointed to 0 originally.
		add_node(0, 1); // root of even-length palindromes
		add_node(-1, 1); // root of odd-length palindromes
		last = 0;
	}
	const palindrome& operator[](int i) const { return p[i]; }
	int size() const { return pcnt; }
	void add_char(char c, char base = 0) {
		str[n++] = c;
		c -= base;
		assert(c >= 0 && c < CHAR_SET_SIZE);
		int fa = get_father(last);
		if (!p[fa].next[c]) {
			int t = add_node(p[fa].len + 2, p[get_father(p[fa].link)].next[c], 1);
			last = p[fa].next[c] = t;
		}
		else {
			last = p[fa].next[c];
			++p[last].dup;
		}
	}
	// one last work to count occurrence times of each palindrome nodes
	void finishing_touch() {
		for (int i = pcnt - 1; i >= 0; --i)
			p[p[i].link].dup += p[i].dup;
	}
	void add_string(char* s, char base = 0) {
		while (*s) add_char(*s++, base);
		finishing_touch();
	}
	void add_string(const string& s, char base = 0) {
		for (int i = 0; i < s.size(); ++i) add_char(s[i], base);
		finishing_touch();
	}
	int count_total_palindromes() const {
		int ret = 0;
		for (int i = pcnt - 1; i >= 2; --i) ret += p[i].dup;
		return ret;
	}
	int count_different_palindromes() const { return pcnt - 2; }
};



/* eof */
#endif