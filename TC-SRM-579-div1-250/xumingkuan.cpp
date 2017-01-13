#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;

class UndoHistory
{
private:
	vector<string> history;
	string buffer;
	int maxmatch(const string &s)
	{
		for(int i = s.size(); i >= 0; i--)//brute force
			for(int j = 0; j < history.size(); j++)
				if(history[j] == s.substr(0, i))
					return i;
		return printf("error\n");
	}
public:
	int minPresses(vector<string> lines)
	{
		int ans = 0;
		history.assign(1, buffer = string());//empty string
		for(int i = 0; i < lines.size(); i++, ans++)//press Enter
		{
			int j = maxmatch(lines[i]);
			if(j >= buffer.size() + 2 || lines[i].size() < buffer.size() || lines[i].substr(0, buffer.size()) != buffer)//2 mouse clicks
				ans += 2;
			else if(j == buffer.size() + 1)
				j--;//type the single letter instead of clicking mouse twice
			buffer = lines[i].substr(0, j);
			for(; j < lines[i].size(); j++, ans++)//type the letter
				history.push_back(buffer += lines[i][j]);
		}
		return ans;
	}
};

