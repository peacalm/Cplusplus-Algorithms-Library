/*
 * splay-tree header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-8-25
 */

#ifndef __SPLAY_TREE_H__
#define __SPLAY_TREE_H__

#include "cil_config.h"
#include <cstdlib>
#include <utility>

template<typename T>
struct splay_node_base {
	T val;
	size_t subtree_size;
	splay_node_base(T v = 0) : val(v), subtree_size(1) {}
	virtual ~splay_node_base() {}
	virtual void downpush() {}
};

template<typename T>
struct default_splay_node : splay_node_base<T> {
	default_splay_node* father, *left, *right;
	default_splay_node(T v = 0): splay_node_base<T>(v), father(0), left(0), right(0) {}
};


template <typename T, typename SplayNode = default_splay_node<T> >
class splay_tree {
	SplayNode* __root;
public:
	splay_tree(SplayNode* r = 0) : __root(r) {}
	splay_tree(const splay_tree& rhs) : __root(rhs.__root) {}

	void destroy() { __destroy(__root); }
	void clear() { __destroy(__root); __root = 0; }
	size_t size() const { return __root->subtree_size; }
	SplayNode* root() const { return __root; }
	bool empty() const { return !__root; }

	SplayNode* insert(const T& v) {
		return insert(new SplayNode(v));
	}
#ifdef __cpp11
	template<typename ...Args>
	SplayNode* insert(const Args&... args) {
		return insert(new SplayNode(args...));
	}
#endif
	SplayNode* insert(SplayNode* newnode) {
		if (!__root) return __root = newnode;
		return __insert(__root, newnode);
	}
	SplayNode* find(const T& v) const {
		return __find(__root, v);
	}
	void erase(const T& v) {
		SplayNode *u;
		while (u = __find(__root, v)) erase(u);
	}
	void erase(SplayNode* u) {
		__erase(u);
	}
	void splay(const T& v) {
		__splay(__find(__root, v));
	}
	void splay(SplayNode* u) {
		__splay(u);
	}
	SplayNode* lower_bound(const T& v) const {
		return __lower_bound(__root, v);
	}
	SplayNode* upper_bound(const T& v) const {
		return __upper_bound(__root, v);
	}
	SplayNode* max_element() const {
		SplayNode* u = __root;
		if (!u) return u;
		u->downpush();
		while (u->right) {
			u = u->right;
			u->downpush();
		}
		return u;
	}
	SplayNode* min_element() const {
		SplayNode* u = __root;
		if (!u) return u;
		u->downpush();
		while (u->left) {
			u = u->left;
			u->downpush();
		}
		return u;
	}
	// {<, >=}
	std::pair<splay_tree, splay_tree> split(const T& v) {
		SplayNode* r = lower_bound(v);
		if (r == min_element())
			return std::make_pair(splay_tree(NULL), *this);
		if (r == max_element())
			return std::make_pair(*this, splay_tree(NULL));

		__splay(r);
		SplayNode* l = r->left;
		l->father = 0;
		r->left = 0;
		r->subtree_size -= l->subtree_size;
		return std::make_pair(splay_tree(l), splay_tree(r));
	}
	// caller should make sure l <= r
	splay_tree& merge(const splay_tree& rhs) {
		__root = __merge(__root, rhs.__root);
		return *this;
	}


private:
	void __destroy(SplayNode* u) {
		if (!u) return;
		__destroy(u->left);
		__destroy(u->right);
		delete u;
	}
	SplayNode* __merge(SplayNode* l, SplayNode* r) {
		if (!l) return r;
		if (!r) return l;
		if (l->subtree_size > r->subtree_size) {
			l->downpush();
			l->subtree_size += r->subtree_size;
			SplayNode* rret = __merge(l->right, r);
			rret->father = l;
			l->right = rret;
			return l;
		}
		else {
			r->downpush();
			r->subtree_size += l->subtree_size;
			SplayNode* lret = __merge(l, r->left);
			lret->father = r;
			r->left = lret;
			return r;
		}
	}
	SplayNode* __upper_bound(SplayNode* u, const T& v) const {
		if (!u) return u;
		if (u->val <= v) return __upper_bound(u->right, v);
		SplayNode* lret = __upper_bound(u->left, v);
		return lret ? lret : u;
	}
	SplayNode* __lower_bound(SplayNode* u, const T& v) const {
		if (!u) return u;
		if (u->val < v) return __lower_bound(u->right, v);
		SplayNode* lret = __lower_bound(u->left, v);
		return lret ? lret : u;
	}
	void __splay(SplayNode* u) {
		while (u->father) {
			if (u == u->father->left) __right_rotate(u->father);
			else __left_rotate(u->father);
		}
	}
	void __erase(SplayNode* u) {
		u->downpush();
		while (u->left && u->right) {
			if (u->left->subtree_size > u->right->subtree_size) {
				__right_rotate(u);
			}
			else {
				__left_rotate(u);
			}
		}
		SplayNode* f = u->father;
		while (f) {
			--(f->subtree_size);
			f = f->father;
		}
		if (u->left) {
			u->left->father = u->father;
			if (u == __root) __root = u->left;
			else {
				if (u == u->father->left) u->father->left = u->left;
				else u->fathe->right = u->left;
			}
		}
		else if (u->right) {
			u->right->father = u->father;
			if (u == __root) __root = u->right;
			else {
				if (u == u->father->left) u->father->left = u->right;
				else u->father->right = u->right;
			}
		}
		else {
			if (u == __root) __root = NULL;
			else {
				if (u == u->father->left) u->father->left = NULL;
				else u->father->right = NULL;
			}
		}
	}
	void __left_rotate(SplayNode* u) {
		SplayNode* r = u->right;
		u->downpush();
		r->downpush();
		u->subtree_size -= 1 + (r->right ? r->right->subtree_size : 0);
		r->subtree_size += 1 + (u->left ? u->left->subtree_size : 0);
		r->father = u->father;
		if (u == __root) __root = r;
		else {
			if (u == u->father->left) u->father->left = r;
			else u->father->right = r;
		}
		u->right = r->left;
		if (r->left) r->left->father = u;
		u->father = r;
		r->left = u;
	}
	void __right_rotate(SplayNode* u) {
		SplayNode* l = u->left;
		u->downpush();
		l->downpush();
		u->subtree_size -= 1 + (l->left ? l->left->subtree_size : 0);
		l->subtree_size += 1 + (u->right ? u->right->subtree_size : 0);
		l->father = u->father;
		if (u == __root) __root = l;
		else {
			if (u == u->father->left) u->father->left = l;
			else u->father->right = l;
		}
		u->left = l->right;
		if (l->right) l->right->father = u;
		u->father = l;
		l->right = u;
	}
	SplayNode* __find(SplayNode* u, const T& v) const {
		if (!u) return u;
		if (v < u->val) return __find(u->left, v);
		if (v > u->val) return __find(u->right, v);
		return u;
	}
	SplayNode* __insert(SplayNode* u, SplayNode* newnode) {
		++(u->subtree_size);
		u->downpush();
		if (newnode->val < u->val) {
			if (u->left) return __insert(u->left, newnode);
			u->left = newnode;
			newnode->father = u;
			return newnode;
		}
		else {
			if (u->right) return __insert(u->right, newnode);
			u->right = newnode;
			newnode->father = u;
			return newnode;
		}
	}
};


/* eof */
#endif