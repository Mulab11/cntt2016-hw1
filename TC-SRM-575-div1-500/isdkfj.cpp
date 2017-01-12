#include <bits/stdc++.h>

using namespace std;


class TheSwapsDivOne {
public:
	double find(vector <string> sequence, int k) {
		int n=0,x=0;
		for(int i=0;i<sequence.size();++i)n+=sequence[i].size();
		double p=1,t,r;
		for(int i=1;i<=k;++i)p=p*(n-2)/n+(1-p)*2/n/(n-1);//递推算在原来位置和其他位置的概率 
		t=(1-p)/(n-1);r=0;
		for(int i=0;i<sequence.size();++i)
			for(int j=0;j<sequence[i].size();++j){
				int u=sequence[i][j]-'0';
				for(int k=0;k<n;++k)
				if(k!=x)
					r+=u*t*(k+1)*(n-k);//其他位置 
				r+=u*p*(x+1)*(n-x);//当前位置 
				++x;
			}
		return 2*r/n/(n+1);
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
