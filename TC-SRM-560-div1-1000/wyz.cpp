// BEGIN CUT HERE

// END CUT HERE
#line 5 "BoundedOptimization.cpp"
#include <bits/stdc++.h>
#define ll long long
#define eps (1e-8)

using namespace std;

const int maxn=15;

class BoundedOptimization{
	int l[maxn],r[maxn],n;
	int b[maxn][maxn];
	double val[maxn];
	bool established[maxn];
	double ans;
	void dfs(int u,double sum){
		if (u==n){
			if (sum<-eps) return;
			int cnt=0;
			for (int i=0;i<n;++i)if (!established[i]){
				++cnt;
				double now=0;
				for (int j=0;j<n;++j)if (established[j]&&b[i][j])
					now+=val[j];
				val[i]=now;
				sum-=now;
			}
			if (cnt>0) sum/=cnt;
			for (int i=0;i<n;++i)if (!established[i]){
				val[i]+=sum;
				if (val[i]-eps>r[i]||val[i]+eps<l[i]) return;
			}
			
			double res=0;
			for (int i=0;i<n;++i)for (int j=i+1;j<n;++j)
				if (b[i][j]) res+=val[i]*val[j];
			ans=max(ans,res);
			return;
		}
		established[u]=1;
		dfs(u+1,sum-(val[u]=l[u]));
		dfs(u+1,sum-(val[u]=r[u]));
		established[u]=0;
		dfs(u+1,sum);
	}
	public:
	double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum){
		string st="";
		for (int i=0;i<expr.size();++i) st+=expr[i];
		memset(b,0,sizeof(b));
		for (int i=0;i<st.size();i+=3){
			int u=st[i]-'a',v=st[i+1]-'a';
			b[u][v]=b[v][u]=1;
		}
		n=lowerBound.size();
		for (int i=0;i<n;++i) l[i]=lowerBound[i],r[i]=upperBound[i];
		ans=0;
		dfs(0,maxSum);
		return ans;
	}
};
