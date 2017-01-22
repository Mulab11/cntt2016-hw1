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

class XorCards {
    public:
        long long a[233];
        long long Q[233];int V[233];
        long long numberOfWays(vector<long long> number, long long limit) {
            int n=number.size();
            for (int i=0;i<n;i++) for (int j=0;j<63;j++) if (number[i]>>j&1) a[j]|=1ll<<i;
            limit++;
            long long ans=0;
            for (int i=63;i--;) if (limit>>i&1){
                int q=0;
                bool tag=true;
                for (int j=i;j<63;j++){
                    int v=i==j?0:limit>>j&1;
                    long long t=a[j];
                    for (int k=0;k<q;k++) if ((Q[k]&-Q[k])&t) t^=Q[k],v^=V[k];
                    if (!t&&v) tag=false;
                    if (!t) continue;
                    for (int k=0;k<q;k++) if (Q[k]&(t&-t)) Q[k]^=t,V[k]^=v;
                    Q[q]=t,V[q]=v;
                    q++;
                }
                if (tag) ans+=1ll<<(n-q);//,printf("%d %lld\n",i,ans);
            }
            return ans;
        }
};

// CUT begin
ifstream data("XorCards.sample");

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

bool do_test(vector<long long> number, long long limit, long long __expected) {
    time_t startClock = clock();
    XorCards *instance = new XorCards();
    long long __result = instance->numberOfWays(number, limit);
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
        vector<long long> number;
        from_stream(number);
        long long limit;
        from_stream(limit);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(number, limit, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1480509943;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "XorCards (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
