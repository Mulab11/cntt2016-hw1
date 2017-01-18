#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<ctime>
#include<algorithm>
#include<iomanip>
#include<vector>
using namespace std;
#define MAXN 51
struct RockPaperScissors
{
	double p1[MAXN],p2[MAXN],p3[MAXN];
	int n;
	double p[MAXN][MAXN][MAXN][MAXN];
	double bestScore(vector<int>_p1,vector<int>_p2,vector<int>_p3)
	{
		int i,j,k,l,u;
		n=_p1.size();
		for(i=1;i<=n;i++)
		{
			p1[i]=1.0*_p1[i-1]/300;
			p2[i]=1.0*_p2[i-1]/300;
			p3[i]=1.0*_p3[i-1]/300;
		}
		for(i=1;i<=n;i++)
		{
			p[0][0][0][i]=1;
		}
		for(l=1;l<=n;l++)
		{
			for(u=1;u<=n;u++)
			{
				for(i=l;~i;i--)
				{
					for(j=l-i;~j;j--)
					{
						for(k=l-i-j;~k;k--)
						{
							double t=0;
							if(i)
							{
								t+=p[i-1][j][k][u]*p1[l];
							}
							if(j)
							{
								t+=p[i][j-1][k][u]*p2[l];
							}
							if(k)
							{
								t+=p[i][j][k-1][u]*p3[l];
							}
							double pp=1.0*(i+j+k)/l;
							p[i][j][k][u]*=1-pp;
							if(u!=l)
							{
								p[i][j][k][u]+=pp*t;
							}
						}
					}
				}
			}
		}
		double re=0;
		for(i=0;i<n;i++)
		{
			for(j=0;i+j<n;j++)
			{
				for(k=0;i+j+k<n;k++)
				{
					double pn1=0;
					double pn2=0;
					double pn3=0;
					for(l=1;l<=n;l++)
					{
						pn1+=p1[l]*p[i][j][k][l]/(n-i-j-k);
						pn2+=p2[l]*p[i][j][k][l]/(n-i-j-k);
						pn3+=p3[l]*p[i][j][k][l]/(n-i-j-k);
					}
					re+=max(3*pn1+pn2,max(3*pn2+pn3,3*pn3+pn1));
					
				}
			}
		}
		return re;
	}
};