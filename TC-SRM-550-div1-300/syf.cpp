//============================================================================
// Author       : Sun YaoFeng
//============================================================================

//#pragma 	comment(linker, "/STACK:100240000,100240000")
//#include	<cstdio>
//#include	<cstdlib>
//#include	<cstring>
//#include	<algorithm>

#include	<bits/stdc++.h>

using	namespace	std;

#define DB		double
#define	lf		else if
#define I64		long long
#define	Rd()	(rand()<<15|rand())
#define For(i,a,b)	for(int i=a,lim=b;i<=lim;i++)
#define Rep(i,a,b)	for(int i=a,lim=b;i>=lim;i--)

#define	fi	first
#define se	second
#define MK	make_pair
#define PA	pair<int, int>

//#define	min(a,b)	((a)<(b)?(a):(b))
//#define	max(a,b)	((a)<(b)?(b):(a))

#define	CH	(ch=getchar())
int		IN()	{
		int x= 0, f= 0, ch;
		for	(; CH < '0' || ch > '9';)	f= (ch == '-');
		for	(; ch >= '0' && ch <= '9'; CH)	x= x*10 + ch -'0';
		return	f? -x : x;
}

class	RotatingBot{
	public:
int minArea(vector <int> moves)
{
    // We will use point (100, 100) as the center of the simulation.
    // with a 200x200 grid, there will be more than enough cells at
    // every direction to perform a good simulation.

    // initialize the record of visited cells:        
    bool used[200][200];
    int x = 100, y = 100;
    memset(used,0, sizeof(used));
    used[x][y] = true;
    
    // Use the minimum and maximum coordinates to find the rectangle
    // with the minimum dimensions.
    int minx = x, maxx = x, miny = y, maxy = y;
    int d = 0;
    // Each direction, east, north, west, south, increase or
    // decrease each coordinate differently. It simplifies
    // our task to encode them in these vectors:
    int dx[4] = {1,0,-1,0};
    int dy[4] = {0,-1,0,1};

    // A counter-clockwise rotation in direction is the
    // same as increasing the index of the direction by 1
    // unless the current direction is 3, then we need to
    // return back to direction 0.
    
    // 1) First simulation, make sure we never visit the same
    //    cell twice, find the minimum rectangle.
    int totalSteps = 0;
    for (int i=0; i<moves.size(); i++) {
        for (int j=0; j<moves[i]; j++) {
            totalSteps++;
            int nx = x + dx[d];
            int ny = y + dy[d];
            //if we visited it before, it is invalid
            if ( used[nx][ny] ) {
                return -1;
            }
            // move:
            x = nx;
            y = ny;
            minx = std::min(minx, x);
            miny = std::min(miny, y);
            maxx = std::max(maxx, x);
            maxy = std::max(maxy, y);
            used[x][y] = true;
        }
        // rotate:
        d = (d+1) % 4;
    }
    // 2) Now that we have the borders of the minimum rectangle,
    //   simulate again, making sure the moves[] array we generate
    //   is the same as the one in the return value.
    d = 0;
    x = 100, y = 100;
    memset(used, 0, sizeof(used));
    used[x][y] = true;
    vector<int> moves2;
    
    int m = 0; // current amount of steps made in the current direction
    int i = 0;
    while (i < totalSteps) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if ( used[nx][ny] || nx < minx || nx > maxx || ny < miny || ny > maxy ) {
            // save moves:
            moves2.push_back(m);
            //rotate
            m = 0;
            d = (d + 1) % 4;
            nx = x + dx[d];
            ny = y + dy[d];
            if ( used[nx][ny] || nx < minx || nx > maxx || ny < miny || ny > maxy ) {
                // again?
                // must end
                break;
            }
        } else {
            // advance, mark cell as visited
            x = nx;
            y = ny;
            used[nx][ny] = true;
            m ++;
            i++; //we moved a step
        }
    }
    // add the last set of steps (if they exist):
    if (m != 0) {
        moves2.push_back(m);
    }

    if (moves2 != moves) {
        return -1;
    }        
    // all is correct, return the minimum area:
    return (maxx - minx + 1) * (maxy - miny + 1);

}
};