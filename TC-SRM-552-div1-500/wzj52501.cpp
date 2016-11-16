#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector> 
#define rep(i,s,t) for(int i=s;i<=t;i++)
#define dwn(i,s,t) for(int i=s;i>=t;i--)
using namespace std;
const int maxn=35;
const int maxm=2000;
const int inf=1e9;
struct FoxAndFlowerShopDivOne {
	int B[maxn][maxn],C[maxn][maxn],f[maxn][maxm],g[maxn][maxm];
	int sum(int x1,int y1,int x2,int y2) {return B[x2][y2]+B[x1-1][y1-1]-B[x2][y1-1]-B[x1-1][y2];}
	int calc(int x1,int y1,int x2,int y2) {return C[x2][y2]+C[x1-1][y1-1]-C[x2][y1-1]-C[x1-1][y2];}
	int theMaxFlowers(vector<string> A,int lim) {
		int n=A.size(),m=A[0].length();
		
		/*Preprocess*/
		
		memset(C,0,sizeof(C));
		memset(B,0,sizeof(B));
		rep(i,1,n) rep(j,1,m) {
			if(A[i-1][j-1]=='L') B[i][j]=1;
			if(A[i-1][j-1]=='P') B[i][j]=-1;
			if(B[i][j]) C[i][j]=1;
			B[i][j]+=B[i-1][j]+B[i][j-1]-B[i-1][j-1];
			C[i][j]+=C[i-1][j]+C[i][j-1]-C[i-1][j-1];
		}
		
		/*First Part*/
		
		rep(i,0,n+1) rep(j,0,1999) f[i][j]=-inf;   
		rep(i,0,n+1) rep(j,0,1999) g[i][j]=-inf;
		rep(i,1,n) {  //Calculate f[i][k]
			rep(j,1,m) rep(x,1,i) rep(y,1,j) { 
				int t=sum(x,y,i,j)+1000;
				f[i][t]=max(f[i][t],calc(x,y,i,j)); 
			}
			rep(j,0,1999) f[i][j]=max(f[i][j],f[i-1][j]);
		}
		dwn(i,n,1) {   //Calculate g[i][k]
			rep(j,1,m) rep(x,i,n) rep(y,j,m) {
				int t=sum(i,j,x,y)+1000;
				g[i][t]=max(g[i][t],calc(i,j,x,y)); 
			}
			rep(j,0,1999) g[i][j]=max(g[i][j],g[i+1][j]);
		}
		int ans=-inf; // Merge f & g to get the answer
		rep(i,1,n-1) rep(j,0,1999) rep(k,max(0,2000-j-lim),min(1999,2000+lim-j)) {
			if(j+k-2000>=-k&&j+k-2000<=k) ans=max(ans,f[i][j]+g[i+1][k]);
		}
		
		/*Second Part*/
		
		rep(i,0,m+1) rep(j,0,1999) f[i][j]=-inf;
		rep(i,0,m+1) rep(j,0,1999) g[i][j]=-inf;
		rep(i,1,m) {
			rep(j,1,n) rep(x,1,j) rep(y,1,i) {
				int t=sum(x,y,j,i)+1000;
				f[i][t]=max(f[i][t],calc(x,y,j,i)); 
			}
			rep(j,0,1999) f[i][j]=max(f[i][j],f[i-1][j]);
		}
		dwn(i,m,1) {
			rep(j,1,n) rep(x,j,n) rep(y,i,m) {
				int t=sum(j,i,x,y)+1000;
				g[i][t]=max(g[i][t],calc(j,i,x,y)); 
			}
			rep(j,0,1999) g[i][j]=max(g[i][j],g[i+1][j]);
		}
		rep(i,1,m-1) rep(j,0,1999) rep(k,max(0,2000-j-lim),min(1999,2000+lim-j)) {
			if(j+k-2000>=-k&&j+k-2000<=k) ans=max(ans,f[i][j]+g[i+1][k]);
		}
		
		
		return ans>=0?ans:-1;
	}
};
