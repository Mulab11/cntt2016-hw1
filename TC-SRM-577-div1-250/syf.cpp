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
#include<numeric>
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

const int N=500+19;

stringstream ss;
int id[N],A[N];
int n,R,num1,num2;
db res,tmp,pro1,pro2;

bool cmp(int x,int y) {return A[x]>A[y];}

class EllysRoomAssignmentsDiv1{	//特判后，随便算一下概率
public:
	db getAverage(Vs V){
		ss<<accumulate(V.begin(),V.end(),string());
		while (ss>>A[++n]);n--;
		For(i,1,n+1) id[i]=i;
		sort(id+1,id+n+1,cmp);
		R=n%20==0?n/20:n/20+1;
		if (n%R==0){
			num1=n/R;pro1=1;
			num2=n/R;pro2=0;
		} else{
			num1=n/R+1;pro1=1.0*(n%R)/R;
			num2=n/R;pro2=1-pro1;
		}
		for (int l=1,r=R;l<=n;l=r+1,r=min(l+R-1,n)){
			int b=1,c=0;
			if (r==n) c=1;
			For(i,l,r+1) if (id[i]==1) b=0;
			if (!b){
				if (c) return (res+A[1])/num1;
				continue;
			}
			if (c){
				For(i,l,r+1) tmp+=1.0*A[id[i]]/(r-l+1);
			} else{
				For(i,l,r+1) res+=1.0*A[id[i]]/R;
			}
		}
		return pro1*(res+tmp+A[1])/num1+pro2*(res+A[1])/num2;
	}
} T;