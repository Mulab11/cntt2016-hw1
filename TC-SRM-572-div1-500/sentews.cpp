#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
	char tt[33][33]={};
	struct ff{int m,cnt;}f[111]={};
	string a[111]={};
	int b[111]={};
	int n;int maxx=0;
	int c[111]={};
	int sum=0;
	string t;
	string ans;
	bool err=0,err2=0;
	bool cmpp(ff m,ff n){return m.cnt>n.cnt;}
	void update()
	{
		for(int i=0;i<a[0].size();i++)
		{
			for(int j=0;j<100;j++)
				f[j].m=f[j].cnt=0;
			for(int j=0;j<n;j++)
				f[a[j][i]-'0'].cnt++;
			for(int j=0;j<=9;j++)
				f[j].m=j+'0';
			sort(f,f+10,cmpp);
			for(int j=0;j<=9;j++)
				tt[i][j]=f[j].m;
		}
	}
	void check(int s)
	{
		for(int i=0;i<n;i++)
			c[i]=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<s;j++)
				if(t[j]==a[i][j])
					c[i]++;
		int tem=a[0].size()-s;
		for(int i=0;i<n;i++)
			if(c[i]>b[i]||b[i]-c[i]>tem)
				err=1;
		if(tem==0&&!err)
		{
				if(sum==1)
					err2=1;
				else
					ans=t,sum=1;
		}
		
	}
	void dfs(int s)
	{
		if(s==a[0].size())
			return;
		for(char i=0;i<=9;i++)
		{
			t[s]=tt[s][i];
			check(s+1);
			if(err2)//存在多个字符串满足条件
				return;
			if(err)//当前字符确定后，后面的字符无论如何都不会满足条件
			{err=0;
			continue;
			}
			else
				dfs(s+1);
		}
	}
class EllysBulls
{
	public:
	string getNumber(vector <string> guesses,vector <int> bulls)
	{
		n=guesses.size();
		printf("%d\n",n);
		for(int i=0;i<n;i++)
			b[i]=bulls[i],a[i]=guesses[i];
		t=a[0];
		update();
		dfs(0);
		if(n==1&&bulls[0]==0)
			return "Ambiguity";
		if(err2)
		return "Ambiguity";
		else if(sum==0)
		return "Liar";
		else
		return ans;
	}
};
