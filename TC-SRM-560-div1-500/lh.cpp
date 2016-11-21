#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class DrawingPointsDivOne{
	static const int maxn=500;
	bool ex[maxn][maxn];
	int mx[maxn][maxn],sum[maxn][maxn],n;
	
	int _sum(int a,int b){
		if (a<0||b<0) return 0;
		return sum[a][b];
	}
	
	bool check(int d,vector<int>&x,vector<int>&y){
		++d;
		memset(sum,0,sizeof(sum));
		memset(mx,0,sizeof(mx));
		for (int i=0;i<n;++i){
			++sum[x[i]][y[i]];
			--sum[x[i]][y[i]+d];
			--sum[x[i]+d][y[i]];
			++sum[x[i]+d][y[i]+d];
		}
		for (int i=0;i<maxn;++i)
		for (int j=0;j<maxn;++j) sum[i][j]+=_sum(i-1,j)+_sum(i,j-1)-_sum(i-1,j-1);
		
		int cnt=0;
		for (int i=0;i<maxn;++i)
		for (int j=0;j<maxn;++j){
			if (sum[i][j]==0) mx[i][j]=0;
			else{
				if (_sum(i-1,j)==0) mx[i][j]=1;
				else if (_sum(i,j-1)==0) mx[i][j]=1;
				else if (_sum(i-1,j-1)==0) mx[i][j]=1;
				else{
					int m=min(mx[i][j-1],mx[i-1][j]);
					if (_sum(i-m,j-m)==0) mx[i][j]=m;
					else mx[i][j]=m+1;
				}
			}
			if (mx[i][j]>=d) ++cnt;
		}
		return cnt==n;
	}
	
	public:
	int maxSteps(vector<int> x, vector<int> y){
		n=x.size();
		for (int i=0;i<n;++i) x[i]+=70,y[i]+=70;
		int l=0,r=300,mid;
		while(l<r){
			mid=(l+r+1)/2;
			if (check(mid,x,y)) l=mid;
			else r=mid-1;
		}
		if (l==300) return -1;
		return l;
	}
};
