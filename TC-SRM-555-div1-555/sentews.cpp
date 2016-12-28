#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
int codeforces=555555555;
int c[3333][3333]={};
class XorBoard
{
	public:
	int count(int H, int W, int Rcount, int Ccount, int S)
	{
		int ans=0;
		c[0][0]=1;
		c[1][0]=c[1][1]=1;
		for(int i=2;i<3333;i++)
			for(int j=0;j<=i;j++)
				c[i][j]=(c[i-1][j]+c[i-1][j-1])%codeforces;
		for(int i=Rcount&1;i<=Rcount;i=i+2)
			for(int j=Ccount&1;j<=Ccount;j=j+2)
				if(S==i*W+j*H-i*j*2)
					ans=(ans+1LL*c[W][j]*c[H][i]%codeforces*c[(Rcount-i>>1)+H-1][H-1]%codeforces*c[(Ccount-j>>1)+W-1][W-1]%codeforces)%codeforces;
		return ans;
	}
};
