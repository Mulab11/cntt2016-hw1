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

const int N = 52;
LL f[N][N], C[2002][2002];
int tot;
LL solve(int n, int k) {
	if(n < 0 || k < 0) return 0;
	LL &res = f[n][k];
	if(res >= 0) return res;
	res = C[n * (n - 1) / 2][k];
	REP(a, 1, n - 1) REP(e, 0, k) {
		LL tmp = C[n - 1][a - 1] * solve(a, e) % mo * C[(n - a) * (n - a - 1) / 2][k - e] % mo;
		res = (res + mo - tmp) % mo;
	}
	return res;
}

class KingdomAndCities {
	public:
	int howMany(int n, int m, int k) {
        CL(f, 0xff);
        tot = n * (n - 1) / 2;
        REP(i, 0, 2000) {
            C[i][0] = C[i][i] = 1;
            REP(j, 1, i - 1)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mo;
        }
		
		if(!m) return solve(n, k);
		if(m == 1) {
			LL ans = C[n - 1][2] * solve(n - 1, k - 2) % mo;
            REP(a, 1, n - 2) REP(e, 0, k - 2) {
				LL tmp = C[n - 2][a - 1] * solve(a, e) % mo * solve(n - 1 - a, k - 2 - e) % mo;
				ans += tmp * a * (n - 1 - a) % mo;
			}
			return ans % mo;
		}
		 //Have led a special city with each other, remaining connected component is one
		LL ans = solve(n - 2, k - 3) * (n - 2) * (n - 2) % mo;
		//special city with each other have is connected, the remaining connected component two 
            REP(a, 1, n - 3) REP(e, 0, k - 3) {
			LL tmp = n >= 3 ? C[n - 3][a - 1] : 0;
			tmp = tmp * solve(a, e) % mo * solve(n - 2 - a, k - 3 - e) % mo;
			ans += tmp * a * (n - 2 - a) * 2 % mo;
		}

		//'re Away is a special city with each other, remaining connected component is one
		if(n >= 2) ans += solve(n - 2, k - 4) * C[n - 2][2] % mo * C[n - 2][2] % mo;
		//'re away is a special city with each other, remaining connected components are two 
		for(int a = 1; a < n - 2; a++) for(int e = 0; e < k - 3; e++){
			int b = n - 2 - a, f = k - 4 - e;
			LL tmp = n >= 3 ? C[n - 3][a - 1] : 0;
			tmp = tmp * solve(a, e) % mo * solve(b, f) % mo;
			//Connection way of a special city 
			tmp = tmp * a * b % mo * (a * b + 2 * (C[a][2] + C[b][2])) % mo;
			ans += tmp;
		}
		//'re Away is a special city with each other, the remaining connected component three
		for(int a = 1; a < n - 3; a++) for(int e = 0; e < k - 3; e++)
		for(int b = 1; b < n - 3; b++) for(int f = 0; f < k - 3; f++){
			int c = n - 2 - a - b, g = k - 4 - e - f;
			if(c <= 0 || g < 0) continue;
			LL tmp = n >= 3 ? C[n - 3][a - 1] : 0;
			tmp *= (n - 3 - a >= 0 ? C[n - 3 - a][b - 1] : 0);
			tmp = tmp % mo * solve(a, e) % mo * solve(b, f) % mo * solve(c, g) % mo;
			//Connection way of a special city 
			tmp = tmp * a * b * c * (a + b + c) * 2 % mo;
			ans += tmp;
		}
		return ans % mo;
	}
};
// CUT begin
ifstream data("KingdomAndCities.sample");

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

bool do_test(int N, int M, int K, int __expected) {
    time_t startClock = clock();
    KingdomAndCities *instance = new KingdomAndCities();
    int __result = instance->howMany(N, M, K);
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
        int N;
        from_stream(N);
        int M;
        from_stream(M);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483961903;
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
        cout << "KingdomAndCities (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
