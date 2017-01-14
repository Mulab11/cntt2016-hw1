#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class NewArenaPassword
{
	public:
	string s;
	int c[26],K,d;
	int v[55];
	
	void dfs(int p)//Get an equivalence class
	{
		v[p]=1;
		c[s[p]-'a']++;
		if(p<K&&!v[p+d])dfs(p+d);
		if(p>=s.size()-K&&!v[p-d])dfs(p-d);
	}
	
	int minChange(string oldPassword,int K)
	{
		s=oldPassword;
		this->K=K;
		d=s.size()-K;
		int ans=0;
		//Use Depth First Search to get all equivalence classes.
		for(int i=0;i<s.size();i++)
			if(!v[i])
			{
				memset(c,0,sizeof(c));
				dfs(i);
				int sm=0,mx=0;
				for(int j=0;j<26;j++)
					sm+=c[j],mx=max(mx,c[j]);
				ans+=sm-mx;//For each equivalence class we keep the most seen letter and change other letters.
			}
		return ans;
	}
};

