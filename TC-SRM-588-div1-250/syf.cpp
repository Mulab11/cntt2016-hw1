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

struct node{
	int d,t;
	bool operator < (const node &B) const {return t<B.t;}
} A[N];
int f[N][N];
int n,res;

void Upd(int &x,int y){
	x=min(x,y);
}

class GUMIAndSongsDiv1{
public:
	int maxSongs(Vi V1,Vi V2,int T){
		n=V1.size();
		For(i,1,n+1) A[i]=(node){V1[i-1],V2[i-1]};
		sort(A+1,A+n+1);
		memset(f,60,sizeof(f));
		For(i,0,n+1) f[i][0]=0;	//DP
		For(i,1,n+1)
			For(j,1,i+1){	//枚举这个点的状态
				Upd(f[i][j],f[i-1][j]+(A[i].t-A[i-1].t));
				Upd(f[i][j],f[i-1][j-1]+A[i].d+(j==1?0:A[i].t-A[i-1].t));
				if (f[i][j]<=T) res=max(res,j);
			}
		return res;
	}
} T;