#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;

int cur[51][51][51];
double die[51][3],P[51][25000];
double f[51][51][51];

class RockPaperScissors
{
	public:
	
	int n;
	
	void init()
	{
		int dn=0;
		//Only record all valid (i,j,k) that i+j+k<=n to save memory.
		for(int i=0;i<=n;i++)
			for(int j=0;i+j<=n;j++)
				for(int k=0;i+j+k<=n;k++)
					cur[i][j][k]=++dn;
		//Determine P[i][cur(r,p,s)] which is the probability that the i-th die is still in the bag 
		//and there have occured r rocks, p papers and s scissors.
		for(int i=1;i<=n;i++)
		{
			//f[r][p][s]: the probability that there have occured r rocks, p papers and s scissors and the i-th die's is still in the bag 
			memset(f,0,sizeof(f));
			f[0][0][0]=1;
			for(int t=1;t<=n;t++)
			{
				int r,p,s,m;
				double now,w;
				for(m=t;~m;m--)
					for(r=0;r<=m;r++)
						for(p=0;r+p<=m;p++)
						{
							s=m-r-p;
							w=(double)m/t;//the probability that the t-th die will be picked.
							f[r][p][s]*=1-w;
							if(t!=i)
							{
								now=0;
								if(r)now+=f[r-1][p][s]*die[t][0];
								if(p)now+=f[r][p-1][s]*die[t][1];
								if(s)now+=f[r][p][s-1]*die[t][2];
								f[r][p][s]+=now*w;
							}
						}
			}
			//Calculate P[i][cur[r][p][s]]
			for(int r=0;r<=n;r++)
				for(int p=0;r+p<=n;p++)
					for(int s=0;r+p+s<=n;s++)
						P[i][cur[r][p][s]]=f[r][p][s];
		}
	}
	
	double work()
	{
		int m,r,p,s;
		double Pr,Pp,Ps,t,ans=0;
		//For all possible situation
		for(m=n-1;~m;m--)
			for(r=0;r<=m;r++)
				for(p=0;r+p<=m;p++)
				{
					s=m-r-p;
					Pr=Pp=Ps=0;
					for(register int i=1;i<=n;i++)
					{
						t=P[i][cur[r][p][s]]/(n-m);//Next die picked is exactly i-th die.
						Pr+=t*die[i][0];
						Pp+=t*die[i][1];
						Ps+=t*die[i][2];
					}
					//Select the hand gestures with the most expected score.
					t=0;
					t=max(t,Pr*3+Pp);
					t=max(t,Pp*3+Ps);
					t=max(t,Ps*3+Pr);
					ans+=t;
				}
		return ans;
	}
	
	double bestScore(vector<int> rockProb,vector<int> paperProb,vector<int> scissorsProb)
	{
		n=rockProb.size();
		for(int i=1;i<=n;i++)
		{
			die[i][0]=rockProb[i-1];
			die[i][1]=paperProb[i-1];
			die[i][2]=scissorsProb[i-1];
			for(int j=0;j<3;j++)
				die[i][j]/=300.0;
		}
		init();
		return work();
	}
};

