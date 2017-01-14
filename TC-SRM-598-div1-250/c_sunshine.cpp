#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class BinPacking
{
	public:
	vector<int> s;
	
	int calc()
	{
		//It is best to match the least item with the largest one.
		int res=s.size();
		for(int i=0,j=s.size()-1;i<j;i++)
		{
			for(;j>i&&s[j]+s[i]>300;j--);
			if(j>i)res--,j--;
		}
		return res;
	}
	
	int minBins(vector<int> item)
	{
		sort(item.begin(),item.end());
		int ans=0,best=item.size();
		//items larger than 200 can't be in the same box with others
		while(!item.empty()&&item.back()>200)
			item.pop_back(),ans++;
		for(int i=0;i*3<=item.size();i++)//pick how many boxes containing 3 100-size items.
			if(i==0||item[i*3-1]==100)
			{
				s.clear();
				for(int j=i*3;j<item.size();j++)
					s.push_back(item[j]);
				best=min(best,i+calc());
			}
		ans+=best;
		return ans;
	}
};

