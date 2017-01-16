// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndFencing.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

struct FoxAndFencing {
    string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d) {
		if(mov1 + rng1 >= d) return "Ciel";// 第一步
		else if(mov2 + rng2 >= d + mov1) return "Liss";// 第二步
		else if(mov1 > mov2 && mov1 + rng1 >= rng2 + mov2 * 2 + 1) return "Ciel";// 如果mov1 > mov2，那么先手不败，之后再判断极限情况下是否能干掉后手
		else if(mov2 > mov1 && mov2 + rng2 >= rng1 + mov1 * 2 + 1) return "Liss";// 如果mov2 > mov1，那么后手不败，之后再判断极限情况下是否能干掉先手
		else return "Draw";// 否则平局
    }
};
