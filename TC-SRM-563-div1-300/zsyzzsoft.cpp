#include <algorithm>
using namespace std;
class FoxAndHandle
{
public:
	string lexSmallestName(string str)
	{
		int n = str.length(), s[50], cnt[51][26] = {0}, chosen[26] = {0};
		for(int i = 0; i < n; i++)
			s[i] = str[i] - 'a';
		for(int i = 0; i < n; i++) 
		{
			for(int j = 0; j < 26; j++)
				cnt[i + 1][j] = cnt[i][j];
			cnt[i + 1][s[i]]++;
		}
		string ans;
		for(int i = 0, j = 0, k; i < n / 2; i++) //依次考虑每一位 
		{
			for(int i = 0; i < 26; i++) //枚举当前位的最小字符 
			{
				if(chosen[i] >= cnt[n][i] / 2)
					continue;
				for(k = j; k < n && s[k] != i; k++);
				bool flag = true;
				for(int c = 0; c < 26 && flag; c++)
					flag &= cnt[k][c] - chosen[c] <= cnt[n][c] / 2;
				if(!flag)
					continue;
				chosen[i]++;
				ans += i + 'a';
				j = k + 1;
				break;
			}
		}
		return ans;
	}
};
