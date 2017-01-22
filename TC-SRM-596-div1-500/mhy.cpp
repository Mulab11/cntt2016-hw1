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

class BitwiseAnd {
    public:
        int tag[60];
        vector<long long> lexSmallest(vector<long long> a, int N) {
            int n=a.size();
            for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if ((a[i]&a[j])==0) return vector<long long>();
            for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) for (int k=j+1;k<n;k++) if (a[i]&a[j]&a[k]) return vector<long long>();
            for (;n<N;){
                long long x=0;
                memset(tag,0,sizeof(tag));
                for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) for (int k=0;k<60;k++) if (a[i]>>k&1) if (a[j]>>k&1) tag[k]=1;
                for (int i=0;i<n;i++) if ((a[i]&x)==0){
                    int ok=0;
                    for (int j=0;j<60;j++) if (!tag[j]) if (a[i]>>j&1){
                        ok=1;
                        x|=1ll<<j;
                        tag[j]=1;
                        break;
                    }
                    if (!ok) return vector<long long>();
                }
                for (int i=0;i<n;i++) for (int j=0;j<60;j++) if (a[i]>>j&1) tag[j]=1;
                //printf("%lld\n",x);
                int c=N-n-1;
                for (int i=0;c&&i<60;i++) if (!tag[i]){
                    x|=1ll<<i;
                    c--;
                }
                if (c) return vector<long long>();
                //printf("%lld\n",x);
                a.push_back(x),n++;
                for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if ((a[i]&a[j])==0) return vector<long long>();
                for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) for (int k=j+1;k<n;k++) if (a[i]&a[j]&a[k]) return vector<long long>();
            }
            sort(a.begin(),a.end());
            return a;
        }
};

// CUT begin
ifstream data("BitwiseAnd.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<long long> subset, int N, vector<long long> __expected) {
    time_t startClock = clock();
    BitwiseAnd *instance = new BitwiseAnd();
    vector<long long> __result = instance->lexSmallest(subset, N);
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
        vector<long long> subset;
        from_stream(subset);
        int N;
        from_stream(N);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(subset, N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483630488;
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
        cout << "BitwiseAnd (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
