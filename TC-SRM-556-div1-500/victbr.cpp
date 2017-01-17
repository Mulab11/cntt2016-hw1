#include <bits/stdc++.h>

using namespace std;

const int N = 60;

class LeftRightDigitsGame2{
	public:
		string f[N][N],g[N],h[N][N];
		int n;
		string minNumber(string digits, string lowerBound){
			n = digits.size();
			
			for (int i = 0;i < n;i++){
				if (digits[0] >= lowerBound[i]) 
					f[0][i] = digits[0];
				if (digits[0] > lowerBound[i]) 
					h[0][i] = digits[0];					
			}
			g[0] = digits[0];
			
			for (int i = 1;i < n;i++)
				if (digits[i]+g[i-1] < g[i-1]+digits[i])
					g[i] = digits[i]+g[i-1];
				else g[i] = g[i-1]+digits[i];

			for (int i = 1;i < n;i++)
				for (int j = 0;j+i < n;j++){

					if (digits[i] > lowerBound[j]){
						f[i][j] = digits[i]+g[i-1];
						h[i][j] = f[i][j];
					}
					
					if (digits[i] == lowerBound[j]){
						if (f[i-1][j+1] != ""){
							if (f[i][j] == "")
								f[i][j] = digits[i]+f[i-1][j+1];
							else
								f[i][j] = min(f[i][j],digits[i]+f[i-1][j+1]);
						}
						if (h[i-1][j+1] != "") 
							if (h[i][j] == "") h[i][j] = digits[i]+h[i-1][j+1];
							else h[i][j] = min(h[i][j],digits[i]+h[i-1][j+1]);
					}
					
					
					if (f[i-1][j] != ""){
						if (digits[i] >= lowerBound[j+i])
							if (f[i][j] != "")
								f[i][j] = min(f[i][j],f[i-1][j]+digits[i]); 
							else f[i][j] = f[i-1][j]+digits[i];
						if (digits[i] > lowerBound[j+i])
							if (h[i][j] != "")
								h[i][j] = min(h[i][j],f[i-1][j]+digits[i]); 
							else h[i][j] = f[i-1][j]+digits[i];
					}
					if (h[i-1][j] != ""){
						if (f[i][j] != "")f[i][j] = min(f[i][j],h[i-1][j]+digits[i]); 
							else f[i][j] = h[i-1][j]+digits[i];	
						if (h[i][j] == "") h[i][j] = h[i-1][j]+digits[i];
							else h[i][j] = min(h[i][j],h[i-1][j]+digits[i]);
					}					
				}
			return f[n-1][0];
		}
};
