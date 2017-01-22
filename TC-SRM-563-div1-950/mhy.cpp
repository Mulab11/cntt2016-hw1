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
#include <map>

using namespace std;

const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};

class CoinsGame {
    public:
        static const int mod=1000000009;
        inline long long qpow(long long x,int y){
            long long ans=1;
            for (;y;y>>=1,x=x*x%mod) if (y&1) ans=ans*x%mod;
            return ans;
        }
        struct rec{
            int d[4];
            friend inline bool operator <(const rec &a,const rec &b){
                for (int i=0;i<4;i++) if (a.d[i]!=b.d[i]) return a.d[i]<b.d[i];
                return false;
            }
            friend inline bool operator ==(const rec &a,const rec &b){
                for (int i=0;i<4;i++) if (a.d[i]!=b.d[i]) return false;
                return true;
            }
            inline long long hashcode(){
                long long ans=0;
                for (int i=0;i<4;i++) ans=ans<<15|d[i];
                return ans;
            }
        } a[55][55];
        struct Hash_Table{
            static const int hash_size=10007,MAXN=1000005;
            int head[hash_size],next[MAXN],n;long long v[MAXN];
            void init(){memset(head,0,sizeof(head)),n=0;}
            inline void insert(long long x){
                int h=x%hash_size;
                for (int i=head[h];i;i=next[i]) if (v[i]==x) return;
                v[++n]=x,next[n]=head[h],head[h]=n;
            }
            inline int find(long long x){
                for (int i=head[x%hash_size];i;i=next[i]) if (v[i]==x) return i;
                return -1;
            }
        } HT;
        //map<long long,int> Map;
        int id[55][55];
        int tmp[2505];
        int ways(vector<string> board) {
            int n=board.size(),m=board[0].size();
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (board[i][j]!='#') id[i][j]=1;
            for (;;){
                //Map.clear();
                HT.init();
                for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (board[i][j]!='#'){
                    for (int f=0;f<4;f++){
                        int x=i+dx[f],y=j+dy[f];
                        if (x<0||x>=n||y<0||y>=m) {a[i][j].d[f]=0;continue;}
                        if (board[x][y]=='#') x=i,y=j;
                        a[i][j].d[f]=id[x][y];
                    }
                    //Map[a[i][j].hashcode()]='?';
                    HT.insert(a[i][j].hashcode());
                }
                //int last=0;
                //for (map<long long,int>::iterator iti=Map.begin();iti!=Map.end();iti++) Map[iti->first]=++last;
                int tag=0;
                for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (board[i][j]!='#'){
                    //int x=Map[a[i][j].hashcode()];
                    int x=HT.find(a[i][j].hashcode());
                    if (x!=id[i][j]){
                        tag=1;
                        id[i][j]=x;
                    }
                }
                if (!tag) break;
            }
            *tmp=0;
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (board[i][j]!='#') tmp[++*tmp]=id[i][j];
            sort(tmp+1,tmp+*tmp+1);
            long long ans=(qpow(2,*tmp)+mod-1)%mod;
            for (int l=1,r;l<=*tmp;l=r+1){
                for (r=l;r<*tmp&&tmp[l]==tmp[r+1];r++);
                ans=(ans+mod-qpow(2,r-l+1)+1)%mod;
            }
            return int(ans);
        }
};

// CUT begin
ifstream data("CoinsGame.sample");

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
    CoinsGame *instance = new CoinsGame();
    int __result = instance->ways(board);
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
        int T = time(NULL) - 1484325785;
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
        cout << "CoinsGame (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
