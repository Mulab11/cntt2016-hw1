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

using namespace std;
const int ALPHA = 26, MAXN = 60;
class Str
{
	public:
	int v[ALPHA];
	void init(const string &s)//count letters
	{
		memset(v, 0, sizeof(v));
		const int len = s.size();
		for(int i = 0; i < len; i++)
			v[s[i] - 'a']++;
	}
};
class StringGame
{
	private:
	int n;
    Str s[MAXN];
    bool used[ALPHA];
    bool alive[MAXN];
    bool winstr(int x)//check if string X will win
    {
    	memset(used, false, sizeof(used));
    	memset(alive, true, sizeof(alive));
    	alive[x] = false;
    	while(1)
    	{
    		for(int ch = 0; ch <= ALPHA; ch++)//try letter ch
    		{
    			if(ch == ALPHA)//no available letters
    				return false;
    			if(used[ch])
    				continue;
    			bool flag = true;
    			for(int j = 0; j < n; j++)
    				if(alive[j] && s[j].v[ch] > s[x].v[ch])//ch would kill string X
    				{
    					flag = false;
    					break;
    				}
    			if(flag)//choose letter ch
    			{
    				used[ch] = true;
    				for(int j = 0; j < n; j++)
    					if(alive[j] && s[j].v[ch] < s[x].v[ch])//kill string j
    						alive[j] = false;
    				break;
    			}
    		}
    		bool flag = true;
	    	for(int i = 0; i < n; i++)
	    		if(alive[i])
	    			flag = false;
    		if(flag)//only string X on stage
    			return true;
    	}
    	return true;
    }
    public:
    vector<int> getWinningStrings(vector<string> S)
	{
		n = S.size();
		for(int i = 0; i < n; i++)
			s[i].init(S[i]);
		vector <int> ret;
		for(int i = 0; i < n; i++)
			if(winstr(i))
				ret.push_back(i);
        return ret;
    }
};
