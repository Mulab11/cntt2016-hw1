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

const int N=50+19;

Vi R;
int dis[N],Q[N],S,T,n;

int bfs(){	//×î¶ÌÂ·
	memset(dis,-1,sizeof(dis));dis[S]=0;
	int f=1,w=0;Q[1]=S;
	while (f>w){
		int x=Q[++w];
		For(i,0,n){
			if (fabs(i-x)<=R[x]||n-fabs(i-x)<=R[x])
				if (dis[i]==-1){
					dis[i]=dis[x]+1;
					Q[++f]=i;
				}
		}
	}
	return dis[T];
}

class TravelOnMars{
public:
	int minTimes(Vi R,int S,int T){
		n=R.size();
		::R=R;::S=S;::T=T;
		return bfs();
	}
} Te;