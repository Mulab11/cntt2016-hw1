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

class StringGame {
    public:
        int cnt[105][105],id[105],vis[105];
        vector<int> getWinningStrings(vector<string> S) {
            memset(cnt,0,sizeof(cnt));
            int n=S.size();
            vector<int> ans;
            for (int i=0;i<n;i++) for (int j=0;j<(int)S[i].size();j++) cnt[i][S[i][j]-'a']++;
            for (int i=0;i<n;i++){
                memset(vis,0,sizeof(vis));
                int m=n;
                for (int j=0;j<m;j++) id[j]=j;
                for (;;){
                    int tag=-1;
                    for (int j=0;j<26;j++) if (!vis[j]){
                        int flag=1;
                        for (int k=0;k<m;k++) if (cnt[i][j]<cnt[id[k]][j]) flag=0;
                        if (flag) {vis[tag=j]=1;break;}
                    }
                    //printf("%d %d %d\n",i,tag,m);
                    if (tag<0) break;
                    int q=0;
                    for (int j=0;j<m;j++) if (cnt[i][tag]==cnt[id[j]][tag]) id[q++]=id[j];
                    m=q;
                }
                //printf("%d %d\n",i,m);
                if (m==1) ans.push_back(i);
            }
            return ans;
        }
};

// CUT begin
ifstream data("StringGame.sample");

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

bool do_test(vector<string> S, vector<int> __expected) {
    time_t startClock = clock();
    StringGame *instance = new StringGame();
    vector<int> __result = instance->getWinningStrings(S);
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
        vector<string> S;
        from_stream(S);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1480509859;
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
        cout << "StringGame (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
