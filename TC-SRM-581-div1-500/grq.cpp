#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=305;

vi make(vector<string> a){
	string s="";
	int now=0;
	vi res;res.clear();
	for(int i=0;i<a.size();i++) s+=a[i];
	for(int i=0;i<s.length();i++)
		if(s[i]>='0'&&s[i]<='9') now=now*10+s[i]-'0'; else res.pb(now),now=0;
	res.pb(now);
	return res;
}
int n,a[10],b[10],dis[N][N];
void uni(int res[],vector<string> tree){
	vi a=make(tree);
	memset(res,0,sizeof(res));
	n=a.size();
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			if(i==j) dis[i][j]=0; else dis[i][j]=N;
	for(int i=0;i<n;i++)
		dis[a[i]][i+1]=dis[i+1][a[i]]=1;
	for(int k=0;k<=n;k++)
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
	for(int i=0;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(dis[i][j]<=7) res[dis[i][j]]++;
}

class TreeUnion{
public:
	double expectedCycles(vector<string> tree1, vector<string> tree2, int K){
		uni(a,tree1);uni(b,tree2);
		debug(n);
		double ans=0.0;
		for(int i=1;i<=K-3;i++) printf("%d %d\n",a[i],b[K-2-i]);
		for(int i=1;i<=K-3;i++)
			ans+=(double)a[i]*b[K-2-i]*2/n/(n+1);
		return ans;
	}
};
