#include <bits/stdc++.h>
#define fe first
#define se second
#define pb(x) push_back((x))

using namespace std;

const int mo = int(1e9) + 9;

typedef vector<int> vi;
typedef pair<int,int> pi;
typedef vector<pi> vpi;

class UnknownTree
{
public:
	int one_point_work(vi dA)
	{
		dA.pb(0);
		sort(dA.begin(),dA.end());
		if (dA[0] < 0) return 0;
		int ans = 1;
		for(auto p = dA.begin() + 1;p != dA.end();p ++)
			ans = (ans * 1ll * (lower_bound(dA.begin(),dA.end(),*p) - dA.begin())) % mo;
		return ans;
	}

	int two_point_work(int fixed,vpi d)
	{
		if (!d.size()) return 1;
		int n = d.size();
		vi dA,dB;
		for(auto p = d.begin();p != d.end();p ++) dA.pb(p->fe),dB.pb(p->se);
		//A as a direct son to B
		vi bel_A,bel_B;
		int l_ab = fabs(dA[0] - dB[0]);
		if (fixed != -1 && l_ab != fixed) l_ab = 0;
		for(int i = 1;i < n;i ++)
			if (fabs(dA[i] - dB[i]) != l_ab) {l_ab = 0;break;}
		if (l_ab)
		{
			for(int i = 0;i < n;i ++)
				if (dA[i] < dB[i]) bel_A.pb(dA[i]); else bel_B.pb(dB[i]);
			return one_point_work(bel_A) * 1ll * one_point_work(bel_B) % mo;
		}
		//there is a point between A and B
		l_ab = (1 << 30);
		for(int i = 0;i < n;i ++) l_ab = min(l_ab,dA[i] + dB[i]);
		if (!l_ab || (fixed != -1 && l_ab != fixed)) return 0;
		vpi sub_A;
		int mpos = -1;
		for(int i = 0;i < n;i ++)
			if (dA[i] + dB[i] == l_ab && (mpos == -1 || dB[i] < dB[mpos])) mpos = i;
		for(int i = 0;i < n;i ++)
			if (i == mpos) continue; else
			if (dB[i] + l_ab == dA[i]) bel_B.pb(dB[i]); else
				if (dA[i] + dB[i] < l_ab) return 0; else sub_A.pb(pi(dA[i],dB[i] - dB[mpos]));
		return one_point_work(bel_B) * 1ll * two_point_work(dA[mpos],sub_A) % mo;
	}

	int as_a_center(int mid,vi dA,vi dB,vi dC)
	{
		vpi b_a,b_b,b_c;
		vi b_0;
		for(int i = 0;i < dA.size();i ++)
			if (i != mid)
			{
				int ta = dA[i] - dA[mid],tb = dB[i] - dB[mid],tc = dC[i] - dC[mid];
				if (ta == tb && ta == tc && ta > 0) b_0.pb(ta); else
					if (ta == tb && ta > 0) b_c.pb(pi(ta,dC[i])); else
						if (ta == tc && ta > 0) b_b.pb(pi(ta,dB[i])); else
							if (tb == tc && tb > 0) b_a.pb(pi(tb,dA[i])); else
								return 0;
			}
		int ans = two_point_work(dA[mid],b_a);
		ans = (ans * 1ll * two_point_work(dB[mid],b_b)) % mo;
		ans = (ans * 1ll * two_point_work(dC[mid],b_c)) % mo;
		ans = (ans * 1ll * one_point_work(b_0)) % mo;
		return ans;
	}

	int middle_work(vi dA,vi dB,vi dC)
	{
		int n = dA.size();
		vpi ava;
		for(int i = 0;i < n;i ++)
		{
			//let j outside A and B
			int t_a = dA[i] - dC[i],t_b = dB[i] - dC[i];
			if (t_a > 0 && t_b > 0) ava.pb(pi(t_a,t_b));
			//let j inside sub_A
				//b_c is fixed,a_c has two conditions.
			int a_c = dA[i] + dC[i];
			if (t_b > 0) ava.pb(pi(a_c,t_b));
			a_c = dC[i] - dA[i];
			if (t_b > 0 && a_c > 0) ava.pb(pi(a_c,t_b));
			//the same to B
			int b_c = dB[i] + dC[i];
			if (t_a > 0) ava.pb(pi(t_a,b_c));
			b_c = dC[i] - dB[i];
			if (t_a > 0 && b_c > 0) ava.pb(pi(t_a,b_c));
		}
		sort(ava.begin(),ava.end());
		ava.resize(unique(ava.begin(),ava.end()) - ava.begin());
		int ans = 0;
		for(auto p : ava)
		{
			vpi b_a,b_b;
			vi b_0;
			b_a.clear(),b_b.clear(),b_0.clear();
			bool ok = 1;
			for(int i = 0;i < n;i ++)
			{
				int t_a = dC[i] + p.fe,t_b = dC[i] + p.se;
				if (t_a == dA[i] && t_b == dB[i])
					b_0.pb(dC[i]); else
						if (t_a == dA[i]) b_b.pb(pi(dB[i],dC[i])); else
							if (t_b == dB[i]) b_a.pb(pi(dA[i],dC[i])); else
								{ok = 0;break;}
			}
			if (!ok) continue;
			int cur = two_point_work(p.fe,b_a) * 1ll * two_point_work(p.se,b_b) % mo * one_point_work(b_0) % mo;
			ans = (ans + cur) % mo;
		}
		return ans;
	}

	int getCount(vi dA,vi dB,vi dC)
	{
		int ans = 0;
		for(int i = 0;i < dA.size();i ++)
			ans = (ans + as_a_center(i,dA,dB,dC)) % mo; //i在中间，分四叉
		ans = (ans + middle_work(dA,dB,dC)) % mo; //A-C-B
		ans = (ans + middle_work(dA,dC,dB)) % mo; //A-B-C
		ans = (ans + middle_work(dB,dC,dA)) % mo; //B-A-C
		return ans;
	}
};
