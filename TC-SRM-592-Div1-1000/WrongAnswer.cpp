#include <vector>
using namespace std;
class SplittingFoxes2{
public:
	int N,iN,a[30],b[30],c[30],ans[30],p,g,ig,s[10000][2],sc[10000];
	void DFT(int*f,int*t,bool r=0){
		for(int i=0,j,x=1;i<N;i++,x=x*(r?ig:g)%p)
			for(t[i]=0,j=N-1;j>=0;j--)t[i]=(t[i]*x+f[j])%p;
		if(r)for(int i=0;i<N;i++)t[i]=t[i]*iN%p;
	}
	void dfs(int i){
		if(i==N){
			DFT(b,c,1);
			for(int s=i=0;i<N;i++){
				for(int j=s=0;j<N;j++)s+=c[j]*c[(i-j+N)%N];
				if(s!=a[i])return;
			}
			for(i=0;i<N;i++)if(c[i]!=ans[i]){
				if(ans[i]==-1||c[i]<ans[i])for(;i<N;i++)ans[i]=c[i];
				return;
			}
			return;
		}
		int x=b[i];
		for(int j=0;j<sc[x];j++)
			if((b[i]=s[x][j])==b[(N-i)%N]||(N-i)%N>=i)dfs(i+1);
		b[i]=x;
	}
	void init(){
		const int P[26]={0,1009,1009,1009,1009,1021,1009,1009,1009,1009,1021,1013,1009,1093,1009,1021,1009,1021,1009,1103,1021,1009,1013,1013,1009,1051},
				  G[26]={0,1,1008,374,469,802,375,935,762,922,432,122,160,124,904,642,179,81,448,749,637,949,209,586,648,644};
		p=P[N];g=G[N];
		for(int i=0;i<p;i++)sc[i]=0;
		for(int i=0;i<p;i++)s[i*i%p][sc[i*i%p]++]=i,i*N%p==1?iN=i:1,i*g%p==1?ig=i:1;
	}
	vector <int> getPattern(vector <int> amount){
		for(int i=0;i<(N=amount.size());i++)a[i]=amount[i];
		init();
		DFT(a,b);
		ans[0]=-1;
		dfs(0);
		vector<int>res;
		for(int i=0;i<N;i++){
			res.push_back(ans[i]);
			if(ans[i]==-1)break;
		}
		return res;
	}
};
