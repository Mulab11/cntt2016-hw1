#include <bits/stdc++.h>

using namespace std;
const int N = 2600;

class EllysRoomAssignmentsDiv1{
	public:
		string s;
		double ans;
		int k,n,tot,m,a[N],val;
		double getAverage(vector <string> ratings){
			n = ratings.size();
			for (int i = 0;i < n;i++) s = s + ratings[i];
			for (int i = 0;i < s.size();i++){
				if (s[i] == ' ') {a[++m] = tot;tot = 0;}
				else tot = tot*10+s[i]-'0';
			}
			a[++m] = tot;
			k = (m+19)/20; 
			val = a[1];
			sort(a+1,a+m+1);
			int i = m,j = 0;
			for (i;i >= k;i -= k){
				bool flag = 0;double sum = 0;
				for (int j = 0;j < k;j++){
					if (a[i-j] == val) flag = 1;
					sum += a[i-j];
				}
				if (flag) ans = (ans*j+val)/(j+1);
				else ans = (ans*j+sum/k)/(j+1);
				j++;
			}
			if (i){
				bool flag = 0;double sum = 0;
				for (int o = 1;o <= i;o++) {
					if (a[o] == val) flag = 1;
					sum += a[o];
				}
				if (flag) ans = (ans*j+val)/(j+1);
				else ans = ans*(k-i)/k+(ans*j+sum/i)/(j+1)*i/k;//分到和分不到的分母不一样 
			}
			return ans;
		}
};
