#include <vector>

class RotatingBot {
  public:
    int minArea(std::vector<int> moves);

  private:
    bool checkBottomLeftCorner(const std::vector<int> &moves);
    bool checkBottomRow(const std::vector<int> &moves);
    bool checkAny(const std::vector<int> &moves);
    bool checkAlt(int x, int y, const std::vector<int> &a);
};

int RotatingBot::minArea(std::vector<int> moves)
{
    if (moves.size() == 1) {
        // (moves[0] + 1) x 1 board, starting at the left end
        return moves[0] + 1;
    } else if (checkBottomLeftCorner(moves)) {
        // (moves[0] + 1) x (moves[1] + 1) board, starting at the
        // bottom-left corner
        return (moves[0] + 1) * (moves[1] + 1);
    } else if (moves.size() >= 3 && checkBottomRow(moves)) {
        // (moves[2] + 1) x (moves[1] + 1) board, starting in the bottom
        // row but not at the bottom-left corner
        return (moves[2] + 1) * (moves[1] + 1);
    } else if (moves.size() >= 4 && checkAny(moves)) {
        // (moves[2] + 1) x (moves[3] + 1) board, starting anywhere
        // other than the bottom row
        return (moves[2] + 1) * (moves[3] + 1);
    } else {
        return -1;
    }
}

bool RotatingBot::checkBottomLeftCorner(const std::vector<int> &moves)
{
    return checkAlt(moves[1], moves[0], std::vector<int>(moves.begin() + 1, moves.end()));
}

bool RotatingBot::checkBottomRow(const std::vector<int> &moves)
{
    return moves[0] < moves[2] && checkAlt(moves[1], moves[2] - moves[0] - 1, std::vector<int>(moves.begin() + 3, moves.end()));
}

bool RotatingBot::checkAny(const std::vector<int> &moves)
{
    return moves[0] < moves[2] && moves[1] < moves[3] && checkAlt(moves[2], moves[3] - moves[1] - 1, std::vector<int>(moves.begin() + 4, moves.end()));
}

bool RotatingBot::checkAlt(int x, int y, const std::vector<int> &a)
{
    for (int i = 0; i < (int)a.size(); i++) {
        int u = (i % 2 ? y : x) - i / 2;
        if (i < (int)a.size() - 1 ? a[i] != u : a[i] > u) {
            return false;
        }
    }
    return true;
}
