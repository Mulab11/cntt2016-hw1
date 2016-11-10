class AlternateColors2
{
public:
	long long countWays(int n, int k)
	{
		long long ret = 0;
		int m3 = (k + 2) / 3 * 3;
		// k 恰好是某一完整的轮的开始，后面是任意的
		if(k % 3 == 1 && m3 <= n)
			ret += (long long) (n - m3 + 2) * (n - m3 + 1) / 2;
		// 枚举三种颜色的的轮数
		for(int c3 = 0; c3 * 3 < k; ++c3)
		{
			// 第一种，经过了 c3 轮三种颜色，之后只有红色了
			++ret;
			// 第二种，经过了 c3 轮三种颜色，还有若干轮是两种颜色，然后就只有红色了
			ret += (k - 1 - c3 * 3) / 2 * 2;
			// 第三种，经过了 c3 轮三种颜色，k 是在某个两种颜色的轮中
			if((k - c3 * 3) % 2 == 1)
				ret += 2ll * (n - c3 * 3 - (k - c3 * 3 + 1) / 2 * 2 + 1);
		}
		return ret;
	}
}	user;
