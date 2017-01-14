#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

class NextAndPrev
{
	public:
	
	int n,m;
	
	int had[333],to[333];
	
	int getMinimum(int nextCost,int prevCost,string start,string goal)
	{
		n=goal.size();
		if(start==goal)return 0;
		for(int i=0;i<n;i++)
			had[goal[i]]++;
		int flag=1;
		for(char i='a';i<='z';i++)
			if(!had[i])flag=0;
		if(flag)return -1;//All letters occur and we can't do any operations.
		for(int i=0;i<n;i++)//We can't change one kind of letters into different kinds.
			if(to[start[i]]==0)to[start[i]]=goal[i];
			else if(to[start[i]]!=goal[i])return -1;
		vector<pair<int,int> > v;
		for(char i='a';i<='z';i++)
			if(to[i])v.push_back(make_pair(i-'a',to[i]-'a'));
		m=v.size();
		int ans=(1<<30)-1;
		for(int st=0;st<m;st++)
		{
			sort(v.begin(),v.end());
			int can=1;
			for(int i=0;i<m-1;i++)
				if(v[i].second>v[i+1].second)can=0;
			if(can)
			{
				for(int p=-1;p<=2;p++)//the alphabet here is a cycle.
				{
					for(int i=0;i<m;i++)v[i].second+=p*26;
					int sum=0;
					for(int i=0,j;i<m;i=j)
					{
						for(j=i;j<m&&v[j].second==v[i].second;j++);//a group of letters will become the same letter.
						int low=v[i].second,high=v[i].second;
						for(int k=i;k<j;k++)
							low=min(low,v[k].first),
							high=max(high,v[k].first);
						//Count the cost.
						sum+=(v[i].second-low)*nextCost;
						sum+=(high-v[i].second)*prevCost;
					}
					if(sum<ans)ans=sum;
					for(int i=0;i<m;i++)v[i].second-=p*26;
				}
			}
			v[0].first+=26;//Change the first letter's direction to be changed into new letter
		}
		return ans==(1<<30)-1?-1:ans;
	}
};

