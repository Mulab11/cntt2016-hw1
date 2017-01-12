#include <bits/stdc++.h>

using namespace std;

class EllysBulls
{
public:
	vector<string> g;
	vector<int> b;
	int ans;
	string bak;
	map<string,int> cou;//the number of s_1 which for every bull its number of matching positions is equal to cou->first[i]
	map<string,string> sav; //any satified s_1

	void work(int ty,int start_pos,string cr)
	{
		string cur = ""; // to save the number of matching positions of every bull 
		for(int i = 0;i < b.size();i ++)
		{
			int c = 0;
			for(int j = start_pos;j < start_pos + cr.length();j ++)
				if (g[i][j] == cr[j - start_pos]) ++ c;
			if (c > b[i]) return;	
			cur = cur + char('0' + ((ty) ? (b[i] - c) : c)); //for s_2,we consider what s_1 should be
		}
		if (!ty) cou[cur] ++,sav[cur] = cr; else
		{
			if (cou[cur]) ans += cou[cur],bak = sav[cur] + cr;
		}
	}

	void dfs(int type,int start_pos,int now,int len,string cur)
	{
		if (now == len) work(type,start_pos,cur); else
		{
			for(char c = '0';c <= '9';c ++)
				dfs(type,start_pos,now + 1,len,cur + c);
		}
	}

	string getNumber(vector <string> guesses, vector <int> bulls)
	{
		g = guesses,b = bulls;
		sav.clear();
		int n = bulls.size(),l = guesses[0].length();
		//we split the answer string into two parts:answer = s_1 + s_2
		dfs(0,0,0,l / 2,"");//find s_1
		dfs(1,l / 2,0,l - l / 2,""); //find s_2
		if (ans > 1) return "Ambiguity"; else
			if (ans == 1) return bak; else
				return "Liar";
	}
};
