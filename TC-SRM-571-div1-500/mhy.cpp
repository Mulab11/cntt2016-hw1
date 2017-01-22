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

class MagicMolecule {
    public:
        int n,ans,cnt;
        vector<int> w;
        vector<string> a;
        int vis[105];
        void dfs(int x,int y){
            if (cnt*3<2*n) return;
            if (x>=n){
                int tag=1;
                for (int i=0;tag&&i<n;i++) if (!vis[i]) for (int j=i+1;tag&&j<n;j++) if (!vis[j]) if (a[i][j]=='N') tag=0;
                if (tag){
                    int sum=0;
                    for (int i=0;i<n;i++) if (!vis[i]) sum+=w[i];
                    ans=max(ans,sum);
                }
                return;
            }
            if (y>=n) return dfs(x+1,x+1);
            if (x==y) return dfs(x,y+1);
            if (a[x][y]=='Y') return dfs(x,y+1);
            if (vis[x]||vis[y]) return dfs(x,y+1);
            vis[x]=1;
            cnt--;
            dfs(x,y+1);
            vis[x]=0;
            cnt++;
            vis[y]=1;
            cnt--;
            dfs(x,y+1);
            vis[y]=0;
            cnt++;
        }
        int maxMagicPower(vector<int> magicPower, vector<string> magicBond) {
            n=magicPower.size(),ans=-1,cnt=n;
            w=magicPower,a=magicBond;
            dfs(0,0);
            return ans;
        }
};

// CUT begin
ifstream data("MagicMolecule.sample");

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

bool do_test(vector<int> magicPower, vector<string> magicBond, int __expected) {
    time_t startClock = clock();
    MagicMolecule *instance = new MagicMolecule();
    int __result = instance->maxMagicPower(magicPower, magicBond);
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
        vector<int> magicPower;
        from_stream(magicPower);
        vector<string> magicBond;
        from_stream(magicBond);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(magicPower, magicBond, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483287725;
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
        cout << "MagicMolecule (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
