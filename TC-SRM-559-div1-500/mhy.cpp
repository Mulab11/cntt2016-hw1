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

class HatRack {
    public:
        struct Edge{int t,next;} G[105];int head[105],e;
        int queue[105],pre[105],depth[105],c[105],d[105][2],cc[105];
        long long countWays(vector<int> X, vector<int> Y) {
            memset(head,0,sizeof(head)),e=1;
            int n=X.size()+1;
            for (int i=0;i<n-1;i++){
                int x=X[i],y=Y[i];
                G[++e].t=y,G[e].next=head[x],head[x]=e;
                G[++e].t=x,G[e].next=head[y],head[y]=e;
            }
            long long ans=0;
            for (int root=1;root<=n;root++){
                pre[queue[1]=root]=0,depth[root]=1;
                for (int x,l=1,r=1;l<=r;l++) for (int i=head[x=queue[l]];i;i=G[i].next) if (G[i].t!=pre[x]) pre[queue[++r]=G[i].t]=x,depth[G[i].t]=depth[x]+1;
                memset(c,0,sizeof(c)),memset(d,0,sizeof(d)),memset(cc,0,sizeof(cc));
                int tag=1;
                for (int x,l=n;l;d[x][0]++,d[x][1]++,l--){
                    x=queue[l];
                    d[x][0]=n+1,d[x][1]=0;
                    for (int i=head[x];i;i=G[i].next)
                        if (G[i].t!=pre[x]) d[x][0]=min(d[G[i].t][0],d[x][0]),d[x][1]=max(d[G[i].t][1],d[x][1]),cc[x]++;
                    if (cc[x]>2) tag=0;
                    if (cc[x]<=1) d[x][0]=0;
                    if (d[x][1]-d[x][0]>1) tag=0;
                    //printf("cc %d %d %d %d %d\n",root,x,cc[x],d[x][0],d[x][1]);
                }
                long long sum=1;
                for (int i=1;i<=n;i++) if (d[i][0]!=d[i][1]) c[depth[i]]++; else if (cc[i]==2) sum<<=1;
                for (int i=1;i<=n;i++) if (c[i]>1) tag=0;
                if (!tag) continue;
                //printf("add %d %lld %d %d %d\n",root,sum,d[root][0],d[root][1],cc[root]);
                ans+=sum;
            }
            return ans;
        }
};

// CUT begin
ifstream data("HatRack.sample");

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

bool do_test(vector<int> knob1, vector<int> knob2, long long __expected) {
    time_t startClock = clock();
    HatRack *instance = new HatRack();
    long long __result = instance->countWays(knob1, knob2);
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
        vector<int> knob1;
        from_stream(knob1);
        vector<int> knob2;
        from_stream(knob2);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(knob1, knob2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483630357;
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
        cout << "HatRack (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
