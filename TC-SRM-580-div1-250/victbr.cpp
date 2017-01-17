#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60;



class EelAndRabbit{
	public:
		int n,len,ans;
		ll a[N<<1];
		int getmax(vector<int> l, vector<int> t){
			n = l.size();
			for (int i = 0;i < n;i++){
				a[++len] = t[i];
				a[++len] = t[i]+l[i];
			}
			for (int i = 1;i <= len;i++){
				int tot = 0;
				for (int k = 0;k < n;k++)
					if (a[i]-t[k] >= 0 && a[i]-t[k]-l[k] <= 0) tot++;
				ans = max(ans,tot);
				int sum = 0;
				for (int j = i+1;j <= len;j++){
					sum =0;
					for (int k = 0;k < n;k++)
						if ((a[i]-t[k] >= 0 && a[i]-t[k]-l[k] <= 0) || (a[j]-t[k] >= 0 && a[j]-t[k]-l[k] <= 0)) sum++;		
					ans = max(ans,sum);		
				}
			}
			return ans;
		}
};
