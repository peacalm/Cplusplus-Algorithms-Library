/*
 * treap-tree header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-8-20
 */

#ifndef __TREAP_TREE_H__
#define __TREAP_TREE_H__

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
	treap_node_base(T v = 0) : val(v), weight(generate_weight()), subtree_size(1), father(0), left(0), right(0) {};
	//virtual ~treap_node_base() {}
	virtual void destroy() {}
	virtual void downpush() {}
	void print() {
		printf("val = %d\nweight = %d\n", val, weight);
		if (father) printf("father = %d\n", father->val);
		else printf("father = NULL\n");

		if (left) printf("left = %d\n", left->val);
		else printf("left = NULL\n");

		if (right) printf("right = %d\n", right->val);
		else printf("right = NULL\n");

		printf("subtree_size = %u\n", subtree_size);
		OUT();
	}
};
template<typename T, typename RandomWeightGenerator = default_random_weight_generator>
RandomWeightGenerator treap_node_base<T, RandomWeightGenerator>::generate_weight = RandomWeightGenerator();


//
template<typename T, typename TreapNode = treap_node_base<T> >
class treap_tree {
private:
	TreapNode* __root;
public:
	treap_tree(TreapNode* r = 0) : __root(r){}
	size_t size() const { return __root ? __root->subtree_size : 0; }
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
	TreapNode* find(const T& val) {
		return __find(__root, val);
	}
	void erase(const T& val) {
		return erase(__find(__root, val));
	}
	void erase(TreapNode* node) {
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
		node->destroy();
		delete node;
	}
	std::pair<treap_tree, treap_tree> split() {

	}
	treap_tree merge(treap_tree& l, treap_tree& r) {

	}
	void traversal() {
		OUT("traversal, root =", __root->val);
		dfs(__root);
	}
	void dfs(TreapNode *u){
		if (!u) return;
		dfs(u->left);
		std::cout << u->val << " " << u->weight << std::endl;
		u->print();
		dfs(u->right);
	}
private:
	TreapNode* __find(TreapNode* u, const T& val) {
		if (!u) return u;
		if (u->val < val) return __find(u->right, val);
		if (u->val > val) return __find(u->left, val);
		return u;
	}
	void __rotate(TreapNode* newnode) {
		while (newnode->father) {
			TreapNode* f = newnode->father;
			if (newnode->weight >= f->weight) break;
			if (newnode == (f->left)) __right_rotate(f);
			else __left_rotate(f);
		}
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
		if(l->right) l->right->father = f;
		l->right = f;
		f->father = l;
	}
};


/* eof */
#endif
