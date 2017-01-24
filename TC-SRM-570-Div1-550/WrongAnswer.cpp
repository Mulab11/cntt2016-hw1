#include <vector>
using namespace std;
class CentaurCompany{
public:
	struct edge{int to;edge*next;}E[80],*ne,*first[40];
	void link(int a,int b){*ne=(edge){b,first[a]};first[a]=ne++;}
	int siz[40]; // siz[i]:i子树大小
	double mem[40][2][80],*f[40][2],*g[2]; // f(i,j,k):i子树内满足i选择状态为j(j=0,1)且V-2E-2=k的点集个数/2^siz[i]
	void dfs(int i,int fa){
		siz[i]=1;
		for(int j=0;j<2;j++)
			for(int k=-2;k<1;k++)f[i][j][k]=0.5*(k==j-2);
		for(edge*e=first[i];e;e=e->next)if(e->to!=fa){
			dfs(e->to,i);
			for(int j=0;j<2;j++)
				for(int k=-siz[i]-siz[e->to]-2;k<siz[i]+siz[e->to];k++)g[j][k]=0;
			for(int j1=0;j1<2;j1++)
				for(int j2=0;j2<2;j2++)
					for(int k1=-siz[i]-2;k1<siz[i];k1++)if(f[i][j1][k1])
						for(int k2=-siz[e->to]-2;k2<siz[e->to];k2++)if(f[e->to][j2][k2])
							g[j1][k1+k2+2*(!j1||!j2)]+=f[i][j1][k1]*f[e->to][j2][k2];
			siz[i]+=siz[e->to];
			for(int j=0;j<2;j++)
				for(int k=-siz[i]-2;k<siz[i];k++)f[i][j][k]=g[j][k];
		}
	}
	double getvalue(vector <int> a, vector <int> b){
		int N=a.size()+1;ne=E;
		for(int i=1;i<=N;i++){
			first[i]=0;
			f[i][0]=mem[i][0]+40;f[i][1]=mem[i][1]+40;
		}
		g[0]=mem[0][0]+40;g[1]=mem[0][1]+40;
		for(int i=0;i<a.size();i++)link(a[i],b[i]),link(b[i],a[i]);
		dfs(1,0);
		double ans=0;
		for(int i=1;i<siz[1];i++)ans+=(f[1][0][i]+f[1][1][i])*i;
		return ans*2;
	}
};
