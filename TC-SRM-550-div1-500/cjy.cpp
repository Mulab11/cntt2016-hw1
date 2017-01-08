#include<bits/stdc++.h>
#define LL long long
using namespace std;
vector<string> S;string s;LL f,i,j,z;
class CheckerExpansion
{
	public:
		char G(LL x,LL y)
		{
			if(z=x-y>>1,x<y||(x-y)%2||y+z>=f||(y+z&z)!=z)return'.';
			return y+z&1?'B':'A';
		}
		vector<string> resultAfter(LL _,LL x,LL y,LL w,LL h)
		{
			for(f=_;i<h;S.push_back(s),i++)for(s="",j=0;j<w;j++)s+=G(x+j,y+h-i-1);
			return S;
		}
};
