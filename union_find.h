/*
 * union-find header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2015-12-31
 */

#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

template<int n> class union_find {
	int r[n], c[n];
public:
	union_find() { clear(); }
	void clear() {
		for (int i = 0; i < n; ++i) {
			r[i] = i;
			c[i] = 1;
		}
	}
	int find(int x) { return x == r[x] ? x : r[x] = find(r[x]); }
	void merge(int u, int v) {
		int ru = find(u);
		int rv = find(v);
		if (ru == rv) return;
		if (c[ru] < c[rv]) swap(ru, rv);
		r[rv] = ru;
		c[ru] += c[rv];
	}
	bool is_merged(int x, int y) { return find(x) == find(y); }
	//check_merge
	bool cmerge(int u, int v) {
		int ru = find(u);
		int rv = find(v);
		if (ru == rv) return false;
		if (c[ru] < c[rv]) swap(ru, rv);
		r[rv] = ru;
		c[ru] += c[rv];
		return true;
	}
	int size(int x) { return c[find(x)]; }
};

/* eof */
#endif