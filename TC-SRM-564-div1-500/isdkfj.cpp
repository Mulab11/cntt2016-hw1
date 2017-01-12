#include <bits/stdc++.h>

using namespace std;


class AlternateColors2 {
public:
	long long countWays(int n, int k) {
		long long ret=0;
		if(k%3==1)ret=(n-k+2ll)*(n-k+1ll)/2;//rgb都有 
		for(int i=0;i*3<k-1;++i){
			int t=k-1-i*3;
			if(t%2==0)ret+=2*(n-k+1);//rb或者rg 
			ret+=(t-1)/2*2+1;//r
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
