#pragma once
template <typename U,typename T>
struct Pairs {
	U left;
	T right;
	Pairs(U l, T r) { left = l; right = r; }
	Pairs() {};
};