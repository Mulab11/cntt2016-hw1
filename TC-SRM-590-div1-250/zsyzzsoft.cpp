#include <algorithm>
using namespace std;
class FoxAndChess
{
public:
	string ableToMove(string s, string t)
	{
		string ps, pt;
		vector<int> xs, xt;
		for(int i = 0; i < s.length(); i++)
		{
			if(s[i] != '.')
				ps += s[i], xs.push_back(i);
		}
		for(int i = 0; i < t.length(); i++)
		{
			if(t[i] != '.')
				pt += t[i], xt.push_back(i);
		}
		if(ps != pt) //去掉空位后的串必须完全相同 
			return "Impossible";
		for(int i = 0; i < ps.size(); i++)
		{
			if(ps[i] == 'L') //位置关系要与左右相符 
			{
				if(xs[i] < xt[i])
					return "Impossible";
			}
			else
			{
				if(xs[i] > xt[i])
					return "Impossible";
			}
		}
		return "Possible";
	}
};