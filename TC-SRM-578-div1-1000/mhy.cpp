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

template <typename T> inline void tension(T &a,const T &b){if (a>b) a=b;}
template <typename T> inline bool tensionv(T &a,const T &b){return a>b?a=b,true:false;}

class DeerInZooDivOne {
    public:
        int n;
        struct Min_Cost_Flow{
            static const int MAXV=205,MAXE=100005;
            struct Edge{int t,next,cap,v;} G[MAXE];int head[MAXV],e;
            inline void add_double_edge(int x,int y,int z,int v){
                G[++e].t=y,G[e].next=head[x],head[x]=e;G[e].cap=z,G[e].v=v;
                G[++e].t=x,G[e].next=head[y],head[y]=e;G[e].cap=0,G[e].v=-v;
            }
            void init(){memset(head,0,sizeof(head)),e=1;}
            int V,S,T;
            int dist[MAXV],vis[MAXV];
            pair<int,int> heap[MAXE];int heap_size;
            void SPFA(){
                memset(dist+1,0x3f,sizeof(*dist)*V),heap[heap_size++]=make_pair(-(dist[T]=0),T);
                for (int d,x;heap_size;){
                    d=-heap->first,x=heap->second,pop_heap(heap,heap+heap_size--);
                    if (d!=dist[x]) continue;
                    for (int i=head[x];i;i=G[i].next) if (G[i^1].cap&&tensionv(dist[G[i].t],d-G[i].v))
                        heap[heap_size++]=make_pair(-dist[G[i].t],G[i].t),push_heap(heap,heap+heap_size);
                }
            }
            int dfs(int x,int aug0){
                if (x==T) return aug0;vis[x]=1;
                int aug=aug0;
                for (int i=head[x];i;i=G[i].next) if (!vis[G[i].t]&&G[i].cap&&dist[x]==dist[G[i].t]+G[i].v){
                    int flow=dfs(G[i].t,min(aug,G[i].cap));
                    if (flow){
                        G[i].cap-=flow,G[i^1].cap+=flow,aug-=flow;
                    }
                }
                return aug0-aug;
            }
            bool adjust(){
                int d=0x3f3f3f3f;
                for (int x=1;x<=V;x++) if (vis[x]) for (int i=head[x];i;i=G[i].next) if (!vis[G[i].t]&&G[i].cap) tension(d,dist[G[i].t]+G[i].v-dist[x]);
                if (d==0x3f3f3f3f) return false;
                for (int i=1;i<=V;i++) if (vis[i]) dist[i]+=d;
                return true;
            }
            pair<int,int> min_cost_flow(){
                pair<int,int> ans(0,0);
                for (SPFA();;){
                    for (int t;;){
                        memset(vis+1,0,sizeof(*vis)*V);
                        if ((t=dfs(S,0x3f3f3f3f))) ans.first+=t,ans.second+=t*dist[S]; else break;
                    }
                    if (!adjust()) break;
                }
                return ans;
            }
        } MCF;
        vector<int> G[55];
        int col[55];
        int dp[55][55][55][55];
        int id[55];
        int DP(int x,int fx,int y,int fy){
            int &ans=dp[x][fx][y][fy];
            if (~ans) return ans;
            for (int i=0;i<(int)G[x].size();i++) if (G[x][i]!=fx) for (int j=0;j<(int)G[y].size();j++) if (G[y][j]!=fy) DP(G[x][i],x,G[y][j],y);
            int &V=MCF.V,&S=MCF.S,&T=MCF.T;
            MCF.init();
            V=0,S=++V,T=++V;
            for (int i=0;i<(int)G[x].size();i++) if (G[x][i]!=fx) MCF.add_double_edge(S,id[G[x][i]]=++V,1,0);
            for (int j=0;j<(int)G[y].size();j++) if (G[y][j]!=fy) MCF.add_double_edge(id[G[y][j]]=++V,T,1,0);
            for (int i=0;i<(int)G[x].size();i++) if (G[x][i]!=fx)
                for (int j=0;j<(int)G[y].size();j++) if (G[y][j]!=fy)
                    MCF.add_double_edge(id[G[x][i]],id[G[y][j]],1,-DP(G[x][i],x,G[y][j],y));
            return ans=1-MCF.min_cost_flow().second;
        }
        int calc(){
            for (int i=1;i<=n;i++) if (!col[i]) for (int j=1;j<=n;j++) if (col[j]) dp[i][0][j][0]=-1;
            for (int i=1;i<=n;i++) if (!col[i]) for (int j=0;j<(int)G[i].size();j++)
                for (int k=1;k<=n;k++) if (col[k]) for (int l=0;l<(int)G[k].size();l++) dp[i][G[i][j]][k][G[k][l]]=-1;
            int ans=0;
            for (int i=1;i<=n;i++) if (!col[i]) for (int j=1;j<=n;j++) if (col[j]) ans=max(ans,DP(i,0,j,0));
            return ans;
        }
        void dfs(int x,int fa,int c){col[x]=c;for (int i=0;i<(int)G[x].size();i++) if (G[x][i]!=fa) dfs(G[x][i],x,c);}
        int getmax(vector<int> X, vector<int> Y) {
            n=(int)X.size()+1;
            for (int i=0;i<n-1;i++) X[i]++,Y[i]++;
            int ans=0;
            for (int i=0;i<n-1;i++){
                for (int j=1;j<=n;j++) G[j].clear();
                for (int j=0;j<n-1;j++) if (i!=j){
                    int x=X[j],y=Y[j];
                    G[x].push_back(y),G[y].push_back(x);
                }
                dfs(X[i],Y[i],0),dfs(Y[i],X[i],1);
                ans=max(ans,calc());
            }
            return ans;
        }
};

// CUT begin
ifstream data("DeerInZooDivOne.sample");

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

bool do_test(vector<int> a, vector<int> b, int __expected) {
    time_t startClock = clock();
    DeerInZooDivOne *instance = new DeerInZooDivOne();
    int __result = instance->getmax(a, b);
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
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475574814;
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
        cout << "DeerInZooDivOne (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
