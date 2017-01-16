#line 2 "FoxAndMp3.cpp"  
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

int n;
std::unordered_set<std::string> s;
std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> q;

std::string get(int x) {// 将int变成字符串
	std::string ret;
	while(x) {
		ret += x % 10 + '0';
		x /= 10;
	}
	std::reverse(ret.begin(), ret.end());
	return ret;
}

int num(std::string s) {// 将字符串变成int
	int ret = 0;
	for(auto i : s) {
		ret = ret * 10 + i - '0';
	}
	return ret;
}

void push(std::string str) {// 入队
	if(!s.count(str)) {// 不能出现过
		if(num(str) <= n) {// 要在[1, n]范围内
			s.insert(str);
			q.push(str);
		}
	}
}

class FoxAndMp3 {  
public:  
	vector <string> playList(int _n) {
		s.clear();
		while(!q.empty()) {
			q.pop();
		}
		n = _n;		
		int cnt = std::min(n, 50);// 操作次数
		// 初始元素为1
		q.push(get(1));
		s.insert(get(1));
		std::vector<std::string> ret;
		while(cnt--) {
			std::string cur = q.top();
			q.pop();
			ret.pb(cur + ".mp3");
			push(cur + "0");// 要么扩展一位
			for(int i = 0; i < SZ(cur); ++i) {// 要么任意一位+1
				if(cur[i] < '9') {
					cur[i]++;
					push(cur);
					cur[i]--;
				}
			}
		}		
		return ret;
	}    
};  
