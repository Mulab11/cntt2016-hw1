class TheBrickTowerEasyDivOne
{
	int min(int a, int b) {return a < b ? a : b;}
	int max(int a, int b) {return a > b ? a : b;}
public:
	int find(int rc, int rv, int bc, int bv)
	{
		// 两个的个数只能差 1
		if(rv == bv) return max(min(rc, bc) * 2, max(min(rc, bc - 1), min(rc - 1, bc)) * 2 + 1);
		return min(rc, bc) + min(rc, bc - 1) + min(rc - 1, bc) + 2;
	}
}	user;