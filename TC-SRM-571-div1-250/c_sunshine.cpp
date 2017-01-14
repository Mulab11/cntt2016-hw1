#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
class FoxAndMp3
{
	public:
	vector<string> ans;
	
	LL to_num(string &s)//change string s into number.
	{
		LL t=0;
		for(int i=0;i<s.size();i++)
			t=t*10+s[i]-'0';
		return t; 
	}
	
	void dfs(string s,int n)//Use Depth First Search to get names by lexicographical order
	{
		if(to_num(s)>n)return;//the number must be less or equal to n.
		if(ans.size()==n||ans.size()==50)return;
		if(s!="")//Insert the current string to the answer
			ans.push_back(s+".mp3");
		for(char i='0'+(!s.size());i<='9';i++)
			dfs(s+i,n);
	}
	
	vector<string> playList(int n)
	{
		dfs("",n);
		return ans;
	}
};

