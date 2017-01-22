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
#include <map>

using namespace std;

template <typename T> inline void tension(T &a,const T &b){if (a>b) a=b;}
template <typename T> inline void relax(T &a,const T &b){if (a<b) a=b;}

class Mountains {
    public:
        static const int mod=1000000009;
        vector<int> a;
        int n,m;
        map<string,int> Map[105];
        string state[105];
        int L[105],R[105];
        int dfs(int i){
            if (i>=n) return 1;
            if (Map[i].find(state[i])!=Map[i].end()) return Map[i][state[i]];
            int ans=0;
            if (L[i]<0){
                int c=0;
                for (int j=0;j<m;j++) if (state[i][j]>=a[i]) c++;
                state[i+1]=string(state[i]);
                ans=1ll*dfs(i+1)*c%mod;
                //printf("0 ans:%d %d %d\n",i,ans,c);for (int j=0;j<m;j++) printf("%d%c",state[i][j]," \n"[j==m-1]);
                Map[i][state[i]]=ans;
                return ans;
            }
            //printf("%d %d %d %d\n",i,L[i],R[i],int(state[i].size()));
            //for (int j=0;j<m;j++) printf("%d%c",state[i][j]," \n"[j==m-1]);
            int l=0,r=m-1;
            relax(l,L[i]-(a[i]-state[i][L[i]]-1)),tension(r,L[i]+(a[i]-state[i][L[i]]-1));
            if (L[i]!=0) l=max(l,(L[i]-1)+(a[i]-state[i][L[i]-1]));
            relax(l,R[i]-(a[i]-state[i][R[i]]-1)),tension(r,R[i]+(a[i]-state[i][R[i]]-1));
            if (R[i]!=m-1) r=min(r,(R[i]+1)-(a[i]-state[i][R[i]+1]));
            //printf("%d:%d %d\n",i,l,r);
            for (int j=l;j<=r;j++){
                state[i+1]=string(state[i]);
                for (int k=0;k<a[i];k++){
                    if (j-k>=0) relax(state[i+1][j-k],char(a[i]-k));
                    if (j+k<m) relax(state[i+1][j+k],char(a[i]-k));
                }
                ans=(ans+dfs(i+1))%mod;
            }
            //printf("ans:%d %d\n",i,ans);
            Map[i][state[i]]=ans;
            return ans;
        }
        int countPlacements(vector<int> heights, vector<string> visibility) {
            a=heights;
            reverse(a.begin(),a.end());
            reverse(visibility.begin(),visibility.end());
            n=heights.size(),m=visibility[0].size();
            for (int i=0;i<n;i++){
                L[i]=R[i]=-1;
                for (int j=0;j<m;j++) if (visibility[i][j]=='X'){
                    int k=0;
                    for (k=j+1;k<m&&visibility[i][k]=='X';k++);
                    L[i]=j,R[i]=k-1;
                    break;
                }
            }
            for (int i=0;i<=n;i++) Map[i].clear();
            state[0]=string(m,0);
            return dfs(0);
        }
};

// CUT begin
ifstream data("Mountains.sample");

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

bool do_test(vector<int> heights, vector<string> visibility, int __expected) {
    time_t startClock = clock();
    Mountains *instance = new Mountains();
    int __result = instance->countPlacements(heights, visibility);
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
        vector<int> heights;
        from_stream(heights);
        vector<string> visibility;
        from_stream(visibility);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(heights, visibility, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1480509864;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Mountains (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
