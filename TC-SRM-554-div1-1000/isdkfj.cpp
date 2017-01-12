#include <bits/stdc++.h>

using namespace std;

const int ce[][4]={{1,1,1,1},{1,1,1,2},{1,1,2,1},{1,2,1,1},{1,2,1,2},{1,2,2,1},
{1,1,2,2},{1,2,2,2},{1,2,2,3},{1,2,3,2},{1,2,1,3},{1,2,3,1},{1,2,3,3},{1,1,2,3},{1,2,3,4}};
const int ke[]={4,2,2,2,2,0,2,2,0,1,1,0,1,1,0};//最小表示法 15种状态 
typedef long long LL;
const int mo=1234567891;
const LL mo2=mo*LL(mo);
int C,K,m,mt[4];
LL A[121][121],B[121][121],qq[121],H;
int gan(int i,int j){return i*15+j;}//标号 
int hao(){//最小表示 
	int kk[4],ii=0,jj;
	for(int i=0;i<4;++i){
		jj=0;
		for(int j=0;j<i;++j)if(mt[j]==mt[i]){jj=kk[j];break;}
		if(jj)kk[i]=jj;else kk[i]=++ii;
	}
	for(int i=0;i<15;++i){
		bool f=1;
		for(int j=0;j<4;++j)if(ce[i][j]!=kk[j])f=0;
		if(f)return i;
	}
	return -1;
}
void dfs(int i,int j,int x,int s,int t){//搜索转移 
	if(x==4){
		int w=0;
		for(int k=0;k<4;++k)if(mt[k]==ce[j][k])++w;
		w+=mt[0]==mt[1];w+=mt[0]==mt[2];
		w+=mt[3]==mt[1];w+=mt[3]==mt[2];
		if(i+w<=K){
			(A[gan(i,j)][gan(i+w,hao())]+=s)%=mo;//构造转移矩阵 
			(A[gan(i,j)][m]+=s)%=mo;
		}
		return;
	}
	for(int k=1;k<=t;++k){
		mt[x]=k;
		dfs(i,j,x+1,s,t);
	}
	if(t+1<=C){//新的颜色 
		mt[x]=t+1;
		dfs(i,j,x+1,s*LL(C-t)%mo,t+1);
	}
}
void mul(LL (*a)[121],LL (*b)[121]){//矩阵乘法 
	static LL c[121][121];
	memset(c,0,sizeof c);
	for(int i=0;i<=m;++i)
		for(int j=0;j<=m;++j){
			LL tmp=0;
			for(int k=0;k<=m;++k){
				tmp+=LL(a[i][k])*b[k][j];
				if(tmp>=mo2)tmp-=mo2;
			}
			c[i][j]=tmp%mo;
		}
	memcpy(a,c,sizeof c);
}

class TheBrickTowerHardDivOne {
public:
	int find(int C, int K, long long H) {
		::C=C;::K=K;::H=H;
		m=(K+1)*15;A[m][m]=1;
		for(int i=0;i<=K;++i)
			for(int j=0;j<15;++j){
				int f=0;
				for(int k=0;k<4;++k)if(ce[j][k]>f)f=ce[j][k];
				if(f<=C&&ke[j]<=K)dfs(i,j,0,1,f);
			}
		for(int i=0;i<15;++i){
			int f=0,s=1;
			for(int j=0;j<4;++j)if(ce[i][j]>f)f=ce[i][j];
			for(int j=1;j<=f;++j)s=LL(s)*(C-j+1)%mo;
			if(ke[i]<=K){
				qq[gan(ke[i],i)]=s;
				qq[m]=(qq[m]+s)%mo;
			}//构造初始矩阵 
		}
		for(int i=0;i<=m;++i)B[i][i]=1;
		for(LL u=H-1;u;u>>=1){//快速幂 
			if(u&1)mul(B,A);
			mul(A,A);
		}
		LL ans=0;
		for(int i=0;i<=m;++i)ans=(ans+LL(qq[i])*B[i][m])%mo;
		return int(ans);
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
