#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class StringGame
{
	public:
	int cnt[55][26];
	bool alive[55],used[26];
	
	bool work(int n)//Check if string 0 can win at last.
	{
		memset(alive,1,n+1);//alive[i] means if string i haven't been killed(can win).
		memset(used,0,26);
		for(int t=26;t--;)
		{
			int k=-1;
			//find a letter string 0 can beat someone else with.
			for(int j=0,flag;j<26&&k==-1;j++)
				if(!used[j])
				{
					flag=1;
					for(int i=1;i<=n&&flag;i++)
						if(alive[i]&&cnt[i][j]>cnt[0][j])flag=0;
					if(flag)k=j;
				}
			if(k==-1)return 0;//can't find such a letter.
			used[k]=1;
			//kill the strings that contains fewer "k"s than string 0.
			for(int i=1;i<=n;i++)
				if(cnt[i][k]<cnt[0][k])alive[i]=0;
		}
		//If any other string remains alive, string 0 can't win.
		for(int i=1;i<=n;i++)
			if(alive[i])return 0;
		return 1;
	}
	
	vector<int> getWinningStrings(vector<string> S)
	{
		vector<int> ans;
		int n=S.size(),m=S[0].size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				cnt[i][S[i][j]-'a']++;
		for(int i=0;i<S.size();i++)//pick each string and check if it can win.
		{
			for(int j=0;j<26;j++)
				swap(cnt[i][j],cnt[0][j]);
			if(work(n-1))ans.push_back(i);
			for(int j=0;j<26;j++)
				swap(cnt[i][j],cnt[0][j]);
		}
		return ans;
	}
};

