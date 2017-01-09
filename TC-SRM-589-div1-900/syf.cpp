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
#include<numeric>
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

const int N=300+19;
const int oo=(1<<30)-1;

string s;
int A[N],fa[N],rev[N],c[N][2],f[N][2];
int n,res=oo;

int getf(int x){	//并查集
	return fa[x]==x?x:fa[x]=getf(fa[x]);
}
void Union(int x,int y){
	x=getf(x),y=getf(y);
	if (x!=y) fa[x]=y;
}

class FlippingBitsDiv1{	//分情况分别进行DP
public:
	int getmin(Vs V,int m){
		s=accumulate(V.begin(),V.end(),string());
		n=s.length();
		if (m*m>n){	//M较大时，暴力枚举，用并查集判断
			For(t,0,1<<(n-1)/m+1){
				int tmp=0;
				memset(c,0,sizeof(c));
				For(i,0,n){
					A[i]=s[i]-'0';
					fa[i]=i;
				}
				for (int i=(n-1)/m;~i;i--){
					rev[i]=rev[i+1]^(t>>i&1);
				}
				For(i,0,n) if (rev[i/m]) A[i]^=1;
				For(i,0,n-m) Union(i,i+m);
				For(i,0,n) c[getf(i)][A[i]]++;
				For(i,0,n) if (fa[i]==i) tmp+=min(c[i][0],c[i][1]);
				res=min(res,tmp+__builtin_popcount(t));
			}
		} else{	//M较小时，状压DP
			For(i,0,n) A[i]=s[i]-'0';
			For(t,0,1<<m){
				memset(c,0,sizeof(c));
				memset(f,60,sizeof(f));
				For(i,0,n) c[i/m][A[i]!=(t>>i%m&1)]++;
				f[(n-1)/m+1][0]=0;
				for (int i=(n-1)/m;~i;i--)
					For(j,0,2) For(k,0,2){
						f[i][j^k]=min(f[i][j^k],f[i+1][j]+k+c[i][j^k^1]);
					}
				res=min(res,min(f[0][0],f[0][1]));
			}
		}
		return res;
	}
} T;

