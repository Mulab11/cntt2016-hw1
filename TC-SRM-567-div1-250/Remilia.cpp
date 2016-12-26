#include <bits/stdc++.h>

using namespace std;

struct TheSquareRootDilemma {
	int countPairs(int, int);
};

int L[101000],R[101000];

int TheSquareRootDilemma::countPairs(int N, int M) {
	// 枚举第一个数，搞掉sqf
	for (int i = 1; i <= N; i++){
		int xjb = i;
		for (int j = 2; j * j <= i; j++)
			while (xjb % (j * j) == 0)
				xjb /= j * j;
		L[xjb]++;
	}
	// 枚举第二个数，搞掉sqf
	for (int i = 1; i <= M; i++){
		int xjb = i;
		for (int j = 2; j * j <= i; j++)
			while (xjb % (j * j) == 0)
				xjb /= j * j;
		R[xjb]++;
	}
	// 每个sqf的答案
	int ans = 0;
	for (int i = 1; i <= 100000; i++)
		ans += L[i] * R[i];
	return ans;
}