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

const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};

struct Edge{int t,next,cap;} G[100005];int head[100005],e;
inline void add_double_edge(int x,int y,int z){
    G[++e].t=y,G[e].next=head[x],head[x]=e;G[e].cap=z;
    G[++e].t=x,G[e].next=head[y],head[y]=e;G[e].cap=0;
}
int V,S,T;
class FoxAndGo3 {
    public:
        struct Orz_Dinisap{
            int queue[100005],level[100005];
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
            int max_flow(){
                int ans=0;
                for (;bfs();ans+=dfs(S,0x3f3f3f3f));
                return ans;
            }
        } Dinisap;
        int id[55][55];
        int maxEmptyCells(vector<string> board) {
            memset(head,0,sizeof(head)),e=1;
            V=0,S=++V,T=++V;
            int nn=board.size(),mm=board[0].size(),ans=0;
            for (int i=0;i<nn;i++) for (int j=0;j<mm;j++) if (board[i][j]!='x') id[i][j]=++V;
            for (int i=0;i<nn;i++) for (int j=0;j<mm;j++) if (board[i][j]!='x'){
                if (board[i][j]=='.'){
                    for (int f=0;f<4;f++){
                        int x=i+dx[f],y=j+dy[f];
                        if (x<0||x>=nn||y<0||y>=mm) continue;
                        if (board[x][y]!='o') continue;
                        add_double_edge(id[i][j],id[x][y],1);
                    }
                    add_double_edge(S,id[i][j],1);
                } else add_double_edge(id[i][j],T,1);
                ans++;
            }
            return ans-Dinisap.max_flow();
        }
};

// CUT begin
ifstream data("FoxAndGo3.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    FoxAndGo3 *instance = new FoxAndGo3();
    int __result = instance->maxEmptyCells(board);
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
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483878121;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FoxAndGo3 (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
