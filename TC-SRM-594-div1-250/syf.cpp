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

int A[N],B[N];
int res,n,m;

int Work(int a,int b){
	static int f[N][N];
	memset(f,0,sizeof(f));
	For(i,1,n+1) For(j,1,m+1)
		if (1ll*A[i]*b==1ll*B[j]*a){	//判断这一位是否相同
			f[i][j]=f[i-1][j-1]+1;
		} else{
			f[i][j]=max(f[i-1][j],f[i][j-1]);
		}
	return f[n][m];
}

class AstronomicalRecords{
public:
	int minimalPlanets(Vi V1,Vi V2){
		n=V1.size();
		m=V2.size();
		For(i,1,n+1) A[i]=V1[i-1];
		For(i,1,m+1) B[i]=V2[i-1];
		For(i,1,n+1) For(j,1,m+1) res=max(res,Work(A[i],B[j])); //对两个序列求解LCS
		return n+m-res;
	}
} T;