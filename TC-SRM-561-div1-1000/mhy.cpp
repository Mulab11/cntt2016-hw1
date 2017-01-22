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

const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};

int V;
int n,m;
struct Edge{int t,next;} G[10005];int head[10005],e;
inline void add_edge(int x,int y){G[++e].t=y,G[e].next=head[x],head[x]=e;}
double C(int n,int m){if (n<=m) return n==m;double ans=1;for (int i=0;i<m;i++) ans*=1.0*(n-i)/(m-i);return ans;}
class Orienteering {
    public:
        int id[105][105];
        int queue[10005],pre[10005],tag[10005],size[10005],num[10005];
        int dist[305][305];
        void dfs(int root,int x,int fa,int v){
            if (tag[x]) dist[tag[root]][tag[x]]=v;
            for (int i=head[x];i;i=G[i].next) if (G[i].t!=fa) dfs(root,G[i].t,x,v+1);
        }
        double expectedLength(vector<string> field, int K) {
            memset(head,0,sizeof(head)),e=1;
            n=field.size(),m=field[0].size(),V=0;
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (field[i][j]!='#') id[i][j]=++V; else id[i][j]=0;
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (field[i][j]!='#') for (int f=0;f<4;f++){
                int x=i+dx[f],y=j+dy[f];
                if (x<0||x>=n||y<0||y>=m||field[x][y]=='#') continue;
                add_edge(id[i][j],id[x][y]);
            }
            pre[queue[1]=1]=0;
            for (int x,l=1,r=1;l<=r;l++) for (int i=head[x=queue[l]];i;i=G[i].next) if (G[i].t!=pre[x]) pre[queue[++r]=G[i].t]=x;
            int q=0;
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (field[i][j]!='#') tag[id[i][j]]=(field[i][j]=='*')?++q:0;
            for (int i=1;i<=V;i++) if (tag[i]) size[num[tag[i]]=i]=1;
            double ans=0;
            for (int x,l=V;l;l--) for (int i=head[x=queue[l]];i;i=G[i].next) if (G[i].t!=pre[x]) size[x]+=size[G[i].t],ans+=1-(C(size[G[i].t],K)+C(q-size[G[i].t],K))/C(q,K);
            ans*=2;
            memset(dist,0,sizeof(dist));
            for (int i=1;i<=q;i++) dfs(num[i],num[i],0,0);
            double sum=0;
            for (int _i=1;_i<=q;_i++) for (int _j=_i+1;_j<=q;_j++){
                int i=num[_i],j=num[_j];
                int c=0;
                for (int _k=1;_k<=q;_k++){
                    int k=num[_k];
                    if (i!=k&&j!=k&&(dist[_i][_k]<dist[_i][_j]||(dist[_i][_k]==dist[_i][_j]&&k>j))&&(dist[_j][_k]<dist[_i][_j]||(dist[_j][_k]==dist[_i][_j]&&k>i))) c++;
                }
                sum+=dist[_i][_j]*(C(c,K-2)/C(q,K));
            }
            return ans-sum;
        }
};

// CUT begin
ifstream data("Orienteering.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> field, int K, double __expected) {
    time_t startClock = clock();
    Orienteering *instance = new Orienteering();
    double __result = instance->expectedLength(field, K);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<string> field;
        from_stream(field);
        int K;
        from_stream(K);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475294421;
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
        cout << "Orienteering (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
