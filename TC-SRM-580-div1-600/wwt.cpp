#include <bits/stdc++.h>

using namespace std;

class ShoutterDiv1
{
public:
	void getval(vector<int> &val,vector<string> a,int coef)
	{
		int l = 0;
		for(auto i : a) for(auto j : i) val[l ++] += (j - 48) * coef;
	}

	void decode(vector<string> a,vector<string> b,vector<string> c,vector<string> d,vector<int> &val)
	{
		val.clear();
		int l = 0;
		for(auto i : a) for(auto j : i) ++ l;
		val.resize(l);
		getval(val,a,1000),getval(val,b,100),getval(val,c,10),getval(val,d,1);
	}

	int count(vector <string> s1000, vector <string> s100, vector <string> s10, 
		vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1) //disgusting
	{
		vector<int> s,t;
		decode(s1000,s100,s10,s1,s);
		decode(t1000,t100,t10,t1,t);
		int n = s.size();
		for(int i = 0;i < n;i ++) //sort according to (s[i],t[i])
			for(int j = i + 1;j < n;j ++)
				if (s[i] > s[j] || s[i] == s[j] && t[i] > t[j])
					swap(s[i],s[j]),swap(t[i],t[j]);
		int left_x = (1 << 30); //find the leftmost t[i]
		for(int i = 0;i < n;i ++) left_x = min(left_x,t[i]);
		int ans = 0;
		for(int i = 0;i < n;i ++) //every person's contribution is independent
		{
			int cover_left = left_x;//the point we need to cover
			for(int j = 0;j < n;)
			{
				if (s[i] <= cover_left) cover_left = max(cover_left,t[i]);//use i for free
				if (s[j] > cover_left) 
					return -1;//impossible to cover
				int next_left = cover_left;
				for(;j < n && s[j] <= cover_left;j ++) next_left = max(next_left,t[j]); //choose a rightmost interval to cover it
				cover_left = next_left;
				if (j != n) ++ ans; //the final interval has no need to transcribe it.
			}
		}
		return ans;
	}
};
