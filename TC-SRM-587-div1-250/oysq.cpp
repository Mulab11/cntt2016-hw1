#line 2 "JumpFurther.cpp"  
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


class JumpFurther {  
public:  
	int furthest(int N, int badStep) {
		// 先假设如果每一步都走，那么高度是h = N(N + 1) / 2
		// 中途会碰到badStep那么答案肯定 < h的，这时我们只要不走第一步，就不会碰到了答案是h - 1
		int ans = N * (N + 1) / 2;
		for(int i = 1; i <= N; ++i)
			if(i * (i + 1) / 2 == badStep) {
				ans--;
				break;
			}
		return ans;
	}    
};  
