/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
	if (b < *a) {
		*a = b;
		return true;
	}
	return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
	if (b > *a) {
		*a = b;
		return true;
	}
	return false;
}

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const int N = 50;
int a[N][N];
int gauss(int n) {//Matrix-Tree Theorem 
	//using gauss elimination to calculate det(A)
	int ans = 1;
	REP(i, 1, n) {
		if (!a[i][i]) {
			ans *= -1;
			REP(j, i + 1, n) if (a[j][i]) {
				REP(k, i, n) swap(a[i][k], a[j][k]);
				break;
			}
		}
		if (!a[i][i]) return 0;
		REP(j, 1, n) if (j != i && a[j][i]) {
			int t = 1LL * a[j][i] * pow(a[i][i], mo - 2) % mo;
			REP(k, 1, n) a[j][k] = (a[j][k] - 1LL * a[i][k] * t % mo + mo) % mo;
		}
	}
	REP(i, 1, n) ans = 1LL * ans * a[i][i] % mo;
	return (ans % mo + mo) % mo;
}
int v[N];
int n, m;
void ae(int x, int y) { // add one edge in the graph
	a[x][y] = mo - 1;
	a[x][x] ++;
}
void build(int k) { // build the graph of last n -  k candy is not sweet
	CL(a, 0);
	REP(i, 1, k) { // the first k candy can adjoin any candy
		REP(j, 1, k) if (j != i) ae(i, j);
		REP(j, m + 1, n) ae(i, j);
	}
	REP(i, k + 1, m) REP(j, m + 1, n) ae(i, j); // k~m candy can only adjoin bitter candies
	REP(i, m + 1, n) REP(j, 1, n) if (i != j) ae(i, j);
}
int tree[N], num[N];
int c[N][N];
int tmp[N];
PII t1[1100000];
PII t2[1100000];
class SweetFruits {
	public:
		int countTrees(vector<int> sweetness, int maxSweetness) {
			n = sweetness.size();
			sort(sweetness.begin(), sweetness.end(), greater<int>());
			m = 0;
			REP(i, 1, n) v[i] = sweetness[i - 1];
			REP(i, 1, n) if (v[i] >= 0) ++m;
			REP(i, 1, n) { // calculate the bionomial coefficient
				c[i][0] = c[i][i] = 1;
				REP(j, 1, i - 1) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mo;
			}
			int l1 = m / 2, l2 = m - l1;
			int tot1 = 0, tot2 = 0;
			for (int s = 0; s < (1 << l1); ++s) { // meet in middle
				int x = 0, y = 0;
				REP(i, 1, l1) if (s & (1 << (i - 1))) x += v[i], ++y;
				t1[++tot1] = MP(x, y);
			}
			for (int s = 0; s < (1 << l2); ++s) {
				int x = 0, y = 0;
				REP(i, 1, l2) if (s & (1 << (i - 1))) x += v[i + l1], ++y;
				t2[++tot2] = MP(x, y);
			}
			sort(t1 + 1, t1 + tot1 + 1, greater<PII>()); // sort two arrays
			sort(t2 + 1, t2 + tot2 + 1);
			int j = 1;
			CL(tmp, 0);
			CL(num, 0);
			CL(tree, 0);
			REP(i, 1, tot1) { // two pointers to calc the number of ways to choose k candies out of m sweet candies
				while (j <= tot2 && t2[j].FR + t1[i].FR <= maxSweetness) {
					tmp[t2[j].SC]++;
					++j;
				}
				REP(k, t1[i].SC, m) num[k] = (num[k] + tmp[k - t1[i].SC]) % mo;
			}
			REP(i, 0, m) {
				build(i); 
				tree[i] = gauss(n - 1);//use Matrix Tree 
				REP(j, 0, i - 1) tree[i] = (tree[i] - 1LL * c[i][j] * tree[j] % mo + mo) % mo; // inclusive and exlusive principle
			}
			int ans = 0;
			REP(i, 0, m) ans = (ans + 1LL * tree[i] * num[i] % mo) % mo; // combine two arrays
			return ans;
		}
};

// CUT begin
ifstream data("SweetFruits.sample");

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

bool do_test(vector<int> sweetness, int maxSweetness, int __expected) {
    time_t startClock = clock();
    SweetFruits *instance = new SweetFruits();
    int __result = instance->countTrees(sweetness, maxSweetness);
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
        vector<int> sweetness;
        from_stream(sweetness);
        int maxSweetness;
        from_stream(maxSweetness);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(sweetness, maxSweetness, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1481543552;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SweetFruits (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
