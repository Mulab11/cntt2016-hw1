#include <bits/stdc++.h>

using namespace std;


class TheTree {
public:
	int maximumDiameter(vector <int> cnt) {
		int n=cnt.size(),ret=n;cnt.push_back(0);//补一个0 
		for(int i=n,j=n;i>=1;--i){//LCA 
			if(cnt[i]<2)j=i;//没办法分叉 
			ret=max(ret,n+j-2*i);
		}
		for(int i=1;i<=n;++i)if(cnt[i-1]>=2)ret=max(ret,n+i);//LCA是根 
		else break;
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
