#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const double pi=acos(-1);
const int mo=100007;
struct point{
	double x,y;
}yu[255],po[55];
LL qe[255][255],col[55];
int h[255][255][2],g[255][255],f[255][255];
bool pe[255][255];

class FencingPenguins {
public:
	int countWays(int numPosts, int radius, vector <int> x, vector <int> y, string color) {
		int n=numPosts,m=x.size();
		for(int i=0;i<n;++i){
			double an=2*pi/n*i;
			yu[i].x=radius*cos(an);//求出圆上的点 
			yu[i].y=radius*sin(an);
		}
		for(int i=0;i<m;++i)po[i].x=x[i],po[i].y=y[i];
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
			if(i!=j)for(int k=0;k<m;++k)//求出i-j这条直线左边的点集 
			if((po[k].x-yu[i].x)*(yu[j].y-yu[i].y)<(yu[j].x-yu[i].x)*(po[k].y-yu[i].y))qe[i][j]|=1ll<<k;
		for(int i=0,j;i<m;++i){
			if(isupper(color[i]))j=color[i]-'A';
			else j=color[i]-'a'+26;
			col[j]|=1ll<<i;
		}
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				for(int k=0;k<52;++k)
				if((qe[i][j]&col[k])&&(qe[j][i]&col[k]))pe[i][j]=1;//判断是否会把颜色隔开 
		for(int i=0;i<n;++i)if(qe[i][(i+1)%n]!=(1ll<<m)-1)return 0;//!!!!!!判断有没有点圈不到 
		for(int i=0;i<n;++i)h[i][i][0]=1;//初始化 
		for(int len=1;len<n;++len)
			for(int l=0;l<n;++l){
				int r=l+len;if(r>=n)break;
				for(int i=l+1;i<=r;++i)if(!pe[l][i])
					for(int j=0;j<2;++j){
						LL o=qe[l][i]&qe[i][r]&qe[r][l];//三角形内部有没有点 
						if(qe[i][l]==0)h[l][r][j|(o>0)]=(h[l][r][j|(o>0)]+h[i][r][j])%mo;//l->i没有点 
						else if(i>l+3){
							LL qq=qe[i][l]&qe[l+1][i-1];
							if(qq==0)h[l][r][j|(o>0)]=(h[l][r][j|(o>0)]+LL(f[l+1][i-1])*h[i][r][j])%mo;
							//l->i有点但可以圈住 
						}
					}
				for(int i=l+2;i<=r;++i)if(!pe[l][i]){//枚举连哪个点 
					if((qe[l][i]&qe[r][l])==0)g[l][r]=(g[l][r]+h[l][i][1])%mo;
					else if(i+1<r&&(qe[l][i]&qe[r][l]&qe[i+1][r])==0)g[l][r]=(g[l][r]+LL(f[i+1][r])*h[l][i][1])%mo;
				}
				for(int i=l;i<r;++i)//第一个连边的点 
				if((qe[r][l]&qe[i][r])==0)f[l][r]=(f[l][r]+g[i][r])%mo;
			}
		return f[0][n-1];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
