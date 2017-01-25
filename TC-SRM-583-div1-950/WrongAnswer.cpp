#include <vector>
#include <string>
using namespace std;
class RandomPaintingOnABoard{
public:
	int N,M,A[22][22],a[22],f[1351],sum;
	double dfs(int S,int Ssum){
		double s=0;
		int Tsum=0;f[0]=-1;
		for(int i=0;i<M;Tsum+=a[i],i++)
			for(int j=Tsum+a[i];j>=0;j--)f[j]=(j>Tsum?0:f[j])-(j<a[i]?0:f[j-a[i]]);
		for(int i=0;i<=Tsum;i++)i+Ssum?s+=f[i]*(sum/(double)(i+Ssum)):1;
		for(int i=0;i<N&&!(S>>i&1);i++){
			for(int j=0;j<M;j++)a[j]-=A[i][j],Ssum+=A[i][j];
			s-=dfs(S|1<<i,Ssum);
			for(int j=0;j<M;j++)a[j]+=A[i][j],Ssum-=A[i][j];
		}
		return s;
	}
	double expectedSteps(vector <string> prob){
		bool t=(N=prob.size())>(M=prob[0].length());
		if(t){int x=N;N=M;M=x;}
		for(int i=0;i<M;i++)a[i]=0;sum=0;
		for(int i=0;i<N;i++)
			for(int j=0;j<M;j++)a[j]+=(A[i][j]=prob[t?j:i][t?i:j]-'0'),sum+=A[i][j];
		return dfs(0,0);
	}
};
