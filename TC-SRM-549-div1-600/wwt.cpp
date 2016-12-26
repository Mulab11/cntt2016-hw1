/*
只有13个帽子。设状态sta，若sta[i]=0，表示还没开，sta[i]=1表示开了，有硬币，
sta[i]=2表示开了，没有硬币，记忆化搜索,f[sta] = max(min(f[sta'],f[sta'']))
*/
#include <bits/stdc++.h>

using namespace std;

class MagicalHats
{
public:
	int rc[13],cc[13];
	int n,m,pw[13],pos[13][2],f[1594325],cnt,coin_cnt,all;

	//define 0->unvealed 1-> revealed with coin 2->revealed without coin
	int dfs(int cur,int coi,int sta)
	{ 
		if (coi > coin_cnt) return (1 << 30);
		if (~f[sta]) return f[sta];
		if (cur > cnt) 
		{
			if (coi != coin_cnt) return (1 << 30);
			for(int i = 0;i < n;i ++)
				if (rc[i] & 1) return (1 << 30);
			for(int i = 0;i < m;i ++)
				if (cc[i] & 1) return (1 << 30);
			return 0;
		}
		f[sta] = 0;
		for(int i = 0,nsta = sta;i < cnt;i ++,nsta /= 3) 
			if (!(nsta % 3))
			{
				int ret_1 = dfs(cur + 1,coi,sta + 2 * pw[i]); //不放硬币
				rc[pos[i][0]] ++,cc[pos[i][1]] ++;
				int ret_2 = dfs(cur + 1,coi + 1,sta + pw[i]) + (cur <= all); //放了硬币
				rc[pos[i][0]] --,cc[pos[i][1]] --;
				if (cur > all)
				{
					f[sta] = min(ret_1,ret_2);
					break;
				}
				f[sta] = max(f[sta],min(ret_1,ret_2));
			}
		return f[sta];
	}

	int findMaximumReward(vector<string> board,vector<int> coins,int numGuesses)
	{
		n = board.size(),m = board[0].length();
		coin_cnt = coins.size();
		pw[0] = 1;
		for(int i = 1;i < 13;i ++) pw[i] = pw[i - 1] * 3;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (board[i][j] == 'H') pos[cnt ++][0] = i,pos[cnt - 1][1] = j,rc[i] ++,cc[j] ++;
		memset(f,255,sizeof f);
		all = numGuesses;
		int v = dfs(1,0,0);
		if (v > cnt) return -1;
		int ans = 0;
		sort(coins.begin(),coins.end()); //只能选前v小
		for(int i = 0;i < v;i ++) ans += coins[i];
		return ans;
	}
};
