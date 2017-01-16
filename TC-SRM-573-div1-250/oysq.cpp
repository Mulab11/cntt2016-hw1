#line 2 "TeamContest.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}


class TeamContest {  
public:  
	int worstRank(vector <int> a) {
		std::sort(a.begin(), a.begin() + 3);
		std::sort(a.begin() + 3, a.end());// 把剩下的从小到大排序
		int sum = a[0] + a[2], ret = 1;
		for(int i = SZ(a) - 1, j = 3; i - j >= 2; --i) {// 贪心匹配，每次选最大的+最小的能满足条件的即可
			while(i - j >= 2 && a[j] + a[i] <= sum) ++j;
			if(i - j < 2) break;
			ret++, j += 2;
		}
		return ret;
	}    
};  
