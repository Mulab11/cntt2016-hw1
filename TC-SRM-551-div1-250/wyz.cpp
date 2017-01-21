// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulChocolates.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class ColorfulChocolates{
	int n;
	int a[maxn],m;
	public:
	int maximumSpread(string chocolates, int maxSwaps){
		n=chocolates.size();
		int ret=0;
		for (int i=0;i<n;++i)for (int j=i;j<n;++j)if (chocolates[i]==chocolates[j]){
			m=0;
			for (int k=i;k<=j;++k)if (chocolates[k]==chocolates[i])
				a[m++]=k;
			for (int pos=i;pos+m-1<=j;++pos){
				int cost=0;
				for (int k=0;k<m;++k) cost+=abs(pos+k-a[k]);
				if (cost<=maxSwaps) ret=max(ret,m);
			}
		}
		return ret;
	}
};
