#include <bits/stdc++.h>

using namespace std;

const int maxn = 30;
const double PI = acos(-1);

typedef complex<double> z;

class SplittingFoxes2
{
public:
	z w[maxn];
	int n;

	vector<z> dft(vector<z> a) //暴力dft即可
	{
		vector<z> tmp;
		tmp.clear();
		for(int i = 0;i < n;i ++)
		{
			z cur = z(0,0);
			for(int j = 0;j < n;j ++)
				cur += a[j] * w[(i * j) % n];
			tmp.push_back(cur);
		}
		return tmp;
	}

	bool legal(vector<int> a,vector<int> b)
	{
		for(int i = 1;i < n;i ++)
			if (a[i] != a[n - i]) return 0; //要首先满足对称性质
		for(int i = 0;i < n;i ++)
		{
			long long s = b[i];
			for(int j = 0;j < n;j ++) s -= a[j] * 1ll * a[(i - j + n) % n]; //a^2是否等于b
			if (s) return 0;
		}
		return 1;
	}

	vector<int> getPattern(vector <int> amount)
	{
		n = amount.size();
		w[0] = z(1,0),w[1] = z(cos(2 * PI / n),sin(2 * PI / n)); //单位根
		for(int i = 2;i <= n;i ++) w[i] = w[i - 1] * w[1];
		vector<z> a;
		a.clear();
		for(int i = 0;i < n;i ++) a.push_back(z(amount[i],0));
		a = dft(a);
		for(int i = 0;i < n;i ++)a[i] = sqrt(a[i]); //a=p^2,dft(a)=dft(p)^2,idft(sqrt(dft(a)))=p
		for(int i = 0;i <= n;i ++) w[i].imag(-w[i].imag()); //插值时代入w_{-i}
		vector<int> ans;
		ans.clear();
		for(int i = 0;i < (1 << ((n + 1) / 2 + 1));i ++) //sqrt有两种取值，因为题目保证对称，所以只需要枚举半边的取值
		{
			vector<z> bak = a;
			for(int j = 0;j < n;j ++)
				if (i & (1 << min(j,n - j))) bak[j] *= -1;
			bak = dft(bak);
			vector<int> cur;
			cur.clear();
			for(int j = 0;j < n;j ++)
				cur.push_back(int(bak[j].real() / n + 0.5));
			if (legal(cur,amount) && (ans.empty() || cur < ans)) ans = cur;
		}
		if (ans.empty()) ans.push_back(-1);
		return ans;
	}
};
