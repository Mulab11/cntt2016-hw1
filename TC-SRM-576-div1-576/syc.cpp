#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <vector>
#include <string>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#define For(i,x,y)  for(int i=(int)(x);i<=(int)(y);i++)
#define Forn(i,x,y) for(int i=(int)(x);i>=(int)(y);i--)
#define Rep(i,x,y)  for(int i=(int)(x);i< (int)(y);i++)
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef long double db;
typedef long long ll;
typedef pair<int,int> PII;
const int N=305;
const int inf=1e9;
const ll Inf=1e10;
const int P=1e9+9;

inline int IN(){
	char ch=getchar(); int x=0,f=0;
	for(;ch<48||ch>57;ch=getchar()) f=(ch=='-');
	for(;ch>=48&&ch<=57;ch=getchar()) x=x*10+ch-48;
	return x;
}

inline int Pow(int x,int y,int p){
	int a=1;
	for(;y;y>>=1,x=(ll)x*x%p) if(y&1) a=(ll)a*x%p;
	return a;
}

int n,wat[N],m,l,va,vb;
int f[N][N][2],s[N],g[N][N];

int valid(int l,int r){
	if(l<0||r<0||l>n||r>n) return 0;
	if(s[r]-s[l-1]>vb) return 0;
	if(s[r]-s[l-1]<va) return 0;
	return 1;
}

void A(int &x,int y){
	x+=y;
	if(x>=P)x-=P;
}

#define REP(i, l, r) for(int i = l; i <= r; i ++)
string water;
struct TheExperiment{
	int countPlacements(vector<string> water_read, int M, int L, int val_A, int B){
		for(auto v : water_read) water += v;
		n = water.size();
		m = M;
		l = L;
		va = val_A;
		vb = B;
		REP(i, 1, n){
			wat[i] = water[i - 1] - '0';
			s[i] = s[i - 1] + wat[i];
		}
		For(i,0,n) f[i][0][1]=1;
		For(i,0,n)
		For(j,0,m)
		For(x,0,1){
			if(!f[i][j][x])continue;
		// 	dprintf("%d %d %d\n",i,j,x);
			For(len,1,l){
				if(!valid(i+1,i+len))continue;
				int nx=x;
				if(x==1&&len==l) nx=0;
				A(f[i+len][j+1][nx],f[i][j][x]);
			}
			if(!x){
				For(k,i+1,n) A(f[k][j][1],f[i][j][x]);
			}
		}
		int ans=0;
		For(i,1,n) A(ans,f[i][m][0]); 
		return ans;
	}
};