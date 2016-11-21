#include<queue>
#include<vector>
#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class XorTravelingSalesman{
	private:
		typedef pair<int,int> pi;
		static const int maxn=55,maxm=1024;
		int head[maxn],list[maxn*maxn],nxt[maxn*maxn],tot;
		int n,val[maxn];
		bool vis[maxn][maxm];
		queue<pi> q;
		
		void add(int a,int b){
			tot++;
			nxt[tot]=head[a];
			head[a]=tot;
			list[tot]=b;
			return;
		}
	public:
		int maxProfit(vector <int> cityValues, vector <string> roads){
			n=cityValues.size();
			for (int i=0;i<n;++i) val[i]=cityValues[i];
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (roads[i][j]=='Y') add(i,j);
			vis[0][val[0]]=true;
			q.push(pi(0,val[0]));
			int ans=0;
			while(!q.empty()){
				pi t=q.front();
				ans=max(ans,t.second);
				q.pop();
				for (int i=head[t.first];i;i=nxt[i]){
					if (!vis[list[i]][t.second^val[list[i]]]){
						vis[list[i]][t.second^val[list[i]]]=true;
						q.push(pi(list[i],t.second^val[list[i]]));
					}
				}
			}
			return ans;
		}
};
