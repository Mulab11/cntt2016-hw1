#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<set>
using namespace std;
typedef long long LL;
class CuttingBitString
{
	public:
	
	set<LL> p5;
	int f[55];
	int getmin(string S)
	{
		int n=S.size();
		for(LL x=1;x<1LL<<50;x*=5LL)//find all powers of 5.
			p5.insert(x);
		//f[i]: the minimum pieces for first i digits.
		memset(f,31,sizeof(f));
		f[0]=0;
		for(int i=0;i<n;i++)
		{
			LL t=0;
			if(S[i]!='0')
				for(int j=i;j<n;j++)//pick the next piece.
				{
					t=t*2+S[j]-'0';
					if(p5.count(t))
						f[j+1]=min(f[j+1],f[i]+1);
				}
		}
		return f[n]<=n?f[n]:-1;
	}
};

