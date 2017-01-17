#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1100;

class LittleElephantAndIntervalsDiv1{
	public:
		bool b[N];
		int n;
		ll ans;
		long long getNumber(int M, vector <int> L, vector <int> R){
			n = L.size();
			ans = 1;
			for (int i = n-1;i >= 0;i--){
				bool flag = 0;
				for (int j = L[i];j <= R[i];j++){
					if (b[j] == 0) flag = 1;
					b[j] = 1;
				}
				if (flag) ans <<= 1;
			}
			return ans;
		}		
};
