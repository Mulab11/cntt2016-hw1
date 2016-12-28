#include<bits/stdc++.h>
using namespace std;
string S;
int i,j,k,l,x,t[55][128],p[128],n;
class FoxAndHandle
{
	public:
		string lexSmallestName(string s)
		{
			for(n=s.size();i<n;i++)for(j='a';j<='z';j++)t[i+1][j]=t[i][j]+(s[i]==j);
			for(i=l=0;i<n/2;i++)for(j='a';j<='z';j++)if(p[j]<t[n][j]/2)
			{
				for(k=l;s[k]!=j;k++);
				for(x='a';x<='z';x++)if(t[k][x]-p[x]>t[n][x]/2)goto E;
				p[j]++;S+=j;l=k+1;break;E:; 
			}
			return S;
		}
};
