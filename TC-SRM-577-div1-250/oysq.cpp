#line 2 "EllysRoomAssignmentsDiv1.cpp"  
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

std::vector<int> get(std::vector<std::string> str) {
	std::string s;
	for(int i = 0; i < SZ(str); ++i) s += str[i];
	s += ' ';
	std::vector<int> ret;
	for(int i = 0; i < SZ(s); ++i) {
		int j = i, num = s[i] - '0';
		while(s[j + 1] != ' ') ++j, num = num * 10 + s[j] - '0';
		ret.pb(num);
		i = j + 1;
	}
	return ret;
}

class EllysRoomAssignmentsDiv1 {  
public:  
	double getAverage(vector <string> ratings) {  
		std::vector<int> a = get(ratings);
		int Elly = a[0];
		std::sort(a.begin(), a.end(), std::greater<int>());// 从大到小排序
		int pos = std::find(a.begin(), a.end(), Elly) - a.begin();// Elly的值的位置
		int n = SZ(a), r = (n + 19) / 20;
		double ans1 = 0, ans2 = 0;
		double cnt1 = n / r, cnt2 = cnt1 + 1;
		// ans1 表示当Elly的房间中有cnt1个人的时候的答案
		// ans2 表示当Elly的房间中有cnt2个人的时候的答案
		for(int i = 0; i < n; ++i) {
			int j = i + r - 1;
			if(j < n - 1) {
				double add;
				if(i <= pos && pos <= j) add = Elly;// 有Elly必选
				else add = (double)std::accumulate(a.begin() + i, a.begin() + j + 1, 0) / r;// 否则随机选一个
				ans1 += add / cnt1, ans2 += add / cnt2;
			}
			else {
				if(i <= pos && pos <= j) {// 最后一段有Elly必选
					if(j == n - 1) ans1 += Elly / cnt1, ans2 = 0;
					else ans1 = 0, ans2 += Elly / cnt2;
				}
				else {
					int s = n - 1 - i + 1;
					double add = (double)std::accumulate(a.begin() + i, a.end(), 0) / s;
					if(s < r) ans2 = (ans2 + add / cnt2) * ((double)s / r), ans1 *= (double)(r - s) / r;
					else ans2 = 0, ans1 += add / cnt1;// s == r 时，只能是cnt1个人
				}
			}
			i = j;
		}
		return ans1 + ans2;
	}  	  
};  
