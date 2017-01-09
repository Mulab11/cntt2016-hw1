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

const int N=2500+19;

string s;
int f[N],g[N],A[N][N],C[N][N],n;
ll res;

class LittleElephantAndRGB{
public:
	ll getNumber(Vs V,int minG){
		s=accumulate(V.begin(),V.end(),string());
		n=s.length();
		memset(A,0,sizeof(A));
		for (int i=n-1;~i;i--)
			For(j,i,n){
				A[i][j]=(s[i]=='G'?A[i+1][j]+1:0);
				C[i][j]=max(max(C[i+1][j],C[i][j-1]),A[i][j]);
			}
		memset(A,0,sizeof(A));	
		for (int i=n-1;~i;i--)
			For(j,i,n){
				A[i][j]=(s[j]=='G'?A[i][j-1]+1:0);
				C[i][j]=max(max(C[i+1][j],C[i][j-1]),A[i][j]);
			}	//预处理每一段区间内的信息
			
		for (int i=n-1;~i;i--){
			for (int j=i,b=1,sum=0;~j;j--){	//枚举答案，利用之前处理好的信息计算总和
				if (s[j]!='G') b=0;
				if (b) sum++;
				if (C[j][i]>=minG) sum=minG;
				res+=f[max(minG-sum,0)];
			}
			memset(g,0,sizeof(g));
			for (int j=i,b=1,sum=0;j<n;j++){
				if (s[j]!='G') b=0;
				if (b) sum++;
				if (C[i][j]>=minG) sum=minG;
				g[sum]++;
			}
			for (int j=n-1;~j;j--){
				g[j]+=g[j+1];
				f[j]+=g[j];
			}
		}
		return res;
	}
} T;