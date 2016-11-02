/*
 * mxor-solver header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-11-2
 */


#ifndef __MXOR_SOLVER_H__
#define __MXOR_SOLVER_H__

#include <cassert>
#include <memory>

// this class is designed to solve max/min xor problems, such as:
// given a integer array A, find the max/min xor result of any of two intgers in A.
// given a integer array A, find the number of integer pair whose xor result is
// greater than X(some given integer).


template<typename IntegerType, size_t MAX_BITS> class mxor_solver {
	struct Node {
		std::shared_ptr<Node> child[2]; // child[i] is child of bit i, i = 0, 1
		size_t dup; // duplicates of this node, also the size of subtree
		Node() : dup(0) {}
	};
	std::shared_ptr<Node> head;
public:
	mxor_solver() : head(new Node) {}

	// number of elements exist now
	size_t size() const { return head->dup; }

	// if number of elements equals to 0
	bool empty() const { return head->dup == 0; }

	// erase all elements
	void clear() { head.reset(new Node); }

	// insert a new element `val`
	void insert(const IntegerType& val) {
		std::shared_ptr<Node> cur = head;
		++(cur->dup);
		for (int i = MAX_BITS - 1; i >= 0; --i) {
			int B = val >> i & 1;
			if (cur->child[B])
				cur = cur->child[B];
			else
				cur = cur->child[B] = std::shared_ptr<Node>(new Node());
			++(cur->dup);
		}
	}

	// erase once occurrence of element whose value is `val`
	void erase(const IntegerType& val) {
		assert(count(val));
		std::shared_ptr<Node> cur = head;
		--(cur->dup);
		for (int i = MAX_BITS - 1; i >= 0; --i) {
			int B = val >> i & 1;
			--(cur->child[B]->dup);
			if (cur->child[B]->dup == 0) {
				cur->child[B].reset();
				return;
			}
			cur = cur->child[B];
		}
	}

	// count time of occurrence of element whose value is `val`
	size_t count(const IntegerType& val) const {
		std::shared_ptr<Node> cur = head;
		for (int i = MAX_BITS - 1; i >= 0; --i) {
			int B = val >> i & 1;
			if (!(cur->child[B])) return 0;
			cur = cur->child[B];
		}
		return cur->dup;
	}

	// query max xor result of all elements with `xorWithWhom`
	IntegerType query_max(const IntegerType& xorWithWhom = 0) const {
		assert(size());
		IntegerType ret = 0;
		std::shared_ptr<Node> cur = head;
		for (int i = MAX_BITS - 1; i >= 0; --i) {
			int B = xorWithWhom >> i & 1;
			if (cur->child[B ^ 1]) {
				ret |= IntegerType(1) << i;
				cur = cur->child[B ^ 1];
			}
			else {
				cur = cur->child[B];
			}
		}
		return ret;
	}

	// query min xor result of all elements with `xorWithWhom`
	IntegerType query_min(const IntegerType& xorWithWhom = 0) const {
		assert(size());
		IntegerType ret = 0;
		std::shared_ptr<Node> cur = head;
		for (int i = MAX_BITS - 1; i >= 0; --i) {
			int B = xorWithWhom >> i & 1;
			if (cur->child[B]) {
				cur = cur->child[B];
			}
			else {
				ret |= IntegerType(1) << i;
				cur = cur->child[B ^ 1];
			}
		}
		return ret;
	}

	// query the number of elements whose xor result with `xorWithWhom` is greater than `thanWhom`
	size_t query_gt(const IntegerType& xorWithWhom, const IntegerType& thanWhom) const {
		if (empty()) return 0;
		size_t ret = 0;
		std::shared_ptr<Node> cur = head;
		for (int i = MAX_BITS - 1; i >= 0; --i) {
			int W = xorWithWhom >> i & 1;
			int T = thanWhom >> i & 1;
			if (T) {
				if (cur->child[W ^ 1]) cur = cur->child[W ^ 1];
				else break;
			}
			else {
				if (cur->child[W ^ 1]) ret += cur->child[W ^ 1]->dup;
				if (cur->child[W]) cur = cur->child[W];
			}
		}
		return ret;
	}
};

/* eof */
#endif