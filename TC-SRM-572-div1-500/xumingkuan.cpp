#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
const int Ambiguity = -1, Liar = -2;
class EllysBulls
{
private:
	int num, k;
	int a[60], b[60];//a: guessed numbers; b: bulls
	int p10[12];//p10[i] = 10^i
	int ok[12];//ok[p] has digit (1<<i) if position p can be i
	int ans;
	map<string, int> mp;
	bool checkvalid(int now, int p)
	{
		for(int j = p; j < k; j++)
			ok[j] = (1 << 10) - 1;
		string str(1, p);
		for(int tim = 1; tim <= 2; tim++)//do it twice
			for(int i = 0; i < num; i++)
			{
				int tmp = 0;
				for(int j = 0; j < p; j++)
					tmp += (now / p10[j] % 10 == a[i] / p10[j] % 10);
				if(tim == 1)
					str += tmp;
				if(tmp > b[i] || tmp + k - p < b[i])
					return false;
				if(tmp == b[i])//positions p~k of answer are different from a[i]
				{
					if(tim == 1)
						for(int j = p; j < k; j++)
							ok[j] = ~(~ok[j] | (1 << (a[i] / p10[j] % 10)));
					continue;
				}
				for(int j = p; j < k; j++)//get the max number of matching digits
					if(ok[j] & (1 << (a[i] / p10[j] % 10)))
						tmp++;
				if(tmp < b[i])//still not enough
					return false;
				if(tmp == b[i])//must choose some digits
					for(int j = p; j < k; j++)
						if(ok[j] & (1 << (a[i] / p10[j] % 10)))
							ok[j] = (1 << (a[i] / p10[j] % 10));
			}
		for(int j = p; j < k; j++)
			if(!ok[j])//can't choose any number at position j
				return false;
		if(mp.find(str) == mp.end())
			mp[str] = 1;
		else if(mp[str] == 1)
			mp[str] = 2;
		else
			return false;//memorization: the same status can only be searched twice.
		return true;
	}
	void search(int now, int p)//number now, position p
	{
		if(p == k)
		{
			if(ans == Liar)
				ans = now;
			else
				ans = Ambiguity;
			return;
		}
		for(int i = 0; i <= 9; i++)
			if((ok[p] & (1 << i)) && checkvalid(now + p10[p] * i, p + 1))//choose i at position p
			{
				search(now + p10[p] * i, p + 1);
				if(ans == Ambiguity)
					return;
			}
	}
public:
	string getNumber(vector<string> guesses, vector<int> bulls)
	{
		num = guesses.size();
		k = guesses[0].size();
		for(int i = 0; i < num; i++)
		{
			a[i] = 0;
			for(int j = 0; j < k; j++)
				a[i] = a[i] * 10 + guesses[i][j] - '0';
			b[i] = bulls[i];
		}
		p10[0] = 1;
		for(int i = 1; i <= k; i++)
			p10[i] = p10[i - 1] * 10;
		ans = Liar;
		ok[0] = (1 << 10) - 1;
		mp.clear();
		search(0, 0);
		if(ans == Liar)
			return "Liar";
		if(ans == Ambiguity)
			return "Ambiguity";
		string ret;
		for(int i = k - 1; i >= 0; i--)
			ret += ans / p10[i] % 10 + '0';
		return ret;
	}
};

