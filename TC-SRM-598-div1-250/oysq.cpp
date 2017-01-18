#line 5 "BinPacking.cpp"
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

const int N = 50;

struct BinPacking {
    int minBins(vector <int> item) {
		int n = SZ(item);
		std::sort(item.begin(), item.end());
		int c100 = 0, ans = 1e9;
		for(int i = 0; i < n; ++i) c100 += item[i] == 100;// c100 表示100的个数
		for(int a = 0; a <= c100 / 3; ++a) {// 枚举3个100合成一个300的个数
			int cur = a;
			for(int i = a * 3, j = n - 1; i < n; ++i) {// 剩下的贪心匹配
				if(i > j) break;
				cur++;
				while(j > i && item[i] + item[j] > 300) cur++, --j;
				if(i == j) break;
				else j--;
			}
			chkmin(ans, cur);
		}
		return ans;
    }
};
