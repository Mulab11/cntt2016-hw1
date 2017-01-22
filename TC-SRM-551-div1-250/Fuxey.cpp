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

class ColorfulChocolates {
    public:
    int n, d[51][2501][30];
    
    int id(char c) { return c - 'A'; }
    void update(int &a , int b) { a = max(a, b); }
    int maximumSpread(string chocolates, int maxSwaps) {
        n = chocolates.size();
        
        int res = 0;
        for(int i=0;i<n;i++) for(int j=i;j<n;j++)
            if(chocolates[i] == chocolates[j])
            {
                vector<int> v;
                for(int k=i;k<=j;k++)
                    if(chocolates[k] == chocolates[i])
                        v.push_back(k);
                
                
                bool ok = false;
                for(int k=0;k<v.size();k++)
                {
                    int now = 0;
                    for(int l=k-1;l>=0;l--) now += abs(v[k]-(k-l)-v[l]);
                    for(int l=k+1;l<v.size();l++) now += abs(v[k]+(l-k)-v[l]);
                    
                    if(now <= maxSwaps)
                    { 
                        ok = true;
                        break;
                    }
                    if(i == 1 && j == 6) cout<<k<<" "<<now<<endl;
                }
                if(ok) res = max(res, (int)v.size());
            }
        return res;
    }
};

// CUT begin
ifstream data("ColorfulChocolates.sample");

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

bool do_test(string chocolates, int maxSwaps, int __expected) {
    time_t startClock = clock();
    ColorfulChocolates *instance = new ColorfulChocolates();
    int __result = instance->maximumSpread(chocolates, maxSwaps);
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
        string chocolates;
        from_stream(chocolates);
        int maxSwaps;
        from_stream(maxSwaps);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(chocolates, maxSwaps, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479130625;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ColorfulChocolates (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
