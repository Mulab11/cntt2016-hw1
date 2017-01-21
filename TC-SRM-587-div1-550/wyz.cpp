// BEGIN CUT HERE

// END CUT HERE
#line 5 "TriangleXor.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

class TriangleXor {
	double w;
	public:
	int theArea(int W){
		w=W;
		double lastx=0,lasty=0,x,y,ret=0;
		for (int i=1;i<=W;++i,lastx=x,lasty=y){
			x=w*i/(w+i);
			y=x/w;
			if (i&1) ret+=x-lastx+(w-2.0*x)*(y-lasty)/2.0;
			else ret+=(w-2.0*lastx)*(y-lasty)/2.0;
		}
		if ((W&1)==0) ret+=w/4.0;
		return ret;
	}
};
