#include <bits/stdc++.h>

using namespace std;

const int MAXN = 510 ; 

int n, m, w[MAXN];

void Parse(const vector<string> &vec, int *arr, int &cnt) {
		string str;
		for(int i = 0; i < vec.size(); i++) str += vec[i];
		for(int i = 0; i < str.length(); i++) {
				if(str[i] == ' ') cnt++;
				else arr[cnt] = arr[cnt] * 10 + (str[i] - '0');
		}
		cnt++;
}

bool cmp(int a, int b) {return a > b; }

class EllysRoomAssignmentsDiv1 {
		public:

				double getAverage(vector<string> ratings)
				{
						Parse(ratings, w, n);
						m = (n + 19) / 20;
						for(int i = 0; i < n; i++)
								w[i] <<= 1 ; 
						w[0] ++ ; 
						sort(w, w + n, cmp) ; 
						double ans = 0, sum = 0;
						for(int i = 0; i < n; i += m) {
								sum = 0;
								for (int j = i; j < i + m && j < n; j ++) if(w[j] & 1) sum += w[j] / 2; 
								if (sum) ans += sum;
								else {
										for (int j = i; j < i + m && j < n; j ++)
												sum += w[j] / 2;
										if (i + m <= n) ans += sum / m; 
										else  ans = 1.0 * (m - n % m) / m * ans / (n / m) * (n / m + 1) + 1.0 * (n % m) / m * (ans + sum / (n % m));
								}
						}
						return ans * m / (n + m - 1);
				}
};
