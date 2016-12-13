#include <algorithm>
using namespace std;
class UndoHistory
{
public:
	int Common(string a, string b) //最长公共前缀 
	{
		for(int i = 0; ; i++)
		{
			if(i >= a.length() || i >= b.length() || a[i] != b[i])
				return i;
		}
		return -1;
	}
	int minPresses(vector<string> lines)
	{
		int ans = lines[0].length();
		for(int i = 1; i < lines.size(); i++)
		{
			int x = Common(lines[i - 1], lines[i]) == lines[i - 1].length() ? lines[i - 1].length() + 2 : 0; //不撤销 
			for(int j = 0; j < i; j++)
				x = max(x, Common(lines[j], lines[i])); //撤销到某一前缀 
			ans += lines[i].length() - x + 2;
		}
		return ans + lines.size();
	}
};