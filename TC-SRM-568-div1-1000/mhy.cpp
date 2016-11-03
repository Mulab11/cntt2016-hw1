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

namespace force{//这里是大暴力1
    int n,m;
    vector<int> a;
    int match[105];
    struct Edge{int t,next;} G[105*105];int head[105],e;
    inline void add_edge(int x,int y){
        G[++e].t=y,G[e].next=head[x],head[x]=e;
        G[++e].t=x,G[e].next=head[y],head[y]=e;
    }
    int vis[105];
    bool color(int x){//二分图染色
        for (int i=head[x];i;i=G[i].next) if (vis[G[i].t]<0){
            if (vis[G[i].t]=!vis[x],!color(G[i].t)) return false;
        } else if (vis[G[i].t]==vis[x]) return false;
        return true;
    }
    bool ok(){
        memset(head,0,sizeof(head)),e=1;
        for (int i=0;i<n;i++) if (i<match[i]){
            for (int j=i+1;j<match[i];j++) if (match[i]<match[j]){//对相交的圆连边
                add_edge(i,j);
            }
        }
        memset(vis,-1,sizeof(vis));
        for (int i=0;i<n;i++) if (i<match[i]) if (vis[i]<0&&(vis[i]=0,!color(i))) return false;//枚举+染色
        return true;
    }
    bool dfs(int i){//一波爆搜
        if (i==m) return ok();
        if (~match[a[i]]) return dfs(i+1);
        for (int j=i+1;j<m;j++) if (match[a[j]]<0){//强行枚举连边
            match[a[j]]=a[i],match[a[i]]=a[j];
            if (dfs(i+1)) return true;
            match[a[i]]=match[a[j]]=-1;
        }
        return false;
    }
    string solve(vector<int> labels){
        memset(match,-1,sizeof(match));//初始化
        n=labels.size();
        for (int i=0;i<n;i++) if (labels[i]>=0) for (int j=0;j<n;j++) if (i!=j&&labels[i]==labels[j]) match[i]=j;
        a.clear();
        n=labels.size();
        for (int i=0;i<n;i++) if (labels[i]<0) a.push_back(i);
        m=a.size();
        return dfs(0)?"POSSIBLE":"IMPOSSIBLE";
    }
}

namespace force2{//这里是大暴力2
    int n,m,q;
    vector<int> a;
    vector<pair<int,int> > b;
    int tag[105];
    struct Edge{int t,next,v;} G[105*105];int head[105],e;
    inline void add_edge(int x,int y,int z){
        G[++e].t=y,G[e].next=head[x],head[x]=e;G[e].v=z;
        G[++e].t=x,G[e].next=head[y],head[y]=e;G[e].v=z;
    }
    int vis[105];
    bool color(int x){//二分图染色
        for (int i=head[x];i;i=G[i].next) if (vis[G[i].t]<0){
            vis[G[i].t]=vis[x]^G[i].v;
            if (!color(G[i].t)) return false;
        } else if (vis[G[i].t]!=(vis[x]^G[i].v)) return false;
        return true;
    }
    bool ok(){
        memset(head,0,sizeof(head)),e=1;
        for (int i=0;i<q;i++) for (int j=0;j<q;j++) if (i!=j&&tag[i]==tag[j]&&b[i].first<b[j].first&&b[j].first<b[i].second&&b[i].second<b[j].second) return false;//判已知条件是否有误
        for (int i=0;i<q;i++){
            int l=lower_bound(a.begin(),a.end(),b[i].first)-a.begin(),r=upper_bound(a.begin(),a.end(),b[i].second)-a.begin();
            l--,r--;
            add_edge(l,r,tag[i]?0:((r-l)&1));//前缀和之间连边，注意方向与权值的关系
        }
        add_edge(0,m-1,0);
        memset(vis,-1,sizeof(vis));
        for (int i=0;i<n;i++) if (vis[i]<0&&(vis[i]=0,!color(i))) return false;//枚举+染色
        //for (int i=0;i<m;i++) printf("%d\n",a[i]);
        //for (int i=0;i<q;i++) printf("cir:%d %d %d\n",b[i].first,b[i].second,tag[i]);
        //for (int x=0;x<m;x++) for (int i=head[x];i;i=G[i].next) printf("%d %d %d\n",x,G[i].t,G[i].v);
        return true;
    }
    bool dfs(int i){//爆搜一波已知圆的方向
        if (i==q) return ok();
        tag[i]=0;if (dfs(i+1)) return true;
        tag[i]=1;if (dfs(i+1)) return true;
        return false;
    }
    string solve(vector<int> labels){
        a.clear(),b.clear();//初始化
        n=labels.size();
        a.push_back(-1);
        for (int i=0;i<n;i++) if (labels[i]<0) a.push_back(i);
        //a.push_back(n);
        for (int i=0;i<n;i++) if (labels[i]>=0) for (int j=i+1;j<n;j++) if (labels[i]==labels[j]) b.push_back(make_pair(i,j));
        m=a.size(),q=b.size();
        return dfs(0)?"POSSIBLE":"IMPOSSIBLE";
    }
}

class DisjointSemicircles {
    public:
        string getPossibility(vector<int> labels) {
            if (std::count(labels.begin(),labels.end(),-1)<=12) return force::solve(labels); else return force2::solve(labels);//一个分类讨论
        }
};

// CUT begin
ifstream data("DisjointSemicircles.sample");

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

bool do_test(vector<int> labels, string __expected) {
    time_t startClock = clock();
    DisjointSemicircles *instance = new DisjointSemicircles();
    string __result = instance->getPossibility(labels);
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
        vector<int> labels;
        from_stream(labels);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(labels, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475159412;
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
        cout << "DisjointSemicircles (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
