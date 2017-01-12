#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pi;

map<pi,int> sav[1005];

class TheNumberGame
{
public:
	int rev(int v)
	{
		int bv = 0;
		for(;v;v /= 10) bv = bv * 10 + v % 10;
		return bv;
	}

	int dfs(int turn,int a,int b) //记忆化搜索
	{
		if (sav[turn].find(pi(a,b)) != sav[turn].end()) return sav[turn][pi(a,b)];
		if (a == b) return 1;
		if (turn == 1000) return 0;
		if (!(turn & 1))
		{
			if (dfs(turn + 1,a / 10,b) || dfs(turn + 1,rev(a),b)) return sav[turn][pi(a,b)] = 1;
			return sav[turn][pi(a,b)] = 0;
		}
		if (!dfs(turn + 1,a,b / 10) || !dfs(turn + 1,a,rev(b))) return sav[turn][pi(a,b)] = 0;
		return sav[turn][pi(a,b)] = 1;
	}

	string determineOutcome(int A, int B)
	{
		return dfs(0,A,B) ? "Manao wins" : "Manao loses";
	}
};
