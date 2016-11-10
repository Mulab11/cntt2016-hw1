#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

class FoxAndChess
{
public:
	string ableToMove(string S, string T)
	{
		int cnt[2] = {}, N = S.size();
		for(int i = 0; i != N; ++i)
		{
			if(S[i] == 'L') ++cnt[0]; if(T[i] == 'L') --cnt[0];
			if(S[i] == 'R') ++cnt[1]; if(T[i] == 'R') --cnt[1];
		}
		if(cnt[0] || cnt[1]) return "Impossible";
		cnt[0] = cnt[1] = 0;
		for(int a = 0, b = 0; ; ++a, ++b)
		{
			while(a != N && S[a] != 'L') ++a; if(a == N) break;
			while(b != N && T[b] != 'L') ++b; if(b == N) break;
			if(b > a) return "Impossible";
			for(int i = 0; i <= a; ++i) {if(S[i] == 'L') ++cnt[0]; if(S[i] == 'R') ++cnt[1];}
			for(int i = 0; i <= b; ++i) {if(T[i] == 'L') --cnt[0]; if(T[i] == 'R') --cnt[1];}
			if(cnt[0] || cnt[1]) return "Impossible";
		}
		for(int a = 0, b = 0; ; ++a, ++b)
		{
			while(a != N && S[a] != 'R') ++a; if(a == N) break;
			while(b != N && T[b] != 'R') ++b; if(b == N) break;
			if(b < a) return "Impossible";
			for(int i = 0; i <= a; ++i) {if(S[i] == 'L') ++cnt[0]; if(S[i] == 'R') ++cnt[1];}
			for(int i = 0; i <= b; ++i) {if(T[i] == 'L') --cnt[0]; if(T[i] == 'R') --cnt[1];}
			if(cnt[0] || cnt[1]) return "Impossible";
		}
		return "Possible";
	}
}	user;
