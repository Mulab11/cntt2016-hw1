#include<vector>
#include<string>
#include<cmath>
#define M 100007
#define pi acos(-1.0)
using namespace std;

int m,c[233];
double ax[233],ay[233];
long long s[233][233],cl[233][233],f[233][233],g[233][233],h[233][233][2];
bool v[233][233];
class FencingPenguins{
	public:
		double cross(double x0,double y0,double x1,double y1,double x2,double y2){
			return (x1-x0)*(y2-y0)-(y1-y0)*(x2-x0);
		}
		int countWays(int n,int r,vector<int> x,vector<int> y,string col){
			m=x.size();
			for(int i=0;i<m;i++)c[i]=col[i]<='Z'?col[i]-'A':col[i]-'a'+26;
			for(int i=0;i<n;i++)ax[i]=(double)r*cos(2.0*pi/n*i),ay[i]=(double)r*sin(2.0*pi/n*i);
			for(int i=0;i<n;i++)for(int j=0;j<n;j++)for(int k=0;k<m;k++)if(cross(ax[i],ay[i],ax[j],ay[j],x[k],y[k])>=0)s[i][j]|=1ll<<k,cl[i][j]|=1ll<<c[k];
			if(s[0][n-1])return 0;
			for(int i=0;i<n;i++)for(int j=0;j<n;j++)v[i][j]=!(cl[i][j]&cl[j][i]);
			for(int i=0;i<n;i++)h[i][i][1]=1;
			for(int del=1;del<n;del++)for(int i=0;i+del<n;i++){
				int j=i+del;
				for(int k=0;k<2;k++)for(int l=i+1;l<=j;l++)if(v[i][l]){
					long long x=h[l][j][k||(s[i][l]&s[l][j]&s[j][i])];
					if(!s[l][i])h[i][j][k]+=x;else if(l-i>3&&!(s[l][i]&s[i+1][l-1]))h[i][j][k]+=x*f[i+1][l-1];
				}
				h[i][j][0]%=M;h[i][j][1]%=M;
				for(int k=j;k>i+1;k--)if(v[i][k])if(!(s[j][i]&s[i][k]))g[i][j]+=h[i][k][0];else if(k<j-2&&!(s[j][i]&s[i][k]&s[k+1][j]))g[i][j]+=f[k+1][j]*h[i][k][0];
				g[i][j]%=M;
				for(int k=i;k<=j;k++)if(!(s[j][i]&s[k][j]))f[i][j]+=g[k][j];
				f[i][j]%=M;
			}
			return (int)f[0][n-1];
		}
};