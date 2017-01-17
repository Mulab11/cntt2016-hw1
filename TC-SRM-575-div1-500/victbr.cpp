#include <bits/stdc++.h>

using namespace std;

const int N = 2610;

class TheSwapsDivOne{
	public:
		double ans,f,g,f1,g1;
		int a[N],len,sum;
		string s;
		double find(vector<string> seq,int k){
			for (int i = 0;i < seq.size();i++)
				s += seq[i];			
			for (int i = 0;i < s.size();i++)
				a[++len] = s[i]-'0';	
			for (int i = 1;i <= len;i++) sum += a[i];
			f1 = 1;
			g1 = 0;
			for (int i = 1;i <= k;i++){
				f = f1/len*(len-2)+g1*2/len;
				g = (1.0-f)/(len-1);
				f1 = f;g1 = g;
			}
			
			for (int i = 1;i <= len;i++)
				ans += (double)i*(len-i+1)*2/len/(len+1)*(g*(sum-a[i])+f*a[i]);
			return ans;
		}
}A;



