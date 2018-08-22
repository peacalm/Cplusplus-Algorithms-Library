/*
 * sorts header
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-19
 * last edit on 2016-7-11
 */

/* *****************************************************************************

////// FUNCTION PROTOTYPES


// find the k-th minimum element

template<typename RandomAccessIterator, typename Compare>
typename std::iterator_traits<RandomAccessIterator>::value_type
find_kth_min(size_t k, RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template<typename RandomAccessIterator>
typename std::iterator_traits<RandomAccessIterator>::value_type
find_kth_min(size_t k, RandomAccessIterator first, RandomAccessIterator last);

template<typename Container>
typename Container::value_type
find_kth_min(size_t k, Container& c);

template<typename Container, typename Compare>
typename Container::value_type
find_kth_min(size_t k, Container& c, Compare comp);

template<typename T>
T find_kth_min(size_t k, T* array, size_t n);


// count inversions while merge sort

template<typename RandomAccessIterator, typename Compare>
void cil_count_inversions_while_merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp, long long& cnt);

template<typename RandomAccessIterator, typename Compare>
long long count_inversions_while_merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template<typename RandomAccessIterator>
long long count_inversions_while_merge_sort(RandomAccessIterator first, RandomAccessIterator last);

template<typename Container>
long long count_inversions_while_merge_sort(Container& c);

template<typename Container, typename Compare>
long long count_inversions_while_merge_sort(Container& c, Compare comp);

template<typename T>
long long count_inversions_while_merge_sort(T* array, size_t n);


//// sort functions

// quick sort

template<typename RandomAccessIterator, typename Compare>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template<typename RandomAccessIterator>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last);

template<typename Container>
void quick_sort(Container& c);

template<typename Container, typename Compare>
void quick_sort(Container& c, Compare comp);

template<typename T>
void quick_sort(T* array, size_t n);


// merge sort

template<typename RandomAccessIterator, typename Compare>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template<typename RandomAccessIterator>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last);

template<typename Container>
void merge_sort(Container& c);

template<typename Container, typename Compare>
void merge_sort(Container& c, Compare comp);

template<typename T>
void merge_sort(T* array, size_t n);


// heap_sort

template<typename RandomAccessIterator, typename Compare>
void heap_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

template<typename RandomAccessIterator>
void heap_sort(RandomAccessIterator first, RandomAccessIterator last);

template<typename Container>
void heap_sort(Container& c);

template<typename Container, typename Compare>
void heap_sort(Container& c, Compare comp);

template<typename T>
void heap_sort(T* array, size_t n);


// radix_sort

template<typename RandomAccessIterator>
void radix_sort(RandomAccessIterator first, RandomAccessIterator last);

template<typename Container>
void radix_sort(Container& c);

template<typename IntegerType>
void radix_sort(IntegerType* c, int n);


// select sort

template<typename ForwardIterator, typename Compare>
void select_sort(ForwardIterator first, ForwardIterator last, Compare comp);

template<typename ForwardIterator>
void select_sort(ForwardIterator first, ForwardIterator last);

template<typename Container>
void select_sort(Container& c);

template<typename Container, typename Compare>
void select_sort(Container& c, Compare comp);

template<typename T>
void select_sort(T* array, size_t n);


// insert_sort

template <typename BidirectionalIterator>
void insert_sort(BidirectionalIterator first, BidirectionalIterator last);

template <typename BidirectionalIterator, typename Compare>
void insert_sort(BidirectionalIterator first, BidirectionalIterator last, Compare comp);

template <typename Container>
void insert_sort(Container& c);

template <typename Container, typename Compare>
void insert_sort(Container& c, Compare comp);

template <typename T>
void insert_sort(T* array, size_t n);


// bubble_sort

template<typename ForwardIterator>
void bubble_sort(ForwardIterator first, ForwardIterator last);

template<typename ForwardIterator, typename Compare>
void bubble_sort(ForwardIterator first, ForwardIterator last, Compare comp);

template<typename Container>
void bubble_sort(Container& c);

template<typename Container, typename Compare>
void bubble_sort(Container& c, Compare comp);

template<typename T>
void bubble_sort(T* array, size_t n);

***************************************************************************** */

#ifndef __SORTS_H__
#define __SORTS_H__

#include <algorithm>
#include <iterator>
#include <functional>


// find the k-th minimum element

