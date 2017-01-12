#include <bits/stdc++.h>

using namespace std;


class FoxPaintingBalls {
public:
	long long theMax(long long R, long long G, long long B, int N) {
		long long k=1ll*N*(N+1)/6;//每种颜色有几个 
		if(N%3!=1)return min(min(R,G),B)/k;//直接算答案 
		if(N==1)return R+G+B;//特判 
		long long ret=min(min(R,G),B)/k; 
		return min(ret,(R+G+B)/(3*k+1));//n%3=1的情况 
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
