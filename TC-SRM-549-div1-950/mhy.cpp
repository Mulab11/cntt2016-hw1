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

struct Edge{int t,next,cap;} G[10005];int head[20],e;
void init(){memset(head,0,sizeof(head)),e=1;}
inline void add_double_edge(int x,int y,int z){
    G[++e].t=y,G[e].next=head[x],head[x]=e;G[e].cap=z;
    G[++e].t=x,G[e].next=head[y],head[y]=e;G[e].cap=0;
}
int V,S,T;
class CosmicBlocks {
    public:
        int n,ll,rr;
        struct Orz_Dinisap{
            int queue[100005],level[100005];
            bool bfs(){
                memset(level,0,sizeof(*level)*V),level[queue[1]=T]=1;
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
            int max_flow(){
                int ans=0;
                for (;bfs();ans+=dfs(S,0x3f3f3f3f));
                return ans;
            }
        } Dinisap;
        int dep[105];
        int mat[105][105];
        int in[105],out[105];
        int dfs(int x,int y){
            if (y>=n) return dfs(x+1,0);
            if (x==n){
                for (int i=0;i<n;i++) if (out[i]<0||in[i]<0) return 0;
                init();
                for (int i=0;i<n;i++) add_double_edge(S,i,out[i]),add_double_edge(i+n,T,in[i]);
                for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (mat[i][j]) add_double_edge(i,j+n,0x3f3f3f3f);
                for (int i=0;i<n;i++) if (!dep[i]) add_double_edge(i,T,0x3f3f3f3f);
                int sum=0;
                for (int i=0;i<n;i++) sum+=out[i];
                if (sum!=Dinisap.max_flow()) return 0;
                static int p[105];
                for (int i=0;i<n;i++) p[i]=i;
                int ans=0;
                for (;;){
                    int tag=1;
                    for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (mat[i][j]&&p[i]>p[j]) tag=0;
                    ans+=tag;
                    if (!next_permutation(p,p+n)) break;
                }
                return ll<=ans&&ans<=rr;
            }
            int ans=dfs(x,y+1);
            if (dep[x]==dep[y]+1){
                out[x]--,in[y]--;
                mat[x][y]=1;
                ans+=dfs(x,y+1);
                mat[x][y]=0;
                out[x]++,in[y]++;
            }
            return ans;
        }
        int dfsdep(int i){
            static int cnt[105];
            if (i>=n){
                for (int j=1;j<n;j++) if (cnt[j-1]<cnt[j]) return 0;
                //for (int j=0;j<n;j++) printf("%d%c",dep[j]," \n"[j==n-1]);
                return dfs(0,0);
            }
            int ans=0;
            for (int j=0;j<n;j++) cnt[dep[i]=j]+=in[i],ans+=dfsdep(i+1),cnt[j]-=in[i];
            return ans;
        }
        int getNumOrders(vector<int> blockTypes, int minWays, int maxWays) {
            n=blockTypes.size(),ll=minWays,rr=maxWays;
            V=2*n,S=V++,T=V++;
            for (int i=0;i<n;i++) in[i]=out[i]=blockTypes[i];
            return dfsdep(0);
        }
};

// CUT begin
ifstream data("CosmicBlocks.sample");

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

bool do_test(vector<int> blockTypes, int minWays, int maxWays, int __expected) {
    time_t startClock = clock();
    CosmicBlocks *instance = new CosmicBlocks();
    int __result = instance->getNumOrders(blockTypes, minWays, maxWays);
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
        vector<int> blockTypes;
        from_stream(blockTypes);
        int minWays;
        from_stream(minWays);
        int maxWays;
        from_stream(maxWays);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(blockTypes, minWays, maxWays, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484059984;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CosmicBlocks (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
