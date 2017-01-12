#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int mo=1000000009;
int f[16][1<<16],g[9][1<<16];

inline void get(int&x,int y,int z){x=(x+LL(y)*z)%mo;}
inline void get(int&x,int y){if((x+=y)>=mo)x-=mo;}

class StringPath {
public:
	int countBoards(int n, int m, string A, string B) {
		if(n>m)swap(n,m);
		if(A[0]!=B[0])return 0;
		f[1][3]=1;
		for(int i=2;i<=n;++i)//前n个对角线，长度递增 
		if(A[i-1]!=B[i-1]){//字符不同 
			int fs=1<<(i<<1);
			memset(g[1],0,fs<<2);
			for(int s=0;s<fs>>2;++s)if(f[i-1][s]){
				if((s&3)==0)get(g[1][s<<2],f[i-1][s],26);//不能走 
				else if((s&3)==1)get(g[1][(s<<2)|1],f[i-1][s]),get(g[1][s<<2],f[i-1][s],25);//能走1 
				else if((s&3)==2)get(g[1][(s<<2)|2],f[i-1][s]),get(g[1][s<<2],f[i-1][s],25);//能走2 
				else get(g[1][(s<<2)|1],f[i-1][s]),get(g[1][(s<<2)|2],f[i-1][s]),get(g[1][s<<2],f[i-1][s],24);//走其中一个 
			}
			for(int j=1;j<i;++j){
				memset(g[j+1],0,fs<<2);
				for(int s=0;s<fs;++s)
				if(g[j][s]){
					int t=((s>>(j<<1))&3)|((s>>((j+1)<<1))&3),p=(s|(3<<(j<<1)))^(3<<(j<<1));
					if(t==0)get(g[j+1][p],g[j][s],26);//不能走 
					else if(t==1)get(g[j+1][p|(1<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走1 
					else if(t==2)get(g[j+1][p|(2<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走2 
					else get(g[j+1][p|(1<<(j<<1))],g[j][s]),get(g[j+1][p|(2<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],24);//走其中一个
				}
			}
			for(int s=0;s<fs;++s)f[i][s]=g[i][s];
		}else {
			int fs=1<<(i<<1);
			memset(g[1],0,fs<<2);
			for(int s=0;s<fs>>2;++s)if(f[i-1][s]){
				if((s&3)==0)get(g[1][s<<2],f[i-1][s],26);//不能走
				else if((s&3)==1)get(g[1][(s<<2)|1],f[i-1][s]),get(g[1][s<<2],f[i-1][s],25);//能走1 
				else if((s&3)==2)get(g[1][(s<<2)|2],f[i-1][s]),get(g[1][s<<2],f[i-1][s],25);//能走2
				else get(g[1][(s<<2)|3],f[i-1][s]),get(g[1][s<<2],f[i-1][s],25);//都能走 
			}
			for(int j=1;j<i;++j){
				memset(g[j+1],0,fs<<2);
				for(int s=0;s<fs;++s)
				if(g[j][s]){
					int t=((s>>(j<<1))&3)|((s>>((j+1)<<1))&3),p=(s|(3<<(j<<1)))^(3<<(j<<1));
					if(t==0)get(g[j+1][p],g[j][s],26);//不能走
					else if(t==1)get(g[j+1][p|(1<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走1
					else if(t==2)get(g[j+1][p|(2<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走2
					else get(g[j+1][p|(3<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//都能走
				}
			}
			for(int s=0;s<fs;++s)f[i][s]=g[i][s];
		}
		for(int i=n+1;i<=m;++i)
		if(A[i-1]!=B[i-1]){
			int fs=1<<(n<<1);
			memset(g[1],0,fs<<2);
			for(int s=0;s<fs;++s)if(f[i-1][s]){
				int t=(s&3)|((s>>2)&3),p=(s|3)^3;
				if(t==0)get(g[1][p],f[i-1][s],26);//不能走
				else if(t==1)get(g[1][p|1],f[i-1][s]),get(g[1][p],f[i-1][s],25);//能走1
				else if(t==2)get(g[1][p|2],f[i-1][s]),get(g[1][p],f[i-1][s],25);//能走2
				else get(g[1][p|1],f[i-1][s]),get(g[1][p|2],f[i-1][s]),get(g[1][p],f[i-1][s],24);//走其中一个
			}
			for(int j=1;j<n;++j){
				memset(g[j+1],0,fs<<2);
				for(int s=0;s<fs;++s)
				if(g[j][s]){
					int t=((s>>(j<<1))&3)|((s>>((j+1)<<1))&3),p=(s|(3<<(j<<1)))^(3<<(j<<1));
					if(t==0)get(g[j+1][p],g[j][s],26);//不能走
					else if(t==1)get(g[j+1][p|(1<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走1
					else if(t==2)get(g[j+1][p|(2<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走2
					else get(g[j+1][p|(1<<(j<<1))],g[j][s]),get(g[j+1][p|(2<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],24);//走其中一个
				}
			}
			for(int s=0;s<fs;++s)f[i][s]=g[n][s];
		}else {
			int fs=1<<(n<<1);
			memset(g[1],0,fs<<2);
			for(int s=0;s<fs;++s)if(f[i-1][s]){
				int t=(s&3)|((s>>2)&3),p=(s|3)^3;
				if(t==0)get(g[1][p],f[i-1][s],26);//不能走
				else if(t==1)get(g[1][p|1],f[i-1][s]),get(g[1][p],f[i-1][s],25);//能走1
				else if(t==2)get(g[1][p|2],f[i-1][s]),get(g[1][p],f[i-1][s],25);//能走2
				else get(g[1][p|3],f[i-1][s]),get(g[1][p],f[i-1][s],25);//都能走
			}
			for(int j=1;j<n;++j){
				memset(g[j+1],0,fs<<2);
				for(int s=0;s<fs;++s)
				if(g[j][s]){
					int t=((s>>(j<<1))&3)|((s>>((j+1)<<1))&3),p=(s|(3<<(j<<1)))^(3<<(j<<1));
					if(t==0)get(g[j+1][p],g[j][s],26);//不能走
					else if(t==1)get(g[j+1][p|(1<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走1
					else if(t==2)get(g[j+1][p|(2<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走2
					else get(g[j+1][p|(3<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//都能走
				}
			}
			for(int s=0;s<fs;++s)f[i][s]=g[n][s];
		}
		for(int i=m+1;i<=n+m-1;++i)
		if(A[i-1]!=B[i-1]){
			int fs=1<<((n+m-i+1)<<1);
			memset(g[1],0,fs<<2);
			for(int s=0;s<fs;++s)if(f[i-1][s]){
				int t=(s&3)|((s>>2)&3),p=(s|3)^3;
				if(t==0)get(g[1][p],f[i-1][s],26);//不能走
				else if(t==1)get(g[1][p|1],f[i-1][s]),get(g[1][p],f[i-1][s],25);//能走1
				else if(t==2)get(g[1][p|2],f[i-1][s]),get(g[1][p],f[i-1][s],25);//能走2
				else get(g[1][p|1],f[i-1][s]),get(g[1][p|2],f[i-1][s]),get(g[1][p],f[i-1][s],24);//走其中一个
			}
			for(int j=1;j<n+m-i;++j){
				memset(g[j+1],0,fs<<2);
				for(int s=0;s<fs;++s)
				if(g[j][s]){
					int t=((s>>(j<<1))&3)|((s>>((j+1)<<1))&3),p=(s|(3<<(j<<1)))^(3<<(j<<1));
					if(t==0)get(g[j+1][p],g[j][s],26);//不能走
					else if(t==1)get(g[j+1][p|(1<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走1
					else if(t==2)get(g[j+1][p|(2<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走2
					else get(g[j+1][p|(1<<(j<<1))],g[j][s]),get(g[j+1][p|(2<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],24);//走其中一个
				}
			}
			int tmp=fs>>2;--tmp;
			for(int s=0;s<fs;++s)get(f[i][s&tmp],g[n+m-i][s]);
		}else {
			int fs=1<<((n+m-i+1)<<1);
			memset(g[1],0,fs<<2);
			for(int s=0;s<fs;++s)if(f[i-1][s]){
				int t=(s&3)|((s>>2)&3),p=(s|3)^3;
				if(t==0)get(g[1][p],f[i-1][s],26);//不能走
				else if(t==1)get(g[1][p|1],f[i-1][s]),get(g[1][p],f[i-1][s],25);//能走1
				else if(t==2)get(g[1][p|2],f[i-1][s]),get(g[1][p],f[i-1][s],25);//能走2
				else get(g[1][p|3],f[i-1][s]),get(g[1][p],f[i-1][s],25);//都能走
			}
			for(int j=1;j<n+m-i;++j){
				memset(g[j+1],0,fs<<2);
				for(int s=0;s<fs;++s)
				if(g[j][s]){
					int t=((s>>(j<<1))&3)|((s>>((j+1)<<1))&3),p=(s|(3<<(j<<1)))^(3<<(j<<1));
					if(t==0)get(g[j+1][p],g[j][s],26);//不能走
					else if(t==1)get(g[j+1][p|(1<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走1
					else if(t==2)get(g[j+1][p|(2<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//能走2
					else get(g[j+1][p|(3<<(j<<1))],g[j][s]),get(g[j+1][p],g[j][s],25);//都能走
				}
			}
			int tmp=fs>>2;--tmp;
			for(int s=0;s<fs;++s)get(f[i][s&tmp],g[n+m-i][s]);
		}
		return f[n+m-1][3];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
