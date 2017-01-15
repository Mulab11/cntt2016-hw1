#line 5 "TomekPhone.cpp"
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
const int INF = 1e9;

int use[N + 9];// use[i] 表示第i个键位已经用了的空间

struct TomekPhone {
    int minKeystrokes(vector <int> freq, vector <int> keys) {// 贪心
		int n = SZ(freq);// n 表示字母个数
		std::sort(freq.begin(), freq.end());// 从小到大排序
		memset(use, 0, sizeof use);
		int ret = 0;
		for(int i = n - 1; i >= 0; --i) {// 从大到小填进去
			int mins = INF, id = -1;	
			for(int j = 0; j < SZ(keys); ++j)
				if(use[j] < keys[j] && use[j] < mins)
					mins = use[j], id = j;// 找到最小代价的键位填进去
			if(id == -1) return -1;// 填不下
			use[id]++;// 更新 use
			ret += freq[i] * use[id];// 更新答案
		}
		return ret;
    }
};
