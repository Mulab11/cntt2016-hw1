// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define clr(a) memset(a,0,sizeof a)
#define cpy(a,b) memcpy(a,b,sizeof a)
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

const int mo=1e9+7;

inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}

LL a,b,c,m;
int n,sa,sb,idx,Tc,A[88],B[88],ID[15][15],M[88][88],Q[88][88];
char s[15],t[15];

inline void mul(){
	cpy(Q,M);clr(M);
	For(i,1,idx)For(k,1,idx)For(j,1,idx)
		inc(M[i][j],1ll*Q[i][k]*Q[k][j]%mo);
}

inline void prod(){
	cpy(B,A);clr(A);
	For(i,1,idx)For(k,1,idx)
		inc(A[i],1ll*M[i][k]*B[k]%mo);
}

inline int Main(){
	rep(i,0,n)if(s[i]=='a'){
		if(t[i]=='b')m-=a,++Tc,++sa;
		else if(t[i]=='c')m-=a+b,Tc+=2,++sb;
	}else if(s[i]=='b'){
		if(t[i]=='c')m-=b,++Tc,++sa;
		else if(t[i]=='a')m-=b+c,Tc+=2,++sb;
	}else if(s[i]=='c'){
		if(t[i]=='a')m-=c,++Tc,++sa;
		else if(t[i]=='b')m-=c+a,Tc+=2,++sb;
	}
	// 处理必要的代价
	if(m<0)return puts("0"),0;
	Tc+=m/(a+b+c)*3;
	// 剩余可走的步数为Tc
	For(i,0,n)For(j,0,n-i)ID[i][j]=++idx;++idx;
	// hash状态
	A[ID[sa][sb]]=1;
	For(i,0,n)For(j,0,n-i){
		if(i)inc(M[ID[i-1][j]][ID[i][j]],i);
		if(j)inc(M[ID[i+1][j-1]][ID[i][j]],j);
		if(n-i-j)inc(M[ID[i][j+1]][ID[i][j]],n-i-j);
	}
	inc(M[idx][idx],1);
	inc(M[idx][ID[0][0]],1);
	//构造转移矩阵
	for(++Tc;Tc;Tc>>=1,mul())if(Tc&1)prod();
	return A[idx];
}

struct ConversionMachine{
	int countAll(string word1, string word2, vector <int> costs, int maxCost){
		n=word1.length();
		rep(i,0,n)s[i]=word1[i],t[i]=word2[i];
		a=costs[0];b=costs[1];c=costs[2];
		m=maxCost;
		// 读入数据
		return Main();
	}
};