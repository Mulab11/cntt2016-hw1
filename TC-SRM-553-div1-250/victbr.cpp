#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60;

class Suminator{
	public:
		bool b[N*3];
		ll sta[N*3];
		int len,n,ans;
		int findMissing(vector <int> program, int wantedResult){
			n = program.size();
			ans = -1;
			check1(program,wantedResult);
			check0(program,wantedResult);			
			return ans;
		}
		void check0(vector <int> program, int wantedResult){
			len = 100;
			for (int i = 1;i <= len;i++)
				sta[i] = 0;
			for (int i = 0;i < n;i++)
				if (program[i] <= 0){
					len--;sta[len] += sta[len+1];
				}
				else sta[++len] = program[i];
			if (sta[len] == wantedResult) ans = 0;	
		}
		void check1(vector <int> program, int wantedResult){
			len = 100;
			memset(b,0,sizeof(b));
			for (int i = 1;i <= len;i++)
				sta[i] = 0;
			for (int i = 0;i < n;i++)
				if (program[i] == 0){
					len--;sta[len] += sta[len+1];
					b[len] |= b[len+1];
					b[len+1] = 0;
				}
				else if (program[i] == -1) {
				b[++len] = 1;
				sta[len] = 0;//
				}
				else sta[++len] = program[i];
			if (sta[len] == wantedResult && !b[len]) ans = 1;
			if (sta[len] < wantedResult && b[len]) 
				ans = wantedResult-sta[len];
		}
};
