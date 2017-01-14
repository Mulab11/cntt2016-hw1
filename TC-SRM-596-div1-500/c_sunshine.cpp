#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
class BitwiseAnd
{
	public:
	int cnt[66];
	vector<LL> lexSmallest(vector<LL> subset,int N)
	{
		//Check the given subset.
		vector<LL> null;
		int m=subset.size();
		for(int i=0;i<m;i++)
			for(int j=i+1;j<m;j++)
				if((subset[i]&subset[j])==0)
					return null;
		for(int i=0;i<m;i++)
			for(int j=i+1;j<m;j++)
				for(int k=j+1;k<m;k++)
					if((subset[i]&subset[j]&subset[k])!=0)
						return null;
		//Count the occurrence number of each bit.
		for(int i=0;i<m;i++)
			for(int j=0;j<60;j++)
				if(subset[i]>>j&1)
					cnt[j]++;
		//Each bit must occur no more than 2 times.
		while(subset.size()<N)
		{
			LL t=0;
			for(int i=0,j;i<subset.size();i++)
			{
				//Let x be the new number to be added into the set.
				//For each number y in the current set.
				//We find a bit where x and y both have 1.
				for(j=0;j<60;j++)//enumerate j from 0 to 59 to get the minimum number.
					if((subset[i]>>j&1LL)&&cnt[j]==1)
					{
						t^=1LL<<j;
						break;
					}
				if(j==60)//Can't find such bits.
					return null;
			}
			//We should place extra 1 in x so that the following numbers to be added into the set can find the bit.
			for(int i=0,j=0;j<=60&&i<N-subset.size()-1;j++)
			{
				if(j==60)
					return null;
				if(cnt[j]==0)
				{
					t^=1LL<<j;
					i++;
				}
			}
			subset.push_back(t);
			//Update the occurrence times.
			for(int j=0;j<60;j++)
				if(t>>j&1LL)
					cnt[j]++;
		}
		sort(subset.begin(),subset.end());
		return subset;
	}
};

