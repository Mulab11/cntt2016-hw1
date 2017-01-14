#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;

class CheckerExpansion
{
	public:
	vector<string> resultAfter(LL t,LL x0,LL y0,int w,int h)
	{
		vector<string> s(h,string(w,'.'));
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++)
			{
				//We can prove the following conclusion
				LL x=x0+j,y=y0+h-i-1;
				if(x+y&1||x<y)continue;//Empty
				LL r=x+y>>1,c=x-y>>1;
				if(r>=t||~r&c)continue;//C(r,c) mod 2 = 1
				s[i][j]="AB"[r&1];
			}
		return s;
	}
};

