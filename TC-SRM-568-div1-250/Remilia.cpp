#include<bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>

using namespace std;

const int maxn=55;
int f[maxn][8];
void upd(int &x,int y){
	if (x==-1||y<x) x=y;
}
/*
决定每个盒子放什么颜色。
有解就是每种颜色都有盒子，xjbDP就O(n)了。
*/

struct BallsSeparating{
	int minOperations(vector<int>R,vector<int>G,vector<int>B){
		int n=R.size();
		memset(f,-1,sizeof f);
		f[0][0]=0;
		rep(i,0,n-1){
			int sum=R[i]+G[i]+B[i];
			rep(j,0,7){
				if (f[i][j]==-1) continue;
				upd(f[i+1][j|1],f[i][j]+sum-R[i]);
				upd(f[i+1][j|2],f[i][j]+sum-G[i]);
				upd(f[i+1][j|4],f[i][j]+sum-B[i]);
			}
		}
		return f[n][7];
	}
};
