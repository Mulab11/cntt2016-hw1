#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int M=1000000009;

class ColorfulBuilding
{
	public:
	int n,m;
	int f[1300][1300],g[1300],s[1300];
	int count(vector<string> color1,vector<string> color2,int L)
	{
		string C1,C2;
		for(int i=0;i<color1.size();i++)C1+=color1[i];
		for(int i=0;i<color2.size();i++)C2+=color2[i];
		n=C1.size();
		vector<int> color,col_v;
		for(int i=0;i<n;i++)color.push_back(C1[i]*256+C2[i]);
		//Make color[i] in [0,n-1]
		col_v=color;
		sort(col_v.begin(),col_v.end());
		col_v.erase(unique(col_v.begin(),col_v.end()),col_v.end());
		m=col_v.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(color[i]==col_v[j])
				{
					color[i]=j;
					break;
				}
		//We do dynamic planning from back to front, so we can reverse the color.
		reverse(color.begin(),color.end());
		//f[i][j]:the number of ways that i color blocks can be seen, and the last building's color is j.
		//For i-th building (base 0), let c=color[i]. Here are the transforms:
		//1. f[j][c] -- i+1 -> f[j][c]
		//2. f[j][k] --  1  -> f[j+1][c] k!=c
		//3. f[j][k] --  i  -> f[j][k]
		//Let s[j]=\sum_k f[j][k], and we can use s to accelerate transform 1.
		//We use g[k] that means f[j][k] should multiply g[k]. g[k] is downdated when needed.
		f[1][color[0]]=1;
		s[1]=1;
		//Let s[i]=\sum_j f[i][j]
		for(int i=0;i<m;i++)
			g[i]=1;
		for(int i=1;i<n;i++)
		{
			int c=color[i];
			for(int j=1;j<=n;j++)//Downdate g[c]
				f[j][c]=(LL)f[j][c]*g[c]%M;
			g[c]=1;
			for(int j=n;j>0;j--)
			{
				s[j]=((LL)s[j]*i+s[j-1]-f[j-1][c]+f[j][c])%M;//Maintain s[j]
				f[j][c]=((LL)f[j][c]*(i+1)+s[j-1]-f[j-1][c])%M;//Use s to do transform 1&2
			}
			//Transform 3: modifying g is enough
			for(int k=0;k<m;k++)
				if(k!=c)
					g[k]=(LL)g[k]*i%M;
		}
		int ans=0;
		//Don't forget to downdate g[k] when counting the answer.
		for(int k=0;k<m;k++)
			ans=(ans+(LL)f[L][k]*g[k])%M;
		ans=(ans+M)%M;
		return ans;
	}
};

