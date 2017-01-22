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
int V,S,T;
struct Edge{int t,next,cap;} G[1000005];int head[100005],e;
class FoxAndCity {
    public:
        int id[55][55];
        inline void add_double_edge(int x,int y,int z){
            G[++e].t=y,G[e].next=head[x],head[x]=e;G[e].cap=z;
            G[++e].t=x,G[e].next=head[y],head[y]=e;G[e].cap=0;
        }
        struct Orz_Dinisap{
            int level[100005],queue[100005];
            bool bfs(){
                memset(level,0,sizeof(level)),level[queue[1]=T]=1;
                for (int x,l=1,r=1;l<=r;l++) for (int i=head[x=queue[l]];i;i=G[i].next) if (G[i^1].cap&&!level[G[i].t]) level[queue[++r]=G[i].t]=level[x]+1;
                return level[S]!=0;
            }
            int dfs(int x,int aug0){
                if (x==T) return aug0;
                int aug=aug0;
                for (int i=head[x];i;i=G[i].next) if (G[i].cap&&level[x]==level[G[i].t]+1){
                    int flow=dfs(G[i].t,min(aug,G[i].cap));
                    if (flow){
                        G[i].cap-=flow,G[i^1].cap+=flow,aug-=flow;
                    } else level[G[i].t]=0;
                }
                return aug0-aug;
            }
            int max_flow(){
                int ans=0;
                for (;bfs();ans+=dfs(S,0x3f3f3f3f));
                return ans;
            }
        } Dinisap;
        int minimalCost(vector<string> linked, vector<int> want) {
            int n=linked.size();
            memset(head,0,sizeof(head)),e=1;
            V=0;
            for (int i=0;i<n;++i) for (int j=0;j<n;++j) id[i][j]=++V;
            S=++V,T=++V;
            if (1<n){
                add_double_edge(id[0][1],T,0x3f3f3f3f);
                for (int i=1;i<n;++i) add_double_edge(S,id[i][1],0x3f3f3f3f);
            }
            for (int i=0;i<n;++i) for (int j=0;j<n;++j){
                if (!j) add_double_edge(S,id[i][j],0x3f3f3f3f);
                else add_double_edge(id[i][j],id[i][j-1],0x3f3f3f3f);
                add_double_edge(id[i][j],j<n-1?id[i][j+1]:T,(j-want[i])*(j-want[i]));
            }
            for (int i=0;i<n;++i) for (int j=0;j<n;++j) if (linked[i][j]=='Y') for (int k=0;k<n;++k){
                if (k) add_double_edge(id[i][k],id[j][k-1],0x3f3f3f3f);
            }
            return Dinisap.max_flow();
        }
};

// CUT begin
ifstream data("FoxAndCity.sample");

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

bool do_test(vector<string> linked, vector<int> want, int __expected) {
    time_t startClock = clock();
    FoxAndCity *instance = new FoxAndCity();
    int __result = instance->minimalCost(linked, want);
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
        vector<string> linked;
        from_stream(linked);
        vector<int> want;
        from_stream(want);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(linked, want, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1480509949;
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
        cout << "FoxAndCity (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
