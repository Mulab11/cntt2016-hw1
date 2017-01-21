// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheSwapsDivOne.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class TheSwapsDivOne{
	int a[2333],n;
	public:
	double find(vector <string> sequence, int k){
		n=0;
		for (int i=0;i<sequence.size();++i)
			for (int j=0;j<sequence[i].size();++j)
				a[++n]=sequence[i][j]-48;
		int sum=(n-1)*n/2;
		double p=1;
		for (int i=0;i<k;++i)
			p=p*(sum-n+1)/sum+(1.0-p)/sum;
		double ret=0;
		sum=n*(n+1)/2;
//		printf("p:%.3f\n",p);
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j){
				double k=1.0*j*(n-j+1)/sum;
				if (i==j) ret+=p*k*a[i];
				else ret+=(1.0-p)/(n-1)*k*a[i];
			}
		return ret;
	}
};
