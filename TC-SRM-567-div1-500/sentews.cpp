#include<cstdio>
#include<algorithm>
#include<vector>
#include<iostream>
#include<string>
using namespace std;
char f[111][111]={};
int n,m;bool flag;
int cnt[111][111]={};bool rrr;
vector<int>ans;int ttt=0;
void getttt()
{
	for(int i=0;i<26;i++)
		for(int j=0;j<n-1;j++)
			if(cnt[j][i]!=cnt[j+1][i])
			{ttt^=(1<<i);break;}
}
void dfs(int pos,int state,long long state2)
{
	if(flag)return;
	if(state2==0){//其余所有字母都被击败
		flag=1;return;}
	bool uuu=0;
	for(int i=0;i<26;i++)//枚举26字母
		if(state&(1<<i)&&!flag)//当前字母还没有被使用
		{
			bool temp=1;
			long long state3=state2;
			for(int j=0;j<n;j++)//枚举n个字符串
				if(state2&(1LL<<j))
					if(cnt[j][i]>cnt[pos][i])//当前字母数量不是最长就不成立
						{temp=0;break;}
					else if(cnt[j][i]<cnt[pos][i])
						state3^=(1LL<<j);
			if(temp)uuu=1;
			if(temp&&state2!=state3)
				dfs(pos,state^(1<<i),state3);
		}
	if(!uuu)rrr=0;
}

class StringGame
{
public:
	vector <int> getWinningStrings(vector <string> S)
	{
		n=S.size();m=S[0].size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				f[i][j]=S[i][j];
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				cnt[i][f[i][j]-'a']++;
		getttt();
		for(int i=0;i<n;i++)
		{
			flag=0;rrr=1;
			dfs(i,ttt,((1LL<<n)-1)^(1LL<<i));
			if(flag)
			ans.push_back(i);
		}
		return ans;
	}
};
/*
int main()
{
	freopen("1","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>f[i][j];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cnt[i][f[i][j]-'a']++;
	getttt();
	for(int i=0;i<n;i++)
	{
		flag=0;
		dfs(i,ttt,((1LL<<n)-1)^(1LL<<i));
		if(flag)
		cout<<i<<endl;
	}
	return 0;
}*/