template<typename RandomAccessIterator, typename Compare>
typename std::iterator_traits<RandomAccessIterator>::value_type
find_kth_min(size_t k, RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
	int n = last - first;
	RandomAccessIterator mid = first + n / 2;
	if (comp(*mid, *first)) std::swap(*first, *mid);
	if (comp(*(last - 1), *first)) std::swap(*first, *(last - 1));
	if (comp(*(last - 1), *mid)) std::swap(*mid, *(last - 1));
	if (n <= 3) {
		assert(k <= 3);
		return *(first + k - 1);
	}
	typename std::iterator_traits<RandomAccessIterator>::value_type pivot = *mid;
	std::swap(*mid, *(last - 2));
	RandomAccessIterator left = first, right = last - 2;
	while (true) {
		while (comp(*++left, pivot));
		while (comp(pivot, *--right));
		if (left < right) std::swap(*left, *right);
		else break;
	}
	std::swap(*left, *(last - 2));
	size_t pivot_id = left - first + 1;
	if (k < pivot_id) return find_kth_min(k, first, left, comp);
	else if (k > pivot_id) find_kth_min(k - pivot_id, left + 1, last, comp);
	else return pivot;
}

template<typename RandomAccessIterator>
inline typename std::iterator_traits<RandomAccessIterator>::value_type
find_kth_min(size_t k, RandomAccessIterator first, RandomAccessIterator last) {
	return find_kth_min(k, first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<typename Container>
inline typename Container::value_type
find_kth_min(size_t k, Container& c) {
	return find_kth_min(k, c.begin(), c.end());
}

template<typename Container, typename Compare>
inline typename Container::value_type
find_kth_min(size_t k, Container& c, Compare comp) {
	return find_kth_min(k, c.begin(), c.end(), comp);
}

template<typename T>
inline T find_kth_min(size_t k, T* array, size_t n) {
	return find_kth_min(k, array, array + n);
}


// count inversions while merge sort

template<typename RandomAccessIterator, typename Compare>
void cil_count_inversions_while_merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp, long long& cnt) {
	if (first + 1 >= last) return;
	int n = last - first;
	RandomAccessIterator mid = first + n / 2;
	cil_count_inversions_while_merge_sort(first, mid, comp, cnt);
	cil_count_inversions_while_merge_sort(mid, last, comp, cnt);
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
	value_type* tmp = new value_type[n];
	RandomAccessIterator left = first, right = mid;
	for (size_t i = 0; i < n; ++i) {
		if (right == last || (left != mid && !comp(*right, *left))) {
			tmp[i] = *left++;
			cnt += right - mid;
		}
		else
			tmp[i] = *right++;
	}
	for (size_t i = 0; i < n; ++i) *first++ = tmp[i];
	delete[] tmp;
}

template<typename RandomAccessIterator, typename Compare>
inline long long count_inversions_while_merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
	long long cnt = 0;
	cil_count_inversions_while_merge_sort(first, last, comp, cnt);
	return cnt;
}

template<typename RandomAccessIterator>
inline long long count_inversions_while_merge_sort(RandomAccessIterator first, RandomAccessIterator last) {
	long long cnt = 0;
	cil_count_inversions_while_merge_sort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>(), cnt);
	return cnt;
}

template<typename Container>
inline long long count_inversions_while_merge_sort(Container& c) {
	return count_inversions_while_merge_sort(c.begin(), c.end());
}

template<typename Container, typename Compare>
inline long long count_inversions_while_merge_sort(Container& c, Compare comp) {
	return count_inversions_while_merge_sort(c.begin(), c.end(), comp);
}

template<typename T>
inline long long count_inversions_while_merge_sort(T* array, size_t n) {
	return count_inversions_while_merge_sort(array, array + n);
}


//// sort functions

// quick sort

template<typename RandomAccessIterator, typename Compare>
void quick_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
	int n = last - first;
	RandomAccessIterator mid = first + n / 2;
	if (comp(*mid, *first)) std::swap(*first, *mid);
	if (comp(*(last - 1), *first)) std::swap(*first, *(last - 1));
	if (comp(*(last - 1), *mid)) std::swap(*mid, *(last - 1));
	if (n <= 3) return;
	typename std::iterator_traits<RandomAccessIterator>::value_type pivot = *mid;
	std::swap(*mid, *(last - 2));
	RandomAccessIterator left = first, right = last - 2;
	while (true) {
		while (comp(*++left, pivot));
		while (comp(pivot, *--right));
		if (left < right) std::swap(*left, *right);
		else break;
	}
	std::swap(*left, *(last - 2));
	quick_sort(first, left, comp);
	quick_sort(left + 1, last, comp);
}

