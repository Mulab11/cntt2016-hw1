#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60;

class TheJediTest{
	public:
		ll a[N];
		int n,ans;
		int minimumSupervisors(vector <int> students, int K){
			n = students.size();ans = 0;
			for (int i = 0;i < n-1;i++){
				ans += (a[i]+students[i])/K;
				if (a[i] == 0){
					a[i+1] += students[i]%K;
				} 
				else if ((a[i]+students[i])%K > students[i]){
					int x = (K-(a[i]+students[i])%K)%K;
					if (x > students[i+1])
						students[i+1] = 0;
					else
						students[i+1] -= x;
					ans++;
				}
				else{
					int x = (a[i]+students[i])%K;
					a[i+1] += x;
				}
			}
			ans += (a[n-1]+students[n-1]+K-1)/K;
			return ans;
		}
};
