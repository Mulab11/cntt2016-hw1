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

const int oo=(1<<30)-1;
int res,n;

int lcp(string A,string B){	//暴力求解LCP
	int i=0;
	for (;i<A.length()&&i<B.length();i++) if (A[i]!=B[i]) break;
	return i;
}

class UndoHistory{
public:
	int minPresses(Vs V){
		n=V.size();
		res=n+V[0].length();
		For(i,1,n){	//枚举
			int mn=oo,mx=0;
			if (lcp(V[i-1],V[i])==V[i-1].length()){
				mn=min(mn,int(V[i].length())-int(V[i-1].length()));
			}
			For(j,0,i) mx=max(mx,lcp(V[i],V[j]));
			mn=min(mn,int(V[i].length())-mx+2);
			res+=mn;
		}
		return res;
	}
} T;