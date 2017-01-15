#line 2 "KnightCircuit2.cpp"  
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

class KnightCircuit2 {  
public:  
	int maxSize(int w, int h) {  
		if(w > h) std::swap(w, h);
		if(w == 1) return 1;// 只有出生点可以
		else if(w == 2) return (h + 1) / 2;// 从最左边出发，一直往右走
		else {
			if(h == 3) return 8;// w = h = 3的时候中间的走不到，只能走8个格子
			else return w * h;// 因为w = 3, h = 4是都能走到的，因此更大的也都可以
		}
	}  
};  
