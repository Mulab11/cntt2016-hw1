#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class BoundedOptimization
{
	public:
	
	int n;
	int g[20][20],LB[20],UB[20];
	
	int S[20],k;
	double ans,M,sum,a,c,val[20];
	
	double maxValue(vector<string> expr,vector<int> lowerBound,vector<int> upperBound,int maxSum)
	{
		string exp="";
		for(int i=0;i<expr.size();i++)
			exp+=expr[i];
		//Build the graph.
		for(int i=0,x,y;i<exp.size();i+=3)
		{
			x=exp[i]-'a',y=exp[i+1]-'a';
			g[x][y]=g[y][x]=1;
		}
		n=lowerBound.size();
		for(int i=0;i<n;i++)
			LB[i]=lowerBound[i],UB[i]=upperBound[i];
		int mask,maskub,other,flag,t;
		ans=0;
		for(mask=0;mask<1<<n;mask++)//pick the set whose elements are not lowerbound or upperbound.
		{
			k=0;
			for(int i=0;i<n;i++)
				if(mask>>i&1)S[k++]=i;
			flag=1;
			//We can prove these varibles must form a clique.
			for(int i=0;i<k&&flag;i++)
				for(int j=i+1;j<k;j++)
					if(mask>>S[i]&1&&mask>>S[j]&1&&!g[S[i]][S[j]])
					{flag=0;break;}
			if(!flag)continue;//Check it.
			other=(1<<n)-1^mask;
			for(maskub=other;maskub!=-1;maskub=maskub==0?-1:maskub-1&other)
			{
				//Pick other varibles to be lowerbound or upperbound.
				M=maxSum;
				for(int i=0;i<n;i++)
					if(!(mask>>i&1))
					{
						val[i]=maskub>>i&1?UB[i]:LB[i];
						M-=val[i];
					}
				if(M<-1e-9)continue;
				//With partial derivative, we can prove x[i]=( \sum val[j] [j is not in S and x_i * x_j occurs] )+C
				sum=0;
				for(int i=0;i<k;i++)
				{
					a=0;
					for(int j=0;j<n;j++)
						if(g[S[i]][j]&&!(mask>>j&1))
							a+=val[j];
					val[S[i]]=a;
					sum+=a;
				}
				c=(M-sum)/k;//get maximum C.
				flag=1;
				for(int i=0;i<k&&flag;i++)
				{
					val[S[i]]+=c;
					if(val[S[i]]<LB[S[i]]-1e-9||val[S[i]]>UB[S[i]]+1e-9)flag=0;
				}
				//Some varibles are not in range [lowerbound,upperbound]
				if(!flag)continue;
				sum=0;
				//Calculate and update the answer.
				for(int i=0;i<n;i++)
					for(int j=i+1;j<n;j++)
						if(g[i][j])sum+=val[i]*val[j];
				ans=max(ans,sum);
			}
		}
		return ans;
	}
	
};

