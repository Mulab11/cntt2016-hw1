#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;
typedef long long ll;
const int maxn = 1e5+1e2;
const int modu = 1e9+7;

class WolfPack {
	public:
		
	ll c[maxn];
	
	ll powerMod(ll a , int n)
	{
		ll res = 1;
		while(n)
		{
			if(n & 1) (res *= a) %= modu;
			a = (a * a) % modu;
			n >>= 1; 
		}
		return res;
	}
	
	ll inv(int a) {  return powerMod(a, modu-2); }
	
	ll getRes(vector<int> a, int m)
	{
		ll ans = 0;
		for(int i=a[0] - m; i<=a[0] + m ; i+=2)
		{
			ll res = 1;
			for(int j=0;j<a.size();j++)
				if(abs(a[j] - i) <= m && abs(a[j] - i - m)%2 == 0)
					(res *= c[(m - abs(a[j] - i))/2]) %= modu;
				else 
				{
					res = 0;
					break;
				}
			(ans += res) %= modu;
		}
		return (ans + modu)%modu;
	}
	
	
	int calc(vector<int> x, vector<int> y, int m) {
		
		c[0] = 1;
		for(int i=1;i<=m;i++) c[i] = (((c[i-1] * (m - i + 1)) % modu) * inv(i)) % modu;
		
		vector<int> z = x , d = x;
		for(int i=0;i<z.size();i++) z[i] = x[i] + y[i] , d[i] = x[i] - y[i];
		return (getRes(z, m) * getRes(d, m)) % modu;
	}
};

// CUT begin
ifstream data("WolfPack.sample");

string next_line() {
	string s;
	getline(data, s);
	return s;
}

template <typename T> void from_stream(T &t) {
	stringstream ss(next_line());
	ss >> t;
}

void from_stream(string &s) {
	s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
	int len;
	from_stream(len);
	ts.clear();
	for (int i = 0; i < len; ++i) {
		T t;
		from_stream(t);
		ts.push_back(t);
	}
}

template <typename T>
string to_string(T t) {
	stringstream s;
	s << t;
	return s.str();
}

string to_string(string t) {
	return "\"" + t + "\"";
}

bool do_test(vector<int> x, vector<int> y, int m, int __expected) {
	time_t startClock = clock();
	WolfPack *instance = new WolfPack();
	int __result = instance->calc(x, y, m);
	double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
	delete instance;

	if (__result == __expected) {
		cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
		return true;
	}
	else {
		cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
		cout << "           Expected: " << to_string(__expected) << endl;
		cout << "           Received: " << to_string(__result) << endl;
		return false;
	}
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
	int cases = 0, passed = 0;
	while (true) {
		if (next_line().find("--") != 0)
			break;
		vector<int> x;
		from_stream(x);
		vector<int> y;
		from_stream(y);
		int m;
		from_stream(m);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(x, y, m, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1477584084;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 850 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	set<int> cases;
	bool mainProcess = true;
	for (int i = 1; i < argc; ++i) {
		if ( string(argv[i]) == "-") {
			mainProcess = false;
		} else {
			cases.insert(atoi(argv[i]));
		}
	}
	if (mainProcess) {
		cout << "WolfPack (850 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
