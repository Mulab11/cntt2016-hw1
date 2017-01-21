// BEGIN CUT HERE

// END CUT HERE
#line 5 "TravellingPurchasingMan.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;

void Get(string &st,int &a,int &b,int &c){
	int k=0;
	for (a=0;st[k]!=' ';(a*=10)+=st[k++]-48);
	for (b=0,++k;st[k]!=' ';(b*=10)+=st[k++]-48);
	for (c=0,++k;k<st.size();(c*=10)+=st[k++]-48);
//	cout<<st<<endl;
//	printf("%d %d %d\n",a,b,c);
}
int lowbit(int x){return x&-x;}
int Count_1(int x){
	int ret=0;
	for (;x;x-=lowbit(x)) ++ret;
	return ret;
}
void Min(int &x,int y){if (y<x) x=y;}

const int inf=604800*2+1;

class TravellingPurchasingMan{
	int bin[maxn],n;
	int op[maxn],ed[maxn],dr[maxn];
	int dist[maxn][maxn];
	void Floyd(int n){
		for (int k=0;k<n;++k)for (int i=0;i<n;++i)for (int j=0;j<n;++j)
			Min(dist[i][j],dist[i][k]+dist[k][j]);
//		for (int i=0;i<n;++i,puts(""))for (int j=0;j<n;++j)printf("%d ",dist[i][j]);
	}
	int dp[100000][maxn];
	void doit(int _s){
		memset(dp,63,sizeof(dp));
		for (int j=0;j<n;++j)if (dist[_s][j]<=ed[j])
			dp[bin[j]][j]=max(dist[_s][j],op[j])+dr[j];
		for (int i=1;i<bin[n];++i)for (int l=0;l<n;++l)if (dp[i][l]<inf)
			for (int j=0;j<n;++j)if (dp[i][l]+dist[l][j]<=ed[j])
				Min(dp[i^bin[j]][j],max(dp[i][l]+dist[l][j],op[j])+dr[j]);
	}
	public:
	int maxStores(int N, vector <string> interestingStores, vector <string> roads){
		for (int i=0;i<18;++i) bin[i]=1<<i;
		n=interestingStores.size();
		for (int i=0;i<n;++i)
			Get(interestingStores[i],op[i],ed[i],dr[i]);
		memset(dist,63,sizeof(dist));
		for (int i=0;i<n;++i) dist[i][i]=0;
		for (int i=0;i<roads.size();++i){
			int u,v,w;
			Get(roads[i],u,v,w);
			dist[u][v]=dist[v][u]=min(dist[u][v],w);
		}
		Floyd(N);
		doit(N-1);
		int ret=0;
		for (int i=1;i<bin[n];++i){
			int now=Count_1(i);
			if (now<=ret) continue;
			for (int j=0;j<n;++j)if (dp[i][j]<inf){ret=now;break;}
		}
		return ret;
	}
};
