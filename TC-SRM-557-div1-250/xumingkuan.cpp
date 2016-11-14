#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
class FoxAndMountainEasy
{
	public:
	string possible(int n, int h0, int hn, string history)
	{
		if((n + hn - h0) % 2 != 0)//ji ou xing bu dui
			return "NO";
		if(abs(h0 - hn) > n)
			return "NO";
		const int up = (n + hn - h0) / 2, down = (n - hn + h0) / 2;
		int numu = 0, numd = 0, low = 0, now = 0;
		for(int i = 0; i < history.size(); i++)//simulate history
			if(history[i] == 'U')
				numu++, now++;
			else
				numd++, low = min(low, --now);
		if(numu + max(0, -low - h0) > up || numd > down)//There must be at least (-low - h0) 'U' before "history", otherwise there would be some h[i] < 0
			return "NO";
		return "YES";
	}
};

