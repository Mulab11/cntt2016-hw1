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

class GooseTattarrattatDiv1 {
    public:
        int fa[105],size[105],cnt[26];
        inline int find(int i){return fa[i]!=i?fa[i]=find(fa[i]):i;}
        inline void merge(int x,int y){if ((x=find(x))!=(y=find(y))) size[x]+=size[y],fa[y]=x;}
        vector<int> a[105];
        int getmin(string S) {
            int n=S.size();
            for (int i=0;i<26;i++) size[fa[i]=i]=1,cnt[i]=0;
            for (int i=0;i<n;i++) cnt[S[i]-'a']++;
            for (int i=0,j=n-1;i<j;i++,j--) merge(S[i]-'a',S[j]-'a');
            for (int i=0;i<26;i++) a[find(i)].push_back(cnt[i]);
            int ans=0;
            for (int i=0;i<26;i++){
                sort(a[i].begin(),a[i].end());
                for (int j=0;j<(int)a[i].size()-1;j++) ans+=a[i][j];
            }
            return ans;
        }
};

// CUT begin
ifstream data("GooseTattarrattatDiv1.sample");

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

bool do_test(string S, int __expected) {
    time_t startClock = clock();
    GooseTattarrattatDiv1 *instance = new GooseTattarrattatDiv1();
    int __result = instance->getmin(S);
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
        string S;
        from_stream(S);
        next_line();
        int __answer;
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
        int T = time(NULL) - 1475495348;
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
        cout << "GooseTattarrattatDiv1 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
