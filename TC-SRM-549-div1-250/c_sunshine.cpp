#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const double eps=1e-11;

class PointyWizardHats
{
	public:
	
	int n,m;
	pair<double,double> A[55],B[55];
	bool used[55];
	
	int getNumHats(vector<int> topHeight,vector<int> topRadius,vector<int> bottomHeight,vector<int> bottomRadius)
	{
		n=topHeight.size();
		m=bottomHeight.size();
		//The limit is topRadius<bottomRadius and topHeight/topRadius>bottomHeight/bottomRadius.
		for(int i=0;i<n;i++)
			A[i]=make_pair((double)topRadius[i],(double)topHeight[i]/topRadius[i]);
		for(int i=0;i<m;i++)
		{
			used[i]=0;
			B[i]=make_pair((double)bottomRadius[i],(double)bottomHeight[i]/bottomRadius[i]);
		}
		sort(A,A+n);
		sort(B,B+m);
		//That means we can match A and B when A.first<B.first and A.second>B.second.
		//And we should find the maximum matching.
		int ans=0;
		//It is clear that we can use a greedy algorithm to solve it.
		for(int i=n-1;~i;i--)
		{
			int j,k=-1;
			//Find availble B[k] satisfying B[k].first>A[i].first and B[k].second is maximum.
			for(j=m-1;~j;j--)
				if(!used[j]&&B[j].first>A[i].first+eps&&B[j].second<A[i].second-eps)
				{
					if(k==-1||B[j].second>B[k].second)k=j;
				}
			if(k!=-1)//match A[i] and B[k]
			{
				ans++;
				used[k]=1;
			}
		}
		return ans;
	}
};

