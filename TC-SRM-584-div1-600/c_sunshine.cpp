#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;

class Excavations
{
	public:
	int n,K;
	LL C[55][55];
	vector<int> building[55],got;
	
	LL f[2][55][55],g[2][55][55];
	
	LL calc(int D)
	{
		LL res=0;
		//f[t][i][j]: first i kinds of buildings, among them j buildings have already been seen
		//t = 0/1 means D is/isn't the least
		for(int i=1;i<=50;i++)//enumerate all kinds of buildings
		{
			int A=0,B=building[i].size(),E=0;
			for(int j=0;j<B;j++)
				if(building[i][j]<=D)
				{
					A++;
					E+=(building[i][j]==D);
				}
			//A is the number of the buildings whose depths are less than or equal to D
			//B is the number of this kind of buildings
			//E is the number of the buildings whose depths are equal to D
			for(int j=0;j<=B;j++)
				if(got[i])//this kind should be seen
				{
					g[0][i][j]=C[B][j]-C[B-A][j];//at least one of this kind of buildings can be seen
					g[1][i][j]=0;
					if(j!=0)
						for(int k=1;k<=E&&k<=j;k++)//can be seen and D is least
							g[1][i][j]+=C[E][k]*C[B-A][j-k];
							//that means at least one building whose depth is exactly D can be seen
							//and all visible buildings' depths can't be less than D
					g[1][i][j]=g[0][i][j]-g[1][i][j];//D is not least
				}
				else//none of this kind of buildings can be seen
				{
					g[0][i][j]=g[1][i][j]=C[B-A][j];
				}
		}
		memset(f,0,sizeof(f));
		f[0][0][0]=f[1][0][0]=1;
		for(int i=1;i<=50;i++)
			for(int j=0;j<=K;j++)
				for(int k=0;j+k<=K;k++)
				{
					f[0][i][j+k]+=f[0][i-1][j]*g[0][i][k];
					f[1][i][j+k]+=f[1][i-1][j]*g[1][i][k];
				}
		res=f[0][50][K]-f[1][50][K];
		return res;
	}
	
	LL count(vector<int> kind,vector<int> depth,vector<int> found,int K)
	{
		this->K=K;
		//calculate the combinatorial numbers
		for(int i=0;i<=50;i++)
			for(int j=C[i][0]=C[i][i]=1;j<i;j++)
				C[i][j]=C[i-1][j-1]+C[i-1][j];
		n=kind.size();
		vector<int> vd;
		for(int i=0;i<depth.size();i++)
			vd.push_back(depth[i]);
		sort(vd.begin(),vd.end());
		vd.erase(unique(vd.begin(),vd.end()),vd.end());
		for(int i=0;i<depth.size();i++)
			for(int j=0;j<vd.size();j++)
				if(vd[j]==depth[i])
				{
					depth[i]=j+1;
					break;
				}
		for(int i=0;i<n;i++)
			building[kind[i]].push_back(depth[i]);
		got=vector<int>(55,0);
		for(int i=0;i<found.size();i++)
			got[found[i]]=1;
		//Above is dealing with the input data
		//Every feasible subset of buildings has exactly one minimum digging depth limit
		LL ans=0;
		//We can enumerate all possible d as a digging depth limit
		for(int i=1;i<=vd.size();i++)
			ans+=calc(i);//Count the ways satisfying d but not any depth less than d
		return ans;
	}
};

