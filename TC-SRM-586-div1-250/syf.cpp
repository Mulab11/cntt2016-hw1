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

Vi V;
int n,res;

void work(db y){	//计算贡献
	int tmp=0;
	For(i,0,n-1){
		if (V[i]<=y&&y<=V[i+1]||V[i+1]<=y&&y<=V[i]) tmp++;
	}
	For(i,1,n-1){
		if (fabs(y-V[i])<1e-9) tmp--;
	}
	res=max(res,tmp);
}

class PiecewiseLinearFunction{
public:
	int maximumSolutions(Vi V){
		::V=V;
		n=V.size();
		For(i,0,n-1) if (V[i]==V[i+1]) return -1;
		For(i,0,n){	//答案是可能是这三种情况
			work(V[i]);
			work(V[i]+0.5);
			work(V[i]-0.5);
		}
		return res;
	}
} T;