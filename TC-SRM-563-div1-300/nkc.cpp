#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct FoxAndHandle
{
	int tot[51][27],a[27],nxt[51],s[51],pre[27];
	string lexSmallestName(string S)
	{
		int i,j,k,n=S.size(),x;
		string ans="";
		for(i=1;i<=26;i++)
		pre[i]=n+1;
		for(j=n-1;j>=0;j--)
		{
			s[j]=S[j]-96;
			for(i=1;i<=26;i++)
			tot[j][i]=tot[j+1][i];
			tot[j][s[j]]++;
			nxt[j]=pre[s[j]];
			pre[s[j]]=j;
		}//预处理下一个相同字母以及这个位置后面所有字母的个数 
		for(i=1;i<=26;i++)
		a[i]=tot[0][i]/2;
		for(i=1;i<=n/2;i++)//贪心地选择字典序最小的合法字母 
		{
			for(j=1;j<=26;j++)
			if(a[j])
			{
				x=pre[j];
				for(k=1;k<=26;k++)
				if(tot[x][k]<a[k]) break;
				if(k==27)
				{
					ans+=char(j+96);
					a[s[x]]--;
					break;
				}
			}
			x++;
			for(j=1;j<=26;j++)
			while(pre[j]<x)
			pre[j]=nxt[pre[j]];
		}
		return ans;
	}
};