template<typename RandomAccessIterator>
inline void quick_sort(RandomAccessIterator first, RandomAccessIterator last) {
	quick_sort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<typename Container>
inline void quick_sort(Container& c) {
	quick_sort(c.begin(), c.end());
}

template<typename Container, typename Compare>
inline void quick_sort(Container& c, Compare comp) {
	quick_sort(c.begin(), c.end(), comp);
}

template<typename T>
inline void quick_sort(T* array, size_t n) {
	quick_sort(array, array + n);
}


// merge sort

template<typename RandomAccessIterator, typename Compare>
void merge_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
	if (first + 1 >= last) return;
	int n = last - first;
	RandomAccessIterator mid = first + n / 2;
	merge_sort(first, mid, comp);
	merge_sort(mid, last, comp);
#if false
	std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> tmp(n);
	std::merge(first, mid, mid, last, tmp.begin(), comp);
	for (size_t i = 0; i < n; ++i) *first++ = tmp[i];
#else
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
	value_type* tmp = new value_type[n];
	RandomAccessIterator left = first, right = mid;
	for (size_t i = 0; i < n; ++i) {
		if (right == last || (left != mid && comp(*left, *right)))
			tmp[i] = *left++;
		else
			tmp[i] = *right++;
	}
	for (size_t i = 0; i < n; ++i) *first++ = tmp[i];
	delete[] tmp;
#endif
}

template<typename RandomAccessIterator>
inline void merge_sort(RandomAccessIterator first, RandomAccessIterator last) {
	merge_sort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<typename Container>
inline void merge_sort(Container& c) {
	merge_sort(c.begin(), c.end());
}

template<typename Container, typename Compare>
inline void merge_sort(Container& c, Compare comp) {
	merge_sort(c.begin(), c.end(), comp);
}

template<typename T>
inline void merge_sort(T* array, size_t n) {
	merge_sort(array, array + n);
}


// heap_sort

//template<typename RandomAccessIterator, typename Compare>
//void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
//	RandomAccessIterator root = first + (last - first - 2) / 2;
//	while (true) {
//		RandomAccessIterator hole = root;
//		typename std::iterator_traits<RandomAccessIterator>::value_type tmp = *hole;
//		for (RandomAccessIterator child = first + (hole - first) * 2 + 1; child < last;) {
//			if ((child + 1) < last && comp(*(child + 1), *child)) ++child;
//			if (comp(*child, tmp)) {
//				*hole = *child;
//				hole = child;
//				child = first + (hole - first) * 2 + 1;
//			}
//			else break;
//		}
//		*hole = tmp;
//		if (root == first) break;
//		else --root;
//	}
//}
//template<typename RandomAccessIterator>
//inline void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
//	make_heap(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
//}

template<typename RandomAccessIterator, typename Compare>
void heap_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
	std::make_heap(first, last, comp);
	std::sort_heap(first, last, comp);
}

