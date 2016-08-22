/*
 * treap-tree header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-8-20
 */

#ifndef __TREAP_TREE_H__
#define __TREAP_TREE_H__

#include <cassert>
#include <cstdlib>
#include <iostream>

struct default_random_weight_generator {
	int operator()() const {
		return rand() << 15 | rand();
	}
};

template<typename T, typename RandomWeightGenerator = default_random_weight_generator>
struct treap_node_base {
	T val;
	int weight;
	size_t subtree_size;
	treap_node_base* father, *left, *right;
	static RandomWeightGenerator generate_weight;
	treap_node_base(T v = 0) : val(v), weight(generate_weight()), subtree_size(1)
		, father(0), left(0), right(0)
	{}
	virtual void downpush() {}
};
template<typename T, typename RandomWeightGenerator>
RandomWeightGenerator treap_node_base<T, RandomWeightGenerator>::generate_weight = RandomWeightGenerator();


//
template<typename T, typename TreapNode = treap_node_base<T> >
class treap_tree {
private:
	TreapNode* __root;
public:
	treap_tree(TreapNode* r = 0) : __root(r) {}
	treap_tree(const treap_tree& tt) : __root(tt.__root) {}

	void destroy() { __destroy(__root); }
	void clear() { __destroy(__root); __root = 0; }
	size_t size() const { return __root ? __root->subtree_size : 0; }
	bool empty() const { return !__root; }
	TreapNode* root() const { return __root; }

	TreapNode* insert(const T& val) {
		TreapNode* newnode = new TreapNode(val);
		return insert(newnode);
	}
	TreapNode* insert(TreapNode* newnode) {
		if (!__root) {
			__root = newnode;
			return newnode;
		}
		__insert(__root, newnode);
		__rotate(newnode);
		return newnode;
	}
	void erase(const T& val) {
		TreapNode* pos;
		while (pos = __find(__root, val))
			__erase(pos);
	}
	void erase(TreapNode* node) {
		if (!node) return;
		__erase(node);
	}
	TreapNode* find(const T& val) const {
		return __find(__root, val);
	}
	//{<, >=}
	std::pair<treap_tree, treap_tree> split(const T& k) {
		TreapNode* l, *r;
		__split(__root, k, l, r);
		return std::make_pair(treap_tree(l), treap_tree(r));
	}
	// make sure l <= r
	treap_tree& merge(treap_tree& rhs) {
		__root = __merge(__root, rhs.__root);
		return *this;
	}
	void downpush_all() {
		__downpush_all(__root);
	}
	TreapNode* max_element() const {
		TreapNode* u = __root;
		assert(u);
		u->downpush();
		while (u->right) {
			u = u->right;
			u->downpush();
		}
		return u;
	}
	TreapNode* min_element() const {
		TreapNode* u = __root;
		assert(u);
		u->downpush();
		while (u->left) {
			u = u->left;
			u->downpush();
		}
		return u;
	}
private:
	void __destroy(TreapNode* u) {
		if (!u) return;
		__destroy(u->left);
		__destroy(u->right);
		delete u;
	}
	void __downpush_all(TreapNode* u) {
		if (!u) return;
		u->downpush();
		__downpush_all(u->left);
		__downpush_all(u->right);
	}
	TreapNode* __merge(TreapNode* l, TreapNode* r) {
		if (!l) return r;
		if (!r) return l;
		l->downpush();
		r->downpush();
		if (l->weight < r->weight) {
			l->subtree_size += r->subtree_size;
			r = __merge(l->right, r);
			l->right = r;
			r->father = l;
			return l;
		}
		else {
			r->subtree_size += l->subtree_size;
			l = __merge(l, r->left);
			l->father = r;
			r->left = l;
			return r;
		}
	}
	void __split(TreapNode* u, const T& k, TreapNode* &l, TreapNode* &r) {
		if (!u) {
			l = r = NULL;
			return;
		}
		u->downpush();
		if (u->val < k) {
			__split(u->right, k, l, r);
			if (r) u->subtree_size -= r->subtree_size;
			u->right = l;
			if (l) l->father = u;
			if (r) r->father = NULL;
			l = u;
		}
		else {
			__split(u->left, k, l, r);
			if (l) u->subtree_size -= l->subtree_size;
			u->left = r;
			if (r) r->father = u;
			if(l) l->father = NULL;
			r = u;
		}
	}
	TreapNode* __find(TreapNode* u, const T& val) const {
		if (!u) return u;
		if (u->val < val) return __find(u->right, val);
		if (u->val > val) return __find(u->left, val);
		return u;
	}
	void __erase(TreapNode* node) {
		node->downpush();
		while (node->left && node->right) {
			if (node->left->weight < node->right->weight) __right_rotate(node);
			else __left_rotate(node);
		}
		TreapNode *f = node->father;
		while (f) {
			--(f->subtree_size);
			f = f->father;
		}
		if (node->left) {
			node->left->father = node->father;
			if (node == __root) __root = node->left;
			else {
				if (node == node->father->left) node->father->left = node->left;
				else node->father->right = node->left;
			}
		}
		else if (node->right) {
			node->right->father = node->father;
			if (node == __root) __root = node->right;
			else {
				if (node == node->father->left) node->father->left = node->right;
				else node->father->right = node->right;
			}
		}
		else {
			if (node == __root) __root = NULL;
			else {
				if (node == node->father->left) node->father->left = NULL;
				else node->father->right = NULL;
			}
		}
		delete node;
	}
	TreapNode* __insert(TreapNode* cur, TreapNode* newnode) {
		++(cur->subtree_size);
		cur->downpush();
		if (newnode->val < cur->val) {
			if (cur->left != 0)
				return __insert(cur->left, newnode);
			cur->left = newnode;
			newnode->father = cur;
			return newnode;
		}
		else {
			if (cur->right != 0)
				return __insert(cur->right, newnode);
			cur->right = newnode;
			newnode->father = cur;
			return newnode;
		}
	}
	void __rotate(TreapNode* newnode) {
		while (newnode->father) {
			TreapNode* f = newnode->father;
			if (newnode->weight >= f->weight) break;
			if (newnode == (f->left)) __right_rotate(f);
			else __left_rotate(f);
		}
	}
	void __left_rotate(TreapNode* f) {
		TreapNode* r = f->right;
		f->downpush();
		r->downpush();
		--(f->subtree_size);
		if (r->right) f->subtree_size -= r->right->subtree_size;
		++(r->subtree_size);
		if (f->left) r->subtree_size += f->left->subtree_size;

		r->father = f->father;
		if (f == __root) __root = r;
		else {
			if (f->father->left == f) f->father->left = r;
			else f->father->right = r;
		}
		f->right = r->left;
		if (r->left) r->left->father = f;
		r->left = f;
		f->father = r;
	}
	void __right_rotate(TreapNode* f) {
		TreapNode* l = f->left;
		f->downpush();
		l->downpush();
		--(f->subtree_size);
		if (l->left) f->subtree_size -= l->left->subtree_size;
		++(l->subtree_size);
		if (f->right) l->subtree_size += f->right->subtree_size;

		l->father = f->father;
		if (f == __root) __root = l;
		else {
			if (f->father->left == f) f->father->left = l;
			else f->father->right = l;
		}
		f->left = l->right;
		if (l->right) l->right->father = f;
		l->right = f;
		f->father = l;
	}
};


/* eof */
#endif
