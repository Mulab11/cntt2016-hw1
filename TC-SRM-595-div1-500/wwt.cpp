#include <bits/stdc++.h>

using namespace std;

const int maxn = 2505;

int Left[maxn],Right[maxn],Lg[maxn],Rg[maxn];

class LittleElephantAndRGB
{
public:
	long long getNumber(vector<string> list, int minGreen)
	{
		string s = "";
		for(auto p : list) s = s + p;
		//Lg[i]:以i为结尾连续有多少个G，Rg[i]:以i为开头向右连续有多少个G
		//Left[i]:最大的j，使得s[j..i]包含一段有连续minGreen个G的子串，Right[i]:最小的j，满足前面的性质
		for(int i = 0,co = 0,lp = -1;i < s.length();i ++)
		{
			if (s[i] == 'G') ++ co; else co = 0;
			if (co >= minGreen) lp = i - minGreen + 1;
			Lg[i] = co,Left[i] = lp;
		}
		for(int i = s.length() - 1,co = 0,lp = s.length();i >= 0;i --)
		{
			if (s[i] == 'G') ++ co; else co = 0;
			if (co >= minGreen) lp = i + minGreen - 1;
			Rg[i] = co,Right[i] = lp;
		}
		long long ans = 0;
		for(int b = 0;b < s.length();b ++)
			for(int c = b + 1;c < s.length();c ++)
			{	
				//part1
				//对于a,d中满足：a<=Left[b]或d>=Right[c]，这种方案都是合法的
				ans += (Left[b] + 1) * 1ll * (s.length() - c) + (s.length() - Right[c]) * 1ll * (b - Left[b]);
				//part2
				//考虑a在(Left[b],b],d在[c,Right[c])的情况
				//将a分为在(Left[b],b-Lg[b]]和(b-Lg[b],b]两种情况分别统计合法的d的个数
				//Lg[b]和Rg[c]都应该<minGreen，否则会重复计算
				int l = min(Lg[b],minGreen - 1),r = min(Rg[c],minGreen - 1),d = Right[c] - c;
				int ll = max(1,minGreen - r);
				//a in (b-Lg[b],b]
				if (ll <= l) ans += (l - ll + 1) * 1ll * (d - minGreen + 1) + (l + ll) * 1ll * (l - ll + 1) / 2;
				int r_need = minGreen - l;
				l = (b - Left[b] - l);
				//a in (Left[b],b-Lg[b]]
				if (r_need <= r) ans += l * 1ll * (d - r_need + 1);
			}
		return ans;
	}
};
