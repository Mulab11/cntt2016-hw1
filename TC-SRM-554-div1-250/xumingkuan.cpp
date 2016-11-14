class TheBrickTowerEasyDivOne
{
	public:
	int find(int redCount, int redHeight, int blueCount, int blueHeight)
	{
		return min(redCount, blueCount) * (2 + (redHeight != blueHeight)) + (redCount != blueCount);//For each number x <= min(redCount, blueCount) of red/blue bricks: (x red, x blue), (x red, x-1 blue), (x-1 red, x blue); that's (2 + (redHeight != blueHeight)) towers. And if (redCount != blueCount), we have 1 more tower with (min(redCount, blueCount) * 2 + 1) bricks.
	}
};

