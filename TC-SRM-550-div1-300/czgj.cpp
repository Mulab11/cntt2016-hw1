/*
	Implementation.
*/

#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};
int A[255][255];
int x, y, xl, xr, yl, yr;
class RotatingBot {
	public:
	int minArea(vector <int> moves) {
		int n = moves.size();
		x = xl = xr = y = yl = yr = 100; // starting at (100, 100)
		memset(A, 0, sizeof A); A[x][y] = 1;
		for (int i = 0; i < n; ++i){
			int d = i % 4; // direction
			// move the bot
			for (int j = 0; j < moves[i]; ++j){
				x += dx[d]; y += dy[d]; 
				if (A[x][y]) return -1; 
				A[x][y] = 1;
				if (x > xr) xr = x;
				if (x < xl) xl = x;
				if (y > yr) yr = y;
				if (y < yl) yl = y;
			}
			if (i < n - 1){
				int tx = x + dx[d], ty = y + dy[d]; // the next cell
				if (!A[tx][ty]){
					// assume this cell is out of the grid
					if (d & 1)
						for (int j = 0; j < 255; ++j){
							if (A[tx][j] > 0) return -1; // conflict with the move before 
							A[tx][j] = -1; // mark the border
						}
					else
						for (int j = 0; j < 255; ++j){
							if (A[j][ty] > 0) return -1;
							A[j][ty] = -1;
						}
				}
			}
		}
		return (xr - xl + 1) * (yr - yl + 1);
	}
};

/*
	'TATOE sekai azamuku kotae da toshitemo
	shinjite sashidasu tenohira'
		- Ai no Scenario
*/
