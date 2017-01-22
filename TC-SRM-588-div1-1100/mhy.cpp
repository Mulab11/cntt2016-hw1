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

class GameInDarknessDiv1 {
    public:
        struct Edge{int t,next;} G[10005];int head[10005],e;
        inline void add_edge(int x,int y){
            G[++e].t=y,G[e].next=head[x],head[x]=e;
            //G[++e].t=x,G[e].next=head[y],head[y]=e;
        }
        int id[55][55];
        int queue[10005],pre[10005],depth[10005],maxdepth[10005];
        string check(vector<string> field) {
            memset(head,0,sizeof(head)),e=1;
            int nn=field.size(),mm=field[0].size(),n=0,A,B;
            for (int i=0;i<nn;i++) for (int j=0;j<mm;j++) if (field[i][j]!='#') id[i][j]=++n;
            for (int i=0;i<nn;i++) for (int j=0;j<mm;j++) if (field[i][j]!='#'){
                if (field[i][j]=='A') A=id[i][j];
                if (field[i][j]=='B') B=id[i][j];
                for (int f=0;f<4;f++){
                    int x=i+dx[f],y=j+dy[f];
                    if (x<0||x>=nn||y<0||y>=mm) continue;
                    if (field[x][y]=='#') continue;
                    add_edge(id[i][j],id[x][y]);
                }
            }
            int ans=0;
            for (int root=1;root<=n;root++){
                pre[queue[1]=root]=0,depth[root]=0;
                for (int x,l=1,r=1;l<=r;maxdepth[x]=0,l++) for (int i=head[x=queue[l]];i;i=G[i].next) if (G[i].t!=pre[x]) pre[queue[++r]=G[i].t]=x,depth[G[i].t]=depth[x]+1;
                for (int x,l=n;l;l--,maxdepth[x]++) for (int i=head[x=queue[l]];i;i=G[i].next) if (G[i].t!=pre[x]) maxdepth[x]=max(maxdepth[x],maxdepth[G[i].t]);
                int c=0;
                for (int i=head[root];i;i=G[i].next) if (maxdepth[G[i].t]>=3) c++;
                if (depth[A]>=depth[B]+2&&c>=3) ans=1;
            }
            return ans?"Bob wins":"Alice wins";
        }
};

// CUT begin
ifstream data("GameInDarknessDiv1.sample");

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

bool do_test(vector<string> field, string __expected) {
    time_t startClock = clock();
    GameInDarknessDiv1 *instance = new GameInDarknessDiv1();
    string __result = instance->check(field);
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
        vector<string> field;
        from_stream(field);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483878163;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1100 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "GameInDarknessDiv1 (1100 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
