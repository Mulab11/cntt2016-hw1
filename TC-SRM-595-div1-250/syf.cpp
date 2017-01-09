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

const int N=1000+19;

int col[N],vis[N],res;

class LittleElephantAndIntervalsDiv1{
public:
	ll getNumber(int n,Vi L,Vi R){
		memset(col,-1,sizeof(col));
		For(i,0,L.size()){
			For(j,L[i],R[i]+1) col[j]=i;
		}
		For(i,1,n+1) if (~col[i]) vis[col[i]]=1;
		For(i,0,L.size()) if (vis[i]) res++;
		return 1ll<<res;	//答案就是可能成为答案的颜色种数的2的幂次
	}
} T;