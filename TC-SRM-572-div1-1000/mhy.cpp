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

class NextAndPrev {
    public:
        int cnt[26];
        int dst[26];
        int getMinimum(int nextCost, int prevCost, string start, string goal) {
            if (start==goal) return 0;
            int n=start.size();
            memset(cnt,0,sizeof(cnt));
            for (int i=0;i<n;i++) cnt[goal[i]-'a']++;
            int tag=0;
            for (int i=0;i<26;i++) if (!cnt[i]) tag=1;
            if (!tag) return -1;
            memset(dst,-1,sizeof(dst));
            for (int i=0;i<n;i++) if (dst[start[i]-'a']<0) dst[start[i]-'a']=goal[i]-'a'; else if (dst[start[i]-'a']!=goal[i]-'a') return -1;
            vector<pair<int,int> > a;
            for (int i=0;i<26;i++) if (dst[i]>=0) a.push_back(make_pair(i,dst[i]));
            int m=a.size(),ans=0x3f3f3f3f;
            for (int t=0;t<m;t++,a[0].first+=26){
                sort(a.begin(),a.end());
                int tag=1;
                for (int i=1;i<m;i++) if (a[i-1].second>a[i].second) tag=0;
                if (!tag) continue;
                for (int d=-1;d<=2;d++){
                    for (int i=0;i<m;i++) a[i].second+=d*26;
                    int t=0;
                    for (int l=0,r;l<m;l=r){
                        for (r=l+1;r<m&&a[l].second==a[r].second;r++);
                        int minv=a[l].second,maxv=a[l].second;
                        for (int i=l;i<r;i++){
                            minv=min(minv,a[i].first);
                            maxv=max(maxv,a[i].first);
                        }
                        t+=(a[l].second-minv)*nextCost;
                        t+=(maxv-a[l].second)*prevCost;
                    }
                    ans=min(ans,t);
                    for (int i=0;i<m;i++) a[i].second-=d*26;
                }
            }
            return ans!=0x3f3f3f3f?ans:-1;
        }
};

// CUT begin
ifstream data("NextAndPrev.sample");

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

bool do_test(int nextCost, int prevCost, string start, string goal, int __expected) {
    time_t startClock = clock();
    NextAndPrev *instance = new NextAndPrev();
    int __result = instance->getMinimum(nextCost, prevCost, start, goal);
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
        int nextCost;
        from_stream(nextCost);
        int prevCost;
        from_stream(prevCost);
        string start;
        from_stream(start);
        string goal;
        from_stream(goal);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(nextCost, prevCost, start, goal, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483803639;
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
        cout << "NextAndPrev (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
