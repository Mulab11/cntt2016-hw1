// BEGIN CUT HERE

// END CUT HERE
#line 5 "FindPolygons.cpp"
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int maxl=11003;
class FindPolygons{	
	int a[maxl],b[maxl],c[maxl],m;
	public:
	double minimumPolygon(int L){
		if ((L&1)||L==2) return -1;
		m=0;
		int k,ret=L;
		for (int i=0;i<=L/2;++i)
			for (int j=i?0:1;(k=sqrt(i*i+j*j))<=L/2;++j)
				if (i*i+j*j==k*k){
					c[++m]=k;a[m]=i;b[m]=j;
				}
		for (int i=1;i<=m;++i)
			for (int j=i+1;j<=m;++j)if (a[i]*b[j]!=a[j]*b[i]){
				int x=abs(a[i]-a[j]),y=abs(b[i]-b[j]),z=sqrt(x*x+y*y);
				if (x*x+y*y!=z*z||c[i]+c[j]+z!=L) continue;
				ret=min(max(max(c[i],c[j]),z)-min(min(c[i],c[j]),z),ret);
			}
		return ret<L?ret:(L/2%2);
	}
};

//this is for test
/*
int main(){
	FindPolygons test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
