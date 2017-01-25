// WA on System Test
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#define MOD 100007
using namespace std;
class FencingPenguins{
public:
	int cnt[233][233]; // cnt[i][j]:有向三角形0-i-j包含的点数
	bool cut[233][233]; // cut[i][j]:边i-j是否把同一颜色分开
	int poly(int i,int j,int k){return cnt[i][j]+cnt[j][k]+cnt[k][i];} // 多边形i-j-k内的点数
	int poly(int i,int j,int k,int l){return cnt[i][j]+cnt[j][k]+cnt[k][l]+cnt[l][i];}; // 多边形i-j-k-l内的点数
	// f[l][r][k]:l~r部分画线段，要求 (1)l-r边对应的多边形至少k个点(2)同色点不被分开(3)所有点在多边形内 的方案数
	// g[l][r]:l~r部分将所有点包住的方案数
	int f[233][233][2],g[233][233];
	double area(double x1,double y1,double x2,double y2,double x3,double y3){ // 三角形有向面积*2
		return x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2);
	}
	bool inside(double x1,double y1,double x2,double y2,double x3,double y3,double x,double y){ // 判断(x,y)是否在三角形内
		return fabs(area(x1,y1,x2,y2,x,y))+fabs(area(x2,y2,x3,y3,x,y))+fabs(area(x3,y3,x1,y1,x,y))-fabs(area(x1,y1,x2,y2,x3,y3))<1e-13;
	}
	int countWays(int n, int radius, vector <int> x, vector <int> y, string color){
		// 预处理
		double PI=acos(-1),xi,yi,xj,yj;
		int ex[128][2]={0};
		for(int i=0;xi=cos(2*PI*i/n),yi=sin(2*PI*i/n),i<n;i++)
			for(int j=i+1;xj=cos(2*PI*j/n),yj=sin(2*PI*j/n),j<n;j++)
				for(int k=0;k<x.size();k++)
					inside(1,0,xi,yi,xj,yj,x[k]*1.0/radius,y[k]*1.0/radius)?cnt[i][j]++,cnt[j][i]--:1,
					ex[color[k]][area(xi,yi,xj,yj,x[k]*1.0/radius,y[k]*1.0/radius)>0]=i*n+j,ex[color[k]][0]==i*n+j&&ex[color[k]][1]==i*n+j?cut[i][j]=1:1;
		int sum=cnt[n-1][0];
		for(int i=1;i<n;i++)sum+=cnt[i-1][i];
		if(sum<x.size())return 0; // 判掉无解的情况
		// DP
		for(int l=n-2;l>=0;l--){
			for(int r=l+1;r<n;r++){
				// 1:l~r只有一条边，要求k=0且l l+1 r-1 r多边形内没有点
				f[l][r][0]=l+1==r||!poly(l,l+1,r-1,r)?l+1<r-1?g[l+1][r-1]:1:0;
				f[l][r][1]=0;
				// 2:l~r有多条边，枚举l的下一个点i，要求l l+1 i-1 i多边形内没有点
				for(int i=l+1;i<r;i++)if(!cut[l][i]&&(l+1==i||!poly(l,l+1,i-1,i))){
					long long t=l+1<i-1?g[l+1][i-1]:1;
					f[l][r][0]=(f[l][r][0]+t*f[i][r][0])%MOD;
					f[l][r][1]=(f[l][r][1]+t*f[i][r][!poly(l,i,r)])%MOD;
				}
				g[l][r]=l+1<r?poly(l,l+1,r)?0:g[l+1][r]:1;
				for(int i=l+1;i<=r;i++){
					if(!cut[l][i]&&(i==r||!poly(l,i,i+1,r)))g[l][r]=(g[l][r]+1ll*f[l][i][1]*(i+1<r?g[i+1][r]:1))%MOD;
				}
			}
		}
		return g[0][n-1];
	}
};
