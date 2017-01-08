#include<bits/stdc++.h>
#define LL long long 
using namespace std;
class FoxPaintingBalls
{
	public:
		LL theMax(LL R,LL G,LL B,LL n)
		{
			if(n<2)return R+G+B;
			LL d=n*(n+1)/6,s=min(min(R/d,G/d),B/d);
			if(n%3==1)s=min(s,(R+G+B)/(3*d+1));
			return s;
		}
};
