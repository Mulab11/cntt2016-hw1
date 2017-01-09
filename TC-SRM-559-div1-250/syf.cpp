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

class	HyperKnight{
	public:

	long countCells(int a, int b, int numRows, int numColumns, int k)
{
    // The 8 moves available:
    long dx[8] = {a,a,-a,-a,b,b,-b,-b};
    long dy[8] = {b,-b,b,-b,a,-a,a,-a};
    
    long exactly[256];
    long result = 0;
    
    // We visit the masks from highest to smallest, this way we
    // can guarantee that all subsets with more elements than the
    // current one have already been solved.
    for (int mask = 255; mask >= 0; mask--) {
        long valid = 0;
        // valid : How many cells allow the moves in mask?
        // (and possibly other moves)
        
        // In the explanation valid is an array, but we do not really
        // need to remember all its values, just valid[mask].
        
        int n = 0;
        // Find the rectangle of such cells:
        long left = 0, right = 0, up = 0, down = 0;
        for (int i=0; i<8; i++) {
            // For each move that belongs to the mask subset:
            if (mask & (1<<i)) {
                n++;
                // update the rectangle's dimensions
                if (dx[i] < 0) {
                    left = std::max(left, -dx[i]);
                } else {
                    right = std::max(right, dx[i]);
                }
                if (dy[i] < 0) {
                    up = std::max(up, -dy[i]);
                } else {
                    down = std::max(down, dy[i]);
                }
            }

        }
        // Area of the rectangle
        valid = (numRows - left - right) * (numColumns - up - down);
        // if we make sure to set valid = 0 when the moves are too large
        // this makes the solution work even without the special constraint
        
        exactly[mask] = valid;
        
        // For each subset with more elements than this one.
        // (mask must be a proper subset of mask2):
        for (int mask2 = mask + 1; mask2 < 256; mask2++) {
            if ( (mask & mask2) == mask ) {
                // remove the cells that allow more moves than mask.
                exactly[mask] -= exactly[mask2];
            }
        }
        // n is the number of moves in the mask.
        // now exactly[mask] contains the number of cells from which the ONLY
        // valid moves are those in the mask:
        if (n == k) {
            result += exactly[mask];
        }
    }
    return result;
}	
	
};