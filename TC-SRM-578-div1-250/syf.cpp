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
const int p=1e9+7;

int id[N][N],fa[N*N],sz[N*N],f[2];
int n,m,num;

int getf(int x){
	return fa[x]==x?x:fa[x]=getf(fa[x]);
}
void Union(int x,int y){	//并查集
	x=getf(x),y=getf(y);
	if (x!=y) fa[x]=y;
}

class GooseInZooDivOne{
public:
	int count(Vs s,int d){
		n=s.size();
		m=s[0].length();
		For(i,1,n+1)
			For(j,1,m+1){
				if (s[i-1][j-1]=='v') id[i][j]=++num;
			}
		For(i,1,num+1) fa[i]=i;
		For(i,1,n+1) For(j,1,m+1)
			if (s[i-1][j-1]=='v'){
				For(x,1,n+1) For(y,1,m+1){
					if (s[x-1][y-1]=='v'&&abs(x-i)+abs(y-j)<=d) Union(id[i][j],id[x][y]);
				}
			}	//将可以互相到达的点并查集合并起来
			
			
		For(i,1,num+1) sz[getf(i)]++;
		f[0]=1;
		For(i,1,num+1)
			if (fa[i]==i){	//对个数为奇数和偶数的分别计数
				if (sz[i]&1){
					f[0]=f[1]=(f[0]+f[1])%p;
				} else{
					f[0]=2*f[0]%p;
					f[1]=2*f[1]%p;
				}
			}
		return (f[0]-1+p)%p;
	}
} T;