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

class KeyDungeonDiv1 {
    public:
        int dp[1<<13][200];
        int maxKeys(vector<int> doorR, vector<int> doorG, vector<int> roomR, vector<int> roomG, vector<int> roomW, vector<int> keys) {
            memset(dp,-1,sizeof(dp));
            int n=doorR.size(),ans=0;
            dp[0][keys[0]]=keys[2];
            for (int s=0;s<1<<n;s++) for (int r=0;r<=160;r++) if (~dp[s][r]){
                int g=keys[0]+keys[1]+keys[2];
                for (int i=0;i<n;i++) if (s>>i&1) g+=roomR[i]+roomG[i]+roomW[i]-doorR[i]-doorG[i];
                g-=r+dp[s][r];
                for (int i=0;i<n;i++) if (~s>>i&1){
                    int rr=max(r-doorR[i],0),gg=max(g-doorG[i],0),ww=dp[s][r]-(doorR[i]-(r-rr))-(doorG[i]-(g-gg));
                    if (ww<0) continue;
                    //printf("%d %d %d %d %d %d %d\n",s,r,g,i,rr,gg,ww);
                    rr+=roomR[i],ww+=roomW[i];
                    dp[s|1<<i][rr]=max(dp[s|1<<i][rr],ww);
                }
                //printf("%d %d %d %d\n",s,r,g,dp[s][r]);
                ans=max(ans,r+g+dp[s][r]);
            }
            return ans;
        }
};

// CUT begin
ifstream data("KeyDungeonDiv1.sample");

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

bool do_test(vector<int> doorR, vector<int> doorG, vector<int> roomR, vector<int> roomG, vector<int> roomW, vector<int> keys, int __expected) {
    time_t startClock = clock();
    KeyDungeonDiv1 *instance = new KeyDungeonDiv1();
    int __result = instance->maxKeys(doorR, doorG, roomR, roomG, roomW, keys);
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
        vector<int> doorR;
        from_stream(doorR);
        vector<int> doorG;
        from_stream(doorG);
        vector<int> roomR;
        from_stream(roomR);
        vector<int> roomG;
        from_stream(roomG);
        vector<int> roomW;
        from_stream(roomW);
        vector<int> keys;
        from_stream(keys);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(doorR, doorG, roomR, roomG, roomW, keys, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483878158;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "KeyDungeonDiv1 (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
