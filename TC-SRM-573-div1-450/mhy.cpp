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

template <typename T> inline bool tensionv(T &a,const T &b){return a>b?a=b,true:false;}

const int MAXV=55*55,MAXE=55*55*55*55;

class SkiResorts {
    public:
        long long dist[MAXV];
        pair<long long,int> heap[MAXE>>2];int heap_size;
        long long minCost(vector<string> road, vector<int> altitude) {
            int n=road.size();
            memset(dist,0x3f,sizeof(dist));
            for (int i=0;i<n;i++) heap[heap_size++]=make_pair(-(dist[i]=abs(altitude[i]-altitude[0])),i);
            make_heap(heap,heap+heap_size);
            for (int x,y;heap_size;){
                long long d=-heap->first;x=heap->second,pop_heap(heap,heap+heap_size--);
                if (d!=dist[x]) continue;
                int i=x/n,j=x%n;
                for (int k=0;k<n;k++) if (road[i][k]=='Y'){
                    for (int l=0;l<n;l++) if (altitude[j]>=altitude[l]){
                        //printf("%d %d %d %d %d\n",d,i,j,k,l);
                        if (tensionv(dist[y=k*n+l],d+abs(altitude[l]-altitude[k])))
                            heap[heap_size++]=make_pair(-dist[y],y),push_heap(heap,heap+heap_size);
                    }
                }
            }
            long long ans=0x3f3f3f3f3f3f3f3fll;
            for (int i=0;i<n;i++) ans=min(ans,dist[(n-1)*n+i]);
            return ans!=0x3f3f3f3f3f3f3f3fll?ans:-1;
        }
};

// CUT begin
ifstream data("SkiResorts.sample");

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

bool do_test(vector<string> road, vector<int> altitude, long long __expected) {
    time_t startClock = clock();
    SkiResorts *instance = new SkiResorts();
    long long __result = instance->minCost(road, altitude);
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
        vector<string> road;
        from_stream(road);
        vector<int> altitude;
        from_stream(altitude);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(road, altitude, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475846939;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SkiResorts (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
