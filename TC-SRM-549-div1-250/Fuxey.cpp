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
const int maxn = 51;
class PointyWizardHats {
    public:
    
    int book[maxn], match[maxn], n, m;    
    vector<int> g[maxn];
    
    bool dfs(int x)
    {
        for(int i=0;i<g[x].size();i++)
        {
            int t = g[x][i];
            if(book[t]) continue;
            book[t] = 1;
            if(match[t] == -1 || dfs(match[t]))
            {
                match[t] = x;
                return true;
            }
        }
        
        return false;
    }
    
    int maxMatch()
    {
        memset(match, -1, sizeof(match));
        int res = 0;
        for(int i=1;i<=n;i++)
        {
            memset(book, 0, sizeof(book));
            res += dfs(i);
        } 
        return res;
    }
    
    
    int getNumHats(vector<int> topHeight, vector<int> topRadius, vector<int> bottomHeight, vector<int> bottomRadius) {
        n = topHeight.size(), m = bottomHeight.size();
        
        for(int i=1;i<=n;i++) g[i].clear();
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(topHeight[i]*bottomRadius[j] > bottomHeight[j]*topRadius[i] && topRadius[i] < bottomRadius[j])
            g[i+1].push_back(j+1);
        return maxMatch();
    }
};

// CUT begin
ifstream data("PointyWizardHats.sample");

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

bool do_test(vector<int> topHeight, vector<int> topRadius, vector<int> bottomHeight, vector<int> bottomRadius, int __expected) {
    time_t startClock = clock();
    PointyWizardHats *instance = new PointyWizardHats();
    int __result = instance->getNumHats(topHeight, topRadius, bottomHeight, bottomRadius);
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
        vector<int> topHeight;
        from_stream(topHeight);
        vector<int> topRadius;
        from_stream(topRadius);
        vector<int> bottomHeight;
        from_stream(bottomHeight);
        vector<int> bottomRadius;
        from_stream(bottomRadius);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(topHeight, topRadius, bottomHeight, bottomRadius, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479039672;
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
        cout << "PointyWizardHats (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
