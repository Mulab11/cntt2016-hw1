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

const int p=1e9+7;
const int N=2000000+19;

char s[N];
int f[N],h[N],prew[N],preo[N],sufw[N],sufo[N];
int x,y;

class WolfDelaymasterHard{
public:
	int countWords(int n,int wlen,int w0,int wmul,int wadd,int olen,int o0,int omul,int oadd){
		For(i,1,n+1) s[i]='?';
		x=w0;
		For(i,0,wlen){
			s[x+1]='w';
			x=(1ll*x*wmul+wadd)%n;
		}
		x=o0;
		For(i,0,olen){
			s[x+1]='o';
			x=(1ll*x*omul+oadd)%n;
		}
		prew[0]=preo[0]=-1;
		for (int i=1;i<=n;i++){
			prew[i]=(s[i]=='w'?i:prew[i-1]);
			preo[i]=(s[i]=='o'?i:preo[i-1]);
		}
		sufw[n+1]=sufo[n+1]=n+1;
		for (int i=n;i>=0;i--){
			sufw[i]=(s[i]=='w'?i:sufw[i+1]);
			sufo[i]=(s[i]=='o'?i:sufo[i+1]);	//预处理每一位前面后面的第一个1或者0
		}
		f[0]=1;
		x=1;
		y=min(sufo[0]-1,(sufw[0]-1)/2);
		if (x<=y){
			h[2]=(h[2]+1)%p;
			h[2*y+1]=(h[2*y+1]-1+p)%p;
		}
		For(i,1,n+1){	//DP计算方案，分情况进行主动转移和被动转移，用前缀和优化
			h[i]=(h[i]+h[i-1])%p;
			if (i%2==0){
				f[i]=h[i];
				x=max((i-prew[i])/2+1,i-sufo[prew[i]]+1);
				y=min((i-preo[prew[i]])/2,i-prew[i]);
				if (x<=y){
					f[i]=(f[i]+f[i-2*x])%p;
					if (i-2*y-1>=0) f[i]=(f[i]-f[i-2*y-1]+p)%p;
				}
				x=1;
				y=min(sufo[i+1]-i-1,(sufw[i+1]-i-1)/2);
				if (x<=y){
					h[i+2]=(h[i+2]+f[i])%p;
					h[i+2*y+1]=(h[i+2*y+1]-f[i]+p)%p;
				}
			}
			f[i]=(f[i-1]+f[i])%p;
		}
		return (f[n]-f[n-1]+p)%p;
	}
} T;