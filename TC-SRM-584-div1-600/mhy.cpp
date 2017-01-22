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

class Excavations {
    public:
        int tag[105];
        long long dp[105][105][2];
        long long C[55][55];
        long long trans[55];
        long long count(vector<int> kind, vector<int> depth, vector<int> found, int K) {
            int n=kind.size();
            for (int i=0;i<=50;*C[i++]=1) for (int j=1;j<=i;j++) C[i][j]=C[i-1][j-1]+C[i-1][j];
            memset(tag,0,sizeof(tag));
            for (int i=0;i<found.size();i++) tag[found[i]]=1;
            long long ans=0;
            vector<int> Set;
            for (int i=0;i<n;i++) Set.push_back(depth[i]);
            sort(Set.begin(),Set.end());
            Set.resize(unique(Set.begin(),Set.end())-Set.begin());
            for (int _i=0;_i<Set.size();_i++){
                int baseline=Set[_i];
                memset(dp,0,sizeof(dp));
                dp[0][0][0]=1;
                for (int i=1;i<=50;i++){
                    if (!tag[i]){
                        for (int j=0;j<=K;j++) for (int f=0;f<2;f++) dp[i][j][f]=dp[i-1][j][f];
                        int cnt[]={0,0};
                        for (int j=0;j<n;j++) if (kind[j]==i&&depth[j]>=baseline){
                            if (depth[j]==baseline) cnt[0]++; else cnt[1]++;
                        }
                        if (!cnt[0]&&!cnt[1]) continue;
                        for (int j=1;j<=K;j++) trans[j]=C[cnt[1]][j];
                        for (int j=0;j<=K;j++) for (int f=0;f<2;f++) if (dp[i-1][j][f]){
                            for (int k=1;k<=K;k++) if (j+k<=K) dp[i][j+k][f]+=dp[i-1][j][f]*trans[k];
                        }
                        if (!cnt[0]) continue;
                        for (int j=1;j<=K;j++){
                            trans[j]=0;
                            for (int k=1;k<=j;k++) if (k<=cnt[0]) trans[j]+=C[cnt[0]][k]*C[cnt[1]][j-k];
                        }
                        for (int j=0;j<=K;j++) for (int f=0;f<2;f++) if (dp[i-1][j][f]){
                            for (int k=1;k<=K;k++) if (j+k<=K) dp[i][j+k][1]+=dp[i-1][j][f]*trans[k];
                        }
                    } else{
                        int cnt[]={0,0};
                        for (int j=0;j<n;j++) if (kind[j]==i){
                            if (depth[j]<baseline) cnt[0]++; else cnt[1]++;
                        }
                        if (!cnt[0]&&!cnt[1]) continue;
                        for (int j=1;j<=K;j++){
                            trans[j]=0;
                            for (int k=1;k<=cnt[0];k++) trans[j]+=C[cnt[0]-k+cnt[1]][j-1];
                        }
                        for (int j=0;j<=K;j++) for (int f=0;f<2;f++) if (dp[i-1][j][f]){
                            for (int k=1;k<=K;k++) if (j+k<=K) dp[i][j+k][f]+=dp[i-1][j][f]*trans[k];
                        }
                    }
                }
                ans+=dp[50][K][1];
                //printf("%d %d %lld\n",_i,baseline,dp[50][K][1]);
            }
            memset(dp,0,sizeof(dp));
            dp[0][0][0]=1;
            for (int i=1;i<=50;i++){
                if (!tag[i]){
                    for (int j=0;j<=K;j++) for (int f=0;f<2;f++) dp[i][j][f]=dp[i-1][j][f];
                } else{
                    int cnt[]={0,0};
                    for (int j=0;j<n;j++) if (kind[j]==i){
                        if (1) cnt[0]++; else cnt[1]++;
                    }
                    if (!cnt[0]&&!cnt[1]) continue;
                    for (int j=1;j<=K;j++){
                        trans[j]=0;
                        for (int k=1;k<=cnt[0];k++) trans[j]+=C[cnt[0]-k+cnt[1]][j-1];
                    }
                    for (int j=0;j<=K;j++) for (int f=0;f<2;f++) if (dp[i-1][j][f]){
                        for (int k=1;k<=K;k++) if (j+k<=K) dp[i][j+k][f]+=dp[i-1][j][f]*trans[k];
                    }
                }
            }
            ans+=dp[50][K][0];
            return ans;
        }
};

// CUT begin
ifstream data("Excavations.sample");

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

bool do_test(vector<int> kind, vector<int> depth, vector<int> found, int K, long long __expected) {
    time_t startClock = clock();
    Excavations *instance = new Excavations();
    long long __result = instance->count(kind, depth, found, K);
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
        vector<int> kind;
        from_stream(kind);
        vector<int> depth;
        from_stream(depth);
        vector<int> found;
        from_stream(found);
        int K;
        from_stream(K);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(kind, depth, found, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483287698;
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
        cout << "Excavations (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
