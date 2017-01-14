#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class TreeUnion
{
	public:
	int n;
	int g1[999][999],g2[999][999];
	int cnt1[999],cnt2[999];
	
	double expectedCycles(vector<string> tree1,vector<string> tree2,int K)
	{
		//The cycle can only go to another tree and back for one time.
		//So we can pick tetrad (a,b,c,d) satisfying dist1(a,b)+dist2(c,d)+2=K.
		string Tree1,Tree2;
		for(int i=0;i<tree1.size();i++)Tree1+=tree1[i];
		for(int i=0;i<tree2.size();i++)Tree2+=tree2[i];
		memset(g1,31,sizeof(g1));
		memset(g2,31,sizeof(g2));
		vector<int> T1,T2;
		for(int t=0,i=0;i<=Tree1.size();i++)
		{
			if(i==Tree1.size()||Tree1[i]==' ')
				T1.push_back(t),t=0;
			else t=t*10+Tree1[i]-'0';
		}
		for(int t=0,i=0;i<=Tree2.size();i++)
		{
			if(i==Tree2.size()||Tree2[i]==' ')
				T2.push_back(t),t=0;
			else t=t*10+Tree2[i]-'0';
		}
		n=T1.size()+1;
		for(int i=0;i+1<n;i++)
			g1[T1[i]][i+1]=g1[i+1][T1[i]]=1;
		for(int i=0;i+1<n;i++)
			g2[T2[i]][i+1]=g2[i+1][T2[i]]=1;
		//Use floyd to get the dist1/dist2(x,y).
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					g1[i][j]=min(g1[i][j],g1[i][k]+g1[k][j]),
					g2[i][j]=min(g2[i][j],g2[i][k]+g2[k][j]);
		double ans=0,one=2.0/(n*(n-1));
		//for each distance count the number of pairs.
		for(int a=0;a<n;a++)
			for(int b=a+1;b<n;b++)
				cnt1[g1[a][b]]++;
		for(int a=0;a<n;a++)
			for(int b=a+1;b<n;b++)
				cnt2[g2[a][b]]++;
		for(int i=1;i<=K;i++)
		{
			int j=K-2-i;
			if(j>0)ans+=cnt1[i]*cnt2[j]*one;
		}
		return ans;
	}
};

