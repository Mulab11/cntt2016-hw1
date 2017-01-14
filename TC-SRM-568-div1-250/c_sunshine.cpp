#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class BallsSeparating
{
	public:
	int minOperations(vector<int> red,vector<int> green,vector<int> blue)
	{
		int n=red.size(),ans=1<<30;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)if(j!=i)
				for(int k=0;k<n;k++)if(k!=i&&k!=j)
				{
					//Move all redundant red balls into i-th box,
					//green ones into j-th box, and blue ones into k-th box.
					int cost=0;
					cost+=green[i]+blue[i];
					cost+=red[j]+blue[j];
					cost+=red[k]+green[k];
					for(int p=0;p<n;p++)
						if(p!=i&&p!=j&&p!=k)//keep the most number of color of balls.
							cost+=red[p]+green[p]+blue[p]-max(max(red[p],green[p]),blue[p]);
					ans=min(ans,cost);
				}
		return ans<1<<30?ans:-1;
	}
};

