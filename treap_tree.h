/*
* treap-tree header.
* written by Shuangquan Li, lishq991@gmail.com
* created on 2016-8-20
*/

#ifndef __TREAP_TREE_H__
#define __TREAP_TREE_H__

#include <cstdlib>
#include <iostream>

template<typename T>
struct treap_node_base {
	T val;
	int weight;
	size_t subtree_size;
	treap_node_base* father, *left, *right;
	treap_node_base(T v = 0) : val(v), weight(generate_weight()), subtree_size(1), father(0), left(0), right(0) {};
	static int generate_weight();
	virtual ~treap_node_base() {}
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
template<typename T>
int treap_node_base<T>::generate_weight() {
	return rand() << 15 | rand();
}


//
template<typename T, typename TreapNode = treap_node_base<T> >
class treap_tree {
private:
	TreapNode* __root;
public:
	treap_tree(TreapNode* r = 0) : __root(r){}
	size_t size() const { return __root->subtree_size; }
	TreapNode* insert(T newval) {
		TreapNode* newnode = new TreapNode(newval);
		return insert(newnode);
	}
	TreapNode* insert(TreapNode* newnode) {
		OUT("insert ", newnode->val);
		if (!__root) {
			__root = newnode;
			newnode->print();
			return newnode;
		}
		__insert(__root, newnode);
		__rotate(newnode);
		newnode->print();
		return newnode;
	}
	std::pair<treap_tree, treap_tree> split() {

	}
	void traversal() {
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
	void __rotate(TreapNode* newnode) {
		while (newnode->father) {
			TreapNode* f = newnode->father;
			std::cout << std::endl;
			if (newnode->weight < f->weight) {
				if (newnode == (f->left) )
					__right_rotate(f);
				else 
					__left_rotate(f);
			}
			else
				break;
		}
	}
	TreapNode* __insert(TreapNode* cur, TreapNode* newnode) {
		++(cur->subtree_size);
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