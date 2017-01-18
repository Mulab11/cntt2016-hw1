#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector> 
#define N 100010
using namespace std;
struct LittleElephantAndBalls
{
	int getNumber(string S)
	{
		int n=S.size();
		int tb=0,tg=0,tr=0;
		int i,ans=0;
		for(i=0;i<n;i++)
		{
			ans+=min(tb,2)+min(tg,2)+min(tr,2);
			if(S[i]=='R') tr++;
			else if(S[i]=='B') tb++;
			else tg++;
		}
		return ans;
	}
};