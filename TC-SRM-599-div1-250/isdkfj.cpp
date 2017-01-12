#include <bits/stdc++.h>

using namespace std;


class BigFatInteger {
public:
	int minOperations(int A, int B) {
		int ret=0,mx=0;
		for(int i=2;i<=A;++i)
		if(A%i==0){
			long long t=0;
			while(A%i==0)A/=i,++t;
			t*=B;
			++ret;//多一个质因子 
			int tmp=0;
			while(t>1)t=(t+1)>>1,++tmp;//快速幂 
			mx=max(mx,tmp);
		}
		return ret+mx;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
