#include <bits/stdc++.h>

using namespace std;

/*
先运行那一个子段，得知初始高度至少是多少
然后在前面放那么多个U，之后再判断一下能否到达hn即可
因为交换顺序是没有影响的
*/

struct FoxAndMountainEasy {
	string possible(int, int, int, string);
};

string FoxAndMountainEasy::possible(int n, int h0, int hn, string h) {
	int m = h.length(), i, x = h0;
	for (i=0;i<m;i++)
		if (h[i] == 'U') x++; else
		if (h[i] == 'D') x--;
	int d = x-hn;
	if (d < 0) d = -d;
	if (d > n-m) return "NO";
	if (d % 2 != (n-m) % 2) return "NO";
	int up = (n-m-d)/2;
	if (hn > x) up += hn-x;
	x = h0+up;
	for (i=0;i<m;i++) {
		if (h[i] == 'U') x++; else
		if (h[i] == 'D') x--;
		if (x < 0) return "NO";
	}
	return "YES";
}