template<typename RandomAccessIterator>
inline void heap_sort(RandomAccessIterator first, RandomAccessIterator last) {
	heap_sort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

template<typename Container>
inline void heap_sort(Container& c) {
	heap_sort(c.begin(), c.end());
}

template<typename Container, typename Compare>
inline void heap_sort(Container& c, Compare comp) {
	heap_sort(c.begin(), c.end(), comp);
}

template<typename T>
inline void heap_sort(T* array, size_t n) {
	heap_sort(array, array + n);
}


// radix sort, for interger types

template<typename IntegerType>
void radix_sort(IntegerType* array, int n) {
	unsigned long long max_positive_element = 0;
	long long min_negetive_element = 0;
	for (int i = 0; i < n; ++i) {
		if (array[i] >= 0) {
			if (array[i] > max_positive_element)
				max_positive_element = array[i];
		}
		else {
			if (array[i] < min_negetive_element)
				min_negetive_element = array[i];
		}
	}
	int digits1 = 0, digits2 = 0;
	while (max_positive_element) {
		++digits1;
		max_positive_element /= 10;
	}
	while (min_negetive_element) {
		++digits2;
		min_negetive_element /= 10;
	}
	int digits = digits1 > digits2 ? digits1 : digits2;

	int* cnt = new int[19];
	int* rem = new int[n];
	IntegerType* tmp = new IntegerType[n];
	IntegerType* num = array, *to = tmp;
	for (long long i = 0, radix = 1; i < digits; ++i, radix *= 10) {
		memset(cnt, 0, sizeof(cnt[0]) * 19);
		for (int j = 0; j < n; ++j) {
			rem[j] = num[j] / radix % 10 + 9;
			++cnt[rem[j]];
		}
		for (int j = 1; j < 19; ++j) cnt[j] += cnt[j - 1];
		for (int j = n - 1; j >= 0; --j) {
			to[--cnt[rem[j]]] = num[j];
		}
		IntegerType* t = num;
		num = to;
		to = t;
	}
	if (num != array) memcpy(array, tmp, sizeof(array[0]) * n);
	delete[] tmp;
	delete[] rem;
	delete[] cnt;
}

template<typename RandomAccessIterator>
inline void radix_sort(RandomAccessIterator first, RandomAccessIterator last) {
	radix_sort(&(*first), int(last - first));
}

template<typename Container>
inline void radix_sort(Container &a) {
	radix_sort(&a[0], (int)(a.size()));
}


// select sort

template<typename ForwardIterator, typename Compare>
void select_sort(ForwardIterator first, ForwardIterator last, Compare comp) {
	while (first != last) {
		ForwardIterator selected = first;
		for (ForwardIterator it = first; ++it != last;)
			if (comp(*it, *selected)) selected = it;
		if (selected != first) {
			typename std::iterator_traits<ForwardIterator>::value_type tmp = *first;
			*first = *selected;
			*selected = tmp;
		}
		++first;
	}
}

template<typename ForwardIterator>
inline void select_sort(ForwardIterator first, ForwardIterator last) {
	select_sort(first, last, std::less<typename std::iterator_traits<ForwardIterator>::value_type>());
}

template<typename Container>
inline void select_sort(Container& c) {
	select_sort(c.begin(), c.end());
}

template<typename Container, typename Compare>
inline void select_sort(Container& c, Compare comp) {
	select_sort(c.begin(), c.end(), comp);
}

template<typename T>
inline void select_sort(T* array, size_t n) {
	select_sort(array, array + n);
}


// insert sort

template <typename BidirectionalIterator, typename Compare>
void insert_sort(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
	BidirectionalIterator it = first;
	++it;
	while (it != last) {
		typename std::iterator_traits<BidirectionalIterator>::value_type tmp = *it;
		BidirectionalIterator hole = it;
		++it;
		while (hole != first) {
			BidirectionalIterator prev = hole;
			--prev;
			if (comp(tmp, *prev)) {
				*hole = *prev;
				--hole;
			}
			else {
				break;
			}
		}
		*hole = tmp;
	}
}

template <typename BidirectionalIterator>
inline void insert_sort(BidirectionalIterator first, BidirectionalIterator last) {
	insert_sort(first, last, std::less<typename std::iterator_traits<BidirectionalIterator>::value_type>());
}

template <typename Container>
inline void insert_sort(Container& c) {
	insert_sort(c.begin(), c.end());
}

template <typename Container, typename Compare>
inline void insert_sort(Container& c, Compare comp) {
	insert_sort(c.begin(), c.end(), comp);
}

template <typename T>
void insert_sort(T* array, size_t n) {
	for (size_t i = 1; i < n; ++i) {
		if (array[i] >= array[i - 1]) continue;
		T tmp = array[i];
		array[i] = array[i - 1];
		size_t hole = i - 1;
		while (hole > 0) {
			if (tmp < array[hole - 1]) {
				array[hole] = array[hole - 1];
				--hole;
			}
			else break;
		}
		array[hole] = tmp;
	}
}



// bubble sort
// if BidirectionalIterator supported, bidirectional bubble may be better/

template<typename ForwardIterator, typename Compare>
void bubble_sort(ForwardIterator first, ForwardIterator last, Compare comp) {
	int inversion_cnt = 0;
	do {
		inversion_cnt = 0;
		ForwardIterator it = first;
		while (1) {
			ForwardIterator pre = it++;
			if (it == last) {
				last = pre;
				break;
			}
			if (!comp(*pre, *it)) {
				++inversion_cnt;
				typename std::iterator_traits<ForwardIterator>::value_type tmp = *pre;
				*pre = *it;
				*it = tmp;
			}
		}
	} while (inversion_cnt);
}

template<typename ForwardIterator>
void bubble_sort(ForwardIterator first, ForwardIterator last) {
	bubble_sort(first, last, std::less<typename std::iterator_traits<ForwardIterator>::value_type>());
}

template<typename Container>
inline void bubble_sort(Container& c) {
	bubble_sort(c.begin(), c.end());
}

template<typename Container, typename Compare>
inline void bubble_sort(Container& c, Compare comp) {
	bubble_sort(c.begin(), c.end(), comp);
}

template<typename T>
inline void bubble_sort(T* array, size_t n) {
	bubble_sort(array, array + n);
}

/* eof */
#endif