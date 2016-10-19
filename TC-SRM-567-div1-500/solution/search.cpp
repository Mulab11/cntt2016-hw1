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
//Author: xumingkuan
//Challenge succeeded by myself...
using namespace std;
const int ALPHA = 26, MAXN = 60;
class Str
{
	public:
	int v[ALPHA];
	void init(const string &s)
	{
		memset(v, 0, sizeof(v));
		const int len = s.size();
		for(int i = 0; i < len; i++)
			v[s[i] - 'a']++;
	}
	bool operator ==(const Str &b) const
	{
		for(int i = 0; i < ALPHA; i++)
			if(v[i] != b.v[i])
				return false;
		return true;
	}
};
class StringGame
{
	private:
	int n;
    Str s[MAXN];
    bool used[ALPHA];
    bool search(int x, vector <int> str)
    {
    	if(str.empty())
    		return true;
    	for(int ch = 0; ch < ALPHA; ch++)
    	{
    		if(used[ch] || !s[x].v[ch])
    			continue;
    		bool flag = true, flag2 = false;//flag2 == false: all strings have same ch, so choosing ch is useless
    		vector <int> tmp;
    		for(vector <int> :: iterator st = str.begin(); st != str.end(); st++)
    			if(s[*st].v[ch] > s[x].v[ch])
    			{
    				flag = false;//lose if choose ch
    				break;
    			}
    			else if(s[*st].v[ch] == s[x].v[ch])
    				tmp.push_back(*st);
    			else
    				flag2 = true;
    		if(flag && flag2)
    		{
    			used[ch] = true;
    			if(search(x, tmp))
    				return true;
    			used[ch] = false;
    		}
    	}
    	return false;
    }
    bool winstr(int x)
    {
    	memset(used, false, sizeof(used));
    	vector <int> tmp;
    	for(int i = 0; i < n; i++)
    		if(i != x)
    		{
				if(s[i] == s[x])
    				return false;
    			tmp.push_back(i);
    		}
    	return search(x, tmp);
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

