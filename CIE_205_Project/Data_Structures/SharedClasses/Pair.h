#pragma once
template <typename U,typename T>
struct Pair {
	U left;
	T right;
	Pair(U l, T r) { left = l; right = r; }
	Pair() {};
};