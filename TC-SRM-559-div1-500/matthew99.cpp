#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 54;

vector<int> adj[maxn + 5];

int cnt[maxn + 5];
int dep[maxn + 5];
int Max[maxn + 5], Min[maxn + 5];

bool dfs(int x, int f = -1)
{
	int d = 0;
	Max[x] = -oo, Min[x] = oo;
	for (auto y : adj[x]) if (y != f)
	{
		++d;
		dep[y] = dep[x] + 1;
		if (!dfs(y, x)) return 0;
		chkmax(Max[x], Max[y]);
		chkmin(Min[x], Min[y]);
	}
	if (d > 2) return 0;
	if (d < 2)
	{
		chkmax(Max[x], dep[x]); 
		chkmin(Min[x], dep[x]); 
	}
	if (Max[x] > Min[x] + 1) return 0; //fail if a vertex is unbalanced by more than 1 
	if (Max[x] != Min[x]) ++cnt[dep[x]];
	if (cnt[dep[x]] > 1) return 0; //fail if more than one unbalanced verteces share the same depth
	return 1;
}

class HatRack 
{
	public:
		long long countWays(vector<int> knob1, vector<int> knob2) 
		{
			int n = SZ(knob1) + 1;
			if (n <= 2) return n;
			REP(i, 0, n) adj[i].clear();
			REP(i, 0, n - 1)
			{
				adj[knob1[i] - 1].pb(knob2[i] - 1);
				adj[knob2[i] - 1].pb(knob1[i] - 1);
			}
			LL ret = 0;
			REP(i, 0, n) //enumerate the root
			{
				memset(cnt, 0, sizeof cnt);
				if (dep[i] = 0, dfs(i))
				{
					LL tmp = 1;
					REP(j, 0, n) if ((SZ(adj[j]) - (j != i)) && Max[j] == Min[j]) tmp <<= 1; //every balanced vertex leads to two ways of tranversing
					ret += tmp;
				}
			}
			return ret;
		}
};

// CUT begin
ifstream data("HatRack.sample");

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

bool do_test(vector<int> knob1, vector<int> knob2, long long __expected) {
    time_t startClock = clock();
    HatRack *instance = new HatRack();
    long long __result = instance->countWays(knob1, knob2);
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
        vector<int> knob1;
        from_stream(knob1);
        vector<int> knob2;
        from_stream(knob2);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(knob1, knob2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
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
        cout << "HatRack (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
