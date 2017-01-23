#include <cstdio>
#include <vector>
using namespace std;
const int dx[4] = {0, -1, 0, 1}, dy[4] = {1, 0, -1, 0};

bool vis[55][55];
class RotatingBot{
	public:
		int minArea(vector <int> moves){
			int n = moves.size(), i, w, h, j, r, c;
			if(n == 1) return moves[0] + 1;
			for(i = 2, w = moves[0] + 1, h = moves[1] + 1; i < n; i += 2){
				w = max(w, moves[i] + 1);
				if(i < n - 1) h = max(h, moves[i + 1] + 1);
			} r = moves[1] + 1, c = w - moves[0];
			for(i = 0; i < n; ++ i){
				for(j = 1; j <= moves[i]; ++ j){
					vis[r][c] = true;
					r += dx[i & 3], c += dy[i & 3];
					if(r < 1 || c < 1 || r > h || c > w || vis[r][c])
						return -1;
				} vis[r][c] = true;
				if(i != n - 1){
					r += dx[i & 3], c += dy[i & 3];
					if(!(r < 1 || c < 1 || r > h || c > w || vis[r][c]))
						return -1;
					r -= dx[i & 3], c -= dy[i & 3];
				}
			} return w * h;
		}
};
