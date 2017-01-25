#include <vector>
#include <string>
using namespace std;
class TreeUnion{
public:
	int N,f[2][310],g[310][5];
	void read(vector<string>T,int*f,int&n){
		*f=f[1]=0;n=1;
		for(int i=0;i<T.size();i++)
			for(int j=0;j<T[i].length();j++)T[i][j]==' '?f[++n]=0:(f[n]*=10)+=T[i][j]-'0';
		n++;
	}
	double expectedCycles(vector <string> tree1, vector <string> tree2, int K){
		read(tree1,f[0],N);read(tree2,f[1],N);
		int cnt[2][5]={0};
		for(int t=0;t<2;t++){
			for(int i=0;i<N;i++)
				for(int j=0;j<5;j++)g[i][j]=!j;
			for(int i=N-1;i;i--){
				for(int j=0;j<=4;j++)
					if(g[f[t][i]][j])for(int k=0;j+k<4;k++)cnt[t][j+k+1]+=g[i][k]*g[f[t][i]][j];
				for(int j=0;j<4;j++)g[f[t][i]][j+1]+=g[i][j];
			}
		}
		double ans=0;
		for(int i=1,j=K-2-i;j;i++,j--)ans+=2.0*cnt[0][i]*cnt[1][j];
		return ans/N/(N-1);
	}
};
