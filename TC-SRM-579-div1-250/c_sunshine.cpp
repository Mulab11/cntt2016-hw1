#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int inf=1000;

class UndoHistory
{
	public:
	vector<string> his;
	string now;
	
	int pre(string a,string b)//Check if a is a prefix of b
	{
		if(a.size()>b.size())return -inf;
		for(int i=0;i<a.size();i++)
			if(a[i]!=b[i])return -inf;
		return a.size();
	}
	
	int minPresses(vector<string> lines)
	{
		int ans=0;
		his.push_back(now);
		for(int i=0;i<lines.size();i++)
		{
			int c=lines[i].size()-pre(now,lines[i])+1,k=-1;
			for(int j=0;j<his.size();j++)//Find the best entry to restore.
				if(lines[i].size()-pre(his[j],lines[i])+3<c)
				{
					c=lines[i].size()-pre(his[j],lines[i])+3;
					k=j;
				}
			if(k!=-1)now=his[k];
			while(now!=lines[i])//Type required letters.
			{
				now+=lines[i][now.size()];
				his.push_back(now);
			}
			ans+=c;
		}
		return ans;
	}
};

