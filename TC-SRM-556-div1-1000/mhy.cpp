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

const int MAXV=100005,MAXE=100005;
struct Edge{int t,next,cap;} G[MAXE];int head[MAXV],e;
inline void add_double_edge(int x,int y,int z){
    G[++e].t=y,G[e].next=head[x],head[x]=e;G[e].cap=z;
    G[++e].t=x,G[e].next=head[y],head[y]=e;G[e].cap=0;
}
class OldBridges {
    public:
        struct Orz_Dinisap{
            int V,S,T;
            int queue[MAXV],level[MAXV];
            bool bfs(){
                memset(level+1,0,sizeof(*level)*V),level[queue[1]=T]=1;
                for (int x,l=1,r=1;l<=r&&(!level[S]||level[queue[l]]<level[S]);l++) for (int i=head[x=queue[l]];i;i=G[i].next)
                    if (G[i^1].cap&&!level[G[i].t]) level[queue[++r]=G[i].t]=level[x]+1;
                return level[S]!=0;
            }
            int dfs(int x,int aug0){
                if (x==T) return aug0;
                int aug=aug0;
                for (int i=head[x];i;i=G[i].next) if (G[i].cap&&level[x]==level[G[i].t]+1){
                    int flow=dfs(G[i].t,min(aug,G[i].cap));
                    if (flow){
                        G[i].cap-=flow,G[i^1].cap+=flow,aug-=flow;
                        if (!aug) break;
                    } else level[G[i].t]=0;
                }
                return aug0-aug;
            }
            int max_flow(int _V,int _S,int _T){
                V=_V,S=_S,T=_T;
                int ans=0;
                for (;bfs();ans+=dfs(S,0x3f3f3f3f));
                return ans;
            }
        } Dinisap;
        int id[MAXV];
        string isPossible(vector<string> bridges, int a1, int a2, int an, int b1, int b2, int bn) {
            int n=bridges.size(),V=0,S=++V,T=++V;
            for (int i=0;i<n;i++) id[i]=++V;

            memset(head,0,sizeof(head)),e=1;
            add_double_edge(S,id[a1],2*an),add_double_edge(S,id[b1],2*bn),add_double_edge(id[a2],T,2*an),add_double_edge(id[b2],T,2*bn);
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (bridges[i][j]!='X') add_double_edge(id[i],id[j],bridges[i][j]=='O'?2:0x3f3f3f3f);
            int ans0=Dinisap.max_flow(V,S,T);

            memset(head,0,sizeof(head)),e=1;
            add_double_edge(S,id[a1],2*an),add_double_edge(S,id[b2],2*bn),add_double_edge(id[a2],T,2*an),add_double_edge(id[b1],T,2*bn);
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (bridges[i][j]!='X') add_double_edge(id[i],id[j],bridges[i][j]=='O'?2:0x3f3f3f3f);
            int ans1=Dinisap.max_flow(V,S,T);

            //printf("%d %d\n",ans0,ans1);
            return ans0==ans1&&ans0==2*(an+bn)?"Yes":"No";
        }
};

// CUT begin
ifstream data("OldBridges.sample");

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

bool do_test(vector<string> bridges, int a1, int a2, int an, int b1, int b2, int bn, string __expected) {
    time_t startClock = clock();
    OldBridges *instance = new OldBridges();
    string __result = instance->isPossible(bridges, a1, a2, an, b1, b2, bn);
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
        vector<string> bridges;
        from_stream(bridges);
        int a1;
        from_stream(a1);
        int a2;
        from_stream(a2);
        int an;
        from_stream(an);
        int b1;
        from_stream(b1);
        int b2;
        from_stream(b2);
        int bn;
        from_stream(bn);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(bridges, a1, a2, an, b1, b2, bn, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325904;
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
        cout << "OldBridges (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
