#include <bits/stdc++.h>

using namespace std;

const int maxn = 35;

typedef pair<int,int> pi;

vector<pi> ti[maxn],lk[maxn];

class History
{
public:
	void decode_time(vector<pi> &a,string b)
	{
		a.clear();
		vector<int> num;
		num.clear();
		bool exi = 0;int x = 0;
		for(auto p : b)
		{
			if (p >= '0' && p <= '9') exi = 1,x = x * 10 + p - 48; else
			{
				if (exi) num.push_back(x);
				exi = x = 0;
			}
		}
		if (exi) num.push_back(x);
		for(int i = 0;i < num.size() - 1;i ++)
			a.push_back(pi(num[i],num[i + 1]));
	}

	void clear()
	{
		memset(lk,0,sizeof lk);
	}

	void add_limit(string s)
	{
		int u = s[0] - 'A',u_d = s[1] - '0',v = s[3] - 'A',v_d = s[4] - '0';
		//(u,u_d)和(v,v_d)这两个王朝代表的线段要有交
		//!(d[u]+s >= d[v]+t1) && !(d[v]+s1>=d[u]+t)
		lk[v].push_back(pi(u,ti[v][v_d].second - ti[u][u_d].first - 1));
		lk[u].push_back(pi(v,ti[u][u_d].second - ti[v][v_d].first - 1));
	}

	bool update(int &a,int b)
	{
		if (b < a) return a = b,1;
		return 0;
	}

	bool legal(int s)
	{	
		//令d[i]表示i这个国家的时间线从d[i]开始，强制d[s]=0，假如有负环就不合法
		static bool in[maxn];
		static int d[maxn],ti[maxn],que[maxn * maxn];
		memset(d,60,sizeof d);
		memset(in,0,sizeof in);
		memset(ti,0,sizeof ti);
		d[s] = 0;
		in[s] = ti[s] = 1;
		que[1] = s;
		for(int fi = 1,en = 1;fi <= en;fi ++)
		{
			int u = que[fi];
			for(auto p : lk[u])
				if (update(d[p.first],d[u] + p.second) && !in[p.first])
				{
					in[p.first] = 1;
					++ ti[p.first];
					if (ti[p.first] > 30) return 0; //入队次数超过n次，存在负环
					que[++ en] = p.first;
				}
			in[u] = 0;
		}
		return 1;
	}	

	string verifyClaims(vector<string> dynasties,vector<string> battles,vector<string> queries)
	{
		for(int i = 0;i < dynasties.size();i ++)
			decode_time(ti[i],dynasties[i]);
		string out = "",bat = "";
		for(auto p : battles) bat = bat + p;
		for(auto p : queries)
		{
			clear();
			for(int i = 0;i < bat.length();i += 6) add_limit(bat.substr(i,5));
			add_limit(p);
			if (legal(p[0] - 'A')) out = out + 'Y'; else
				out = out + 'N';
		}
		return out;
	}
};
