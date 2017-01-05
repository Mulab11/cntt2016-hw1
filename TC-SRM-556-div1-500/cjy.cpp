#include<bits/stdc++.h>
#define B(x,y) (x<y?0:x>y?2:1)
#define U(x,y) x.empty()||x>y?x=y:x
using namespace std;
string f[50][50][3];
int n,i,j,k,l,e;
class LeftRightDigitsGame2
{
	public:
		string minNumber(string a,string b)
		{
			for(n=a.size();i<n;i++)f[i][i][B(a[0],b[i])]=a[0];
			for(;l<n-1;l++)for(i=0;i+l<n;i++)for(j=i+l,k=2;~k;k--)if(f[i][j][k].size())
			{
				if(i)e=B(a[l+1],b[i-1]),U(f[i-1][j][e==1?k:e],a[l+1]+f[i][j][k]);
				if(j<n-1)U(f[i][j+1][k==1?B(a[l+1],b[j+1]):k],f[i][j][k]+a[l+1]);
			}
			if(f[0][n-1][2].size())U(f[0][n-1][1],f[0][n-1][2]);return f[0][n-1][1];
		}
};
