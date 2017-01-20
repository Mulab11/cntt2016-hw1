#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TriangleXor{
	public:
	int theArea(int W){
		long double ans=1*W/2.0*(W+1);
		for (int i=1;i<=W;++i){
			if (i&1) ans-=(long double)1.0/(W+i)*W*(W+1-i)*W;
			else ans+=(long double)1.0/(W+i)*W*(W+1-i)*W;
		}
		return ans;
	}
};