#include <bits/stdc++.h>
using namespace std;

class FoxAndMountainEasy
{
public:
	string possible(int n, int a1, int an, string cat)
	{
		if((n + a1 - an) % 2) return "NO";
		int pos = a1, min_pos = a1;
		for(int i = 0; i != (int) cat.size(); ++i)
		{
			cat[i] == 'U' ? ++pos : --pos;
			if(pos < min_pos) min_pos = pos;
		}
		n -= cat.size();
		while(min_pos < 0)
		{
			if(!n--) return "NO";
			++min_pos, ++pos;
		}
		return (pos - an > n || an - pos > n) ? "NO" : "YES";
	}
}	user;
