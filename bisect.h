/*
 * bisect header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-8-23
 */

#ifndef __BISECT_H__
#define __BISECT_H__

// bisection

// return the min i in [l, r] which isok(i) is true. 
template<typename IntegerType, typename UnaryPredicate>
IntegerType bitsect_min(IntegerType l, IntegerType r, UnaryPredicate isok) {
	while (l < r) {
		IntegerType mid = (l + r) >> 1;
		if (isok(mid)) r = mid;
		else l = mid + 1;
	}
	return l;
}

// return the max i in [l, r] which isok(i) is true. 
template<typename IntegerType, typename UnaryPredicate>
IntegerType bitsect_max(IntegerType l, IntegerType r, UnaryPredicate isok) {
	while (l < r) {
		IntegerType mid = (l + r + 1) >> 1;
		if (isok(mid)) l = mid;
		else r = mid - 1;
	}
	return l;
}

/* eof */
#endif
