#line 2 "EelAndRabbit.cpp"  
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

class EelAndRabbit {  
public:  
	int getmax(vector <int> l, vector <int> t) {
		int n = SZ(l), ret = 0;
		for(int i = 0; i < n; ++i)
			for(int j = i; j < n; ++j) {// 枚举两抓鱼的时间
				int cnt = 0;
				for(int k = 0; k < n; ++k)// 判断能抓到多少鱼
					if((t[i] - t[k] >= 0 && t[i] - t[k] - l[k] <= 0) || (t[j] - t[k] >= 0 && t[j] - t[k] - l[k] <= 0))
						cnt++;
				chkmax(ret, cnt);// 更新答案
			}
		return ret;
	}    
};  
