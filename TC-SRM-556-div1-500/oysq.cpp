#line 2 "LeftRightDigitsGame2.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;

int n;
string d, lb;
string f[N + 9][N + 9][3];
// f[i][j] means minimal string consist of d[0 ~ j - i] which fill in interval [i, j] in 3 situations
// 0 -> string < lowerbound[i ~ j]
// 1 -> string = lowerbound[i ~ j]
// 2 -> string > lowerbound[i ~ j]

// update answer
void update(string &s, const string &t) {
	if(s == "") s = t;
	else chkmin(s, t);
}

class LeftRightDigitsGame2 {  
public:  
	string minNumber(string _d, string _lb) {
		d = _d, lb = _lb, n = SZ(d);
		// initial
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = 0; k < 3; ++k)
					f[i][j][k] = "";
		// pretreat intervals with length 1
		for(int i = 0; i < n; ++i)
			if(d[0] < lb[i]) f[i][i][0] = d[0];
			else if(d[0] == lb[i]) f[i][i][1] = d[0];
			else f[i][i][2] = d[0];
		//enumerate length from 2 ~ n
		for(int l = 1; l < n; ++l)// l + 1 denotes length
			for(int i = 0; i + l < n; ++i) {
				int j = i + l;// interval[i ~ j]
				string cur = lb.substr(i, l + 1);// lowerbound[i ~ j]
				for(int k = 0; k < 3; ++k) {
					if(j && f[i][j - 1][k] != "" && f[i][j - 1][k] + d[l] < cur) update(f[i][j][0], f[i][j - 1][k] + d[l]);
					// f[i][j][k] is ""(empty) means that such situation is not possible, so as below
					if(f[i + 1][j][k] != "" && d[l] + f[i + 1][j][k] < cur) update(f[i][j][0], d[l] + f[i + 1][j][k]);
				}
				if(f[i + 1][j][1] != "" && d[l] + f[i + 1][j][1] == cur) f[i][j][1] = d[l] + f[i + 1][j][1];
				if(j && f[i][j - 1][1] != "" && f[i][j - 1][1] + d[l] == cur) f[i][j][1] = f[i][j - 1][1] + d[l];
				for(int k = 0; k < 3; ++k) {
					if(j && f[i][j - 1][k] != "" && f[i][j - 1][k] + d[l] > cur) update(f[i][j][2], f[i][j - 1][k] + d[l]);
					if(f[i + 1][j][k] != "" && d[l] + f[i + 1][j][k] > cur) update(f[i][j][2], d[l] + f[i + 1][j][k]);
				}
			}
		if(f[0][n - 1][1] != "") return f[0][n - 1][1];
		else return f[0][n - 1][2];
	}    
};  
