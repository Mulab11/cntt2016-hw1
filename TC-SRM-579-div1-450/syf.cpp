//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>

#define For(i,x,y) for (int i=x;i<y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;
typedef vector<string> Vs;

const int N=50+3;
const int oo=(1<<30)-1;

int f[1<<16][16];
int s[N],t[N],d[N],A[N][N];
int n,x,y,z,m,res;

void Upd(int &x,int y){
	x=min(x,y);
}

class TravellingPurchasingMan{
public:
	int maxStores(int n,Vs V1,Vs V2){
		For(i,0,N) For(j,0,N) A[i][j]=oo;
		::n=n;m=V1.size();
		For(i,0,m){
			stringstream ss;
			ss<<V1[i];
			ss>>s[i]>>t[i]>>d[i];
		}
		For(i,0,V2.size()){
			stringstream ss;
			ss<<V2[i];
			ss>>x>>y>>z;
			A[x][y]=A[y][x]=min(A[x][y],z);	//构图
		}
		For(i,0,n) A[i][i]=0;
		For(k,0,n) For(i,0,n) For(j,0,n){
			A[i][j]=min(A[i][j],A[i][k]+A[k][j]);	//用floyd求解两两点对的最短路
		}
		For(i,0,1<<16) For(j,0,16) f[i][j]=oo;	//状压DP
		For(i,0,m)
			if (A[n-1][i]<=t[i]){
				f[1<<i][i]=max(A[n-1][i],s[i])+d[i];
			}
		For(w,1,1<<m) For(i,0,m)
			if (f[w][i]!=oo){
				For(j,0,m)
					if (!(w>>j&1)&&f[w][i]+A[i][j]<=t[j]){
						Upd(f[w|1<<j][j],max(f[w][i]+A[i][j],s[j])+d[j]);
					}
				res=max(res,__builtin_popcount(w));
			}
		return res;
	}
} T;