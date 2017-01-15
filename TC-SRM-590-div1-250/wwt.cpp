#include <bits/stdc++.h>

using namespace std;

class FoxAndChess
{
public:
	string ableToMove(string begin, string target)
	{
		vector<int> lis;
		lis.clear();
		for(int i = 0;i < begin.size();i ++)
			if (begin[i] != '.') lis.push_back(i);
		int fr = 0;
		//one should notice that the relative positions of the pawns won't change,so it is sufficient to check whether each of them matches another one.
		for(int i = 0;i < target.size();i ++)
			if (target[i] != '.')
			{
				if (fr == lis.size() || target[i] != begin[lis[fr]]) return "Impossible";
				if (i > lis[fr] && begin[lis[fr]] == 'L' || i < lis[fr] && begin[lis[fr]] == 'R') return "Impossible";
				++ fr;
			}
		if (fr != lis.size()) return "Impossible"; //pawns must all appear
		return "Possible";
	}
};
