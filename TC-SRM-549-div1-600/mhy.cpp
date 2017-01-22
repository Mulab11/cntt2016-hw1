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

class MagicalHats {
    public:
        int pow3[105];
        pair<int,int> a[105];
        int dp[2333333],cc[105];
        int cnt[2][20];
        int findMaximumReward(vector<string> board, vector<int> coins, int numGuesses) {
            sort(coins.begin(),coins.end());
            int n=board.size(),m=board[0].size(),q=0;
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (board[i][j]=='H') a[q++]=make_pair(i,j);
            int maxs=1;
            for (int i=0;i<q;i++) pow3[i]=maxs,maxs*=3;
            memset(dp,-1,sizeof(dp));
            for (int s=0;s<maxs;s++){
                int c=0;
                for (int i=0,t=s;i<q;i++,t/=3) cc[c++]=t%3;
                for (int i=0;i<q;i++) if (cc[i]==2) c--;
                if (c>=numGuesses){
                    if (c==q){
                        dp[s]=0;
                        memset(cnt,0,sizeof(cnt));
                        for (int i=0;i<q;i++) if (!cc[i]) cnt[0][a[i].first]^=1,cnt[1][a[i].second]^=1;
                        for (int i=0;i<n;i++) if (cnt[0][i]) dp[s]=-1;
                        for (int i=0;i<m;i++) if (cnt[1][i]) dp[s]=-1;
                        c=0;
                        for (int i=0;i<q;i++) if (cc[i]) c++;
                        if (c!=(int)coins.size()) dp[s]=-1;
                    } else{
                        for (int i=0;i<q;i++) if (cc[i]==2){
                            int x=dp[s-cc[i]*pow3[i]],y=dp[s-cc[i]*pow3[i]+pow3[i]];
                            if (~x) dp[s]=0;
                            if (~y) dp[s]=0;
                        }
                    }
                    //if (q==4) printf("%d %d %d\n",s,c,dp[s]);
                    continue;
                }
                int tag=0;
                for (int i=0;i<q;i++) if (cc[i]==2){
                    int x=dp[s-cc[i]*pow3[i]],y=dp[s-cc[i]*pow3[i]+pow3[i]];
                    if (x>=0||y>=0) dp[s]=max(dp[s],min(x<0?0x3f3f3f3f:x,y<0?0x3f3f3f3f:y+1));
                    tag=1;
                }
                //if (q==4) printf("%d %d\n",s,dp[s]);
                continue;
            }
            if (dp[maxs-1]<0) return -1;
            int ans=0;
            int c=dp[maxs-1];
            for (int i=0;i<c;i++) ans+=coins[i];
            return ans;
        }
};

// CUT begin
ifstream data("MagicalHats.sample");

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

bool do_test(vector<string> board, vector<int> coins, int numGuesses, int __expected) {
    time_t startClock = clock();
    MagicalHats *instance = new MagicalHats();
    int __result = instance->findMaximumReward(board, coins, numGuesses);
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
        vector<string> board;
        from_stream(board);
        vector<int> coins;
        from_stream(coins);
        int numGuesses;
        from_stream(numGuesses);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, coins, numGuesses, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484059980;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MagicalHats (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
