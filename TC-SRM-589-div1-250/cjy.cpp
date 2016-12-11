#include<bits/stdc++.h>
using namespace std;
int s,f[29],i,c[29],g[29];
int F(int x){return F[x]==x?x:f[x]=F(f[x]);}
class GooseTattarrattatDiv1
{
	public:
		int getmin(string S)
		{
			for(i=0;i<26;i++)f[i]=i;
			for(i=0;i<S.size();i++)c[S[i]-'a']++,f[F(S[i]-'a')]=F(S[S.size()-i-1]-'a');
			for(i=0;i<26;i++)g[F(i)]=max(g[F(i)],c[i]);//每个集合最大的值需要被减去			
			for(i=0;i<26;i++)if(F(i)==i)s-=g[i];
			return s+S.size();
		}
};
