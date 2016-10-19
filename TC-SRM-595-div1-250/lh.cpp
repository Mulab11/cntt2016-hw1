#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>

class LittleElephantAndIntervalsDiv1{
	private:
		static const int maxn=1050,maxm=55;
		bool vis[maxn];
	public:
		long long getNumber(int n,std::vector<int>L,std::vector<int>R){
			memset(vis,0,sizeof(vis));
			int m=L.size();
			//计算哪些操作会对结果造成影响 
			for (int i=1;i<=n;i++){
				for (int j=m-1;j>=0;--j) if (i>=L[j]&&i<=R[j]){
					vis[j]=true;
					break;
				}
			}
			long long ans=1;
			//统计答案 
			for (int i=0;i<m;i++) if (vis[i]) ans<<=1;
			return ans;
		}
};
