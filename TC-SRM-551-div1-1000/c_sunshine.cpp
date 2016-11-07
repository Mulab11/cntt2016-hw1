#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int M=1000000007;

int pow(int a,int b,int c=M)
{
	int s=1;
	for(;b;b>>=1,a=(LL)a*a%M)
		if(b&1)s=(LL)s*a%M;
	return s;
}

class SweetFruits
{
	public:
	int N,S;
	int sw[45],msw;
	int tree[45],C[45][45];
	
	int a[45][45];
	
	vector<LL> A[45],B[45];
	
	void adde(int u,int v)//Maintain the Kirchhoff's matrix when adding an edge.
	{a[u][v]--,a[v][u]--,a[u][u]++,a[v][v]++;}
	
	int det(int n)//Use Gaussian elimination to determine the determinant
	{
		int dc=1,i,j,k,t,res;
		for(i=1;i<=n;i++)
		{
			k=i;
			for(j=i;j<=n;j++)
				if(a[j][i]){k=j;break;}
			if(!a[k][i])return 0;
			if(k!=i)
			{
				dc=-dc;
				for(j=i;j<=n;j++)
					swap(a[i][j],a[k][j]);
			}
			for(j=i+1;j<=n;j++)
				if(a[j][i])
				{
					t=(LL)a[j][i]*pow(a[i][i],M-2)%M;
					for(k=i;k<=n;k++)
						a[j][k]=((LL)a[j][k]-(LL)t*a[i][k])%M;
				}
		}
		res=dc;
		for(int i=1;i<=n;i++)
			res=(LL)res*a[i][i]%M;
		if(res<0)res+=M;
		return res;
	}
	
	int spanning(int k)
	{
		//We can build a graph and count the spanning-trees of it.
		//Sweet but not truly sweet fruit can only be connected to fruits which are not sweet.
		memset(a,0,sizeof(a));
		for(int i=1;i<=N;i++)
			for(int j=i+1;j<=N;j++)
				if(j>S||i<=k&&j<=k)
					adde(i,j);
		//Use matrix-tree theorem to count them.
		return det(N-1);
	}
	
	int countTrees(vector<int> sweetness,int maxSweetness)
	{
		//Firstly, we use matrix-tree theorem to determine T[k] which is the number of ways that at most k fruits are truly sweet.
		//Then we can get tree[k] that is the number of ways that there are exactly k truly sweet fruits, with Inclusion-exclusion principle.
		//Since the vertices are labelled, it satisfies tree[k]=T[k]-\sum[j<k] Comb(k,j)*tree[j].
		//Then we use a meet-in-the-middle algorithm to calculate cnt[k], the number of ways to select exactly k fruits to be truly sweet,
		//and total sweetness of which do not exceed maxSweetness.
		//Finally return the answer which is \sum cnt[k]*tree[k].
		N=sweetness.size();msw=maxSweetness;
		for(int i=0;i<N;i++)
			sw[i]=sweetness[i],S+=sw[i]!=-1;
		sort(sw,sw+N,greater<int>());
		//combinatorial numbers
		for(int i=0,j;i<=N;i++)
			for(C[i][0]=C[i][i]=j=1;j<i;j++)
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%M;
		for(int k=0;k<=S;k++)
		{
			tree[k]=spanning(k);//Determine the number of ways that at most k sweets are truly sweet.
			for(int i=0;i<k;i++)//Use Inclusion-exclusion principle.
				tree[k]=((LL)tree[k]-(LL)C[k][i]*tree[i])%M;
			if(tree[k]<0)tree[k]+=M;
		}
		int SA=S/2,SB=S-SA,cnt,ans=0;
		LL sum;
		//Do first half part.
		for(int m=0;m<1<<SA;m++)
		{
			sum=cnt=0;
			for(int i=0;i<SA;i++)
				if(m&1<<i)cnt++,sum+=sw[i];
			A[cnt].push_back(sum);
		}
		//Do second half part.
		for(int m=0;m<1<<SB;m++)
		{
			sum=cnt=0;
			for(int i=0;i<SB;i++)
				if(m&1<<i)cnt++,sum+=sw[SA+i];
			B[cnt].push_back(sum);
		}
		for(int x=0;x<=SA;x++)
			sort(A[x].begin(),A[x].end());
		for(int y=0;y<=SB;y++)
			sort(B[y].begin(),B[y].end());
		for(int x=0;x<=SA;x++)//We select x sweet fruits in part A,
			for(int y=0;y<=SB;y++)//and select y sweet fruits in part B
			{
				int i,j;
				cnt=0;
				for(i=A[x].size()-1,j=0;i>=0;i--)
				{
					//Use two-pointers algorithm to get the number of ways.
					for(;j<B[y].size()&&A[x][i]+B[y][j]<=msw;j++)
						cnt++;
					ans=((LL)ans+(LL)cnt*tree[x+y])%M;//Add cnt[k]*tree[k] to the answer.
				}
			}
		return ans;
	}
};

