#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class PenguinSledding{
	private:
		static const int maxn=55;
		int d[maxn];
		long long pw[55];
		bool mp[maxn][maxn];
		
	public: 
		long long countDesigns(int n, vector<int> checkpoint1, vector<int> checkpoint2){
			int m=checkpoint1.size();
			long long ans=m+1;
			memset(mp,0,sizeof(mp));
			pw[0]=1;
			for (int i=1;i<=m;++i) pw[i]=pw[i-1]<<1;
			for (int i=1;i<=n;++i) d[i]=0;
			for (int i=0;i<m;++i){
				if (mp[checkpoint1[i]][checkpoint2[i]]){
					continue;
				}
				mp[checkpoint1[i]][checkpoint2[i]]=true;
				mp[checkpoint2[i]][checkpoint1[i]]=true;
				
				++d[checkpoint1[i]];
				++d[checkpoint2[i]];
			}
			for (int i=1;i<=n;++i) if (d[i]>1)
				ans+=pw[d[i]]-d[i]-1;
			for (int i=1;i<=n;++i)
			for (int j=i+1;j<=n;++j)
			for (int k=j+1;k<=n;++k) if (mp[i][j]&&mp[i][k]&&mp[j][k]) ++ans;
			return ans;
		}
};
