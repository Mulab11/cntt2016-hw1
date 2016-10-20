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

class HyperKnight 
{
	public:
		long long countCells(int a, int b, int numRows, int numColumns, int K) 
		{
			const int walk[8][2] = {{a, b}, {a, -b}, {-a, b}, {-a, -b}, {b, a}, {b, -a}, {-b, a}, {-b, -a}};
			vector<int> X, Y;
			X.pb(0), X.pb(a), X.pb(b), X.pb(numRows - a), X.pb(numRows - b), X.pb(numRows);
			sort(ALL(X));
			X.resize(unique(ALL(X)) - X.begin());
			Y.pb(0), Y.pb(a), Y.pb(b), Y.pb(numColumns - a), Y.pb(numColumns - b), Y.pb(numColumns);
			sort(ALL(Y));
			Y.resize(unique(ALL(Y)) - Y.begin());
			LL ret = 0;
			REP(i, 0, SZ(X) - 1) REP(j, 0, SZ(Y) - 1) //enumerate every subrectangle where every grid has the same valid ways of moving
			{
				int u = X[i], v = Y[j];
				int cnt = 0;
				REP(k, 0, 8)
				{
					int newu = u + walk[k][0], newv = v + walk[k][1];
					if (newu >= 0 && newu < numRows && newv >= 0 && newv < numColumns) ++cnt;
				}
				if (cnt == K) ret += (LL)(X[i + 1] - X[i]) * (Y[j + 1] - Y[j]); //recalculate the answer if the number of ways is K
			}
			return ret;
		}
};

// CUT begin
ifstream data("HyperKnight.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int a, int b, int numRows, int numColumns, int k, long long __expected) {
    time_t startClock = clock();
    HyperKnight *instance = new HyperKnight();
    long long __result = instance->countCells(a, b, numRows, numColumns, k);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int numRows;
        from_stream(numRows);
        int numColumns;
        from_stream(numColumns);
        int k;
        from_stream(k);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, numRows, numColumns, k, __answer)) {
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
        cout << "HyperKnight (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
