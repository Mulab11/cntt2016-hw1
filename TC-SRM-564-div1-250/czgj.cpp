/*
	Easy conclusion.
	No comment.
*/
#include <bits/stdc++.h>
using namespace std;
class KnightCircuit2 {
	public:
	int maxSize(int w, int h) {
		if (w > h) swap(w, h);
		if (w == 1) return 1;
		if (w == 2) return (h + 1) / 2;
		return w * h - (w == 3 && h == 3);
	}
};

/*
	Who's Afraid of the Big Black?
		- With EZHTNF
*/
