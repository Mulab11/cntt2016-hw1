#include <string>
#include <vector>

class FoxAndMp3 {
  public:
    std::vector<std::string> playList(int n);

  private:
    static const int MAXOUT = 50;
};

std::vector<std::string> FoxAndMp3::playList(int n)
{
    std::vector<std::string> ans;
    int cur = 1;
    for (int i = 0; i < MAXOUT; i++) {
        ans.push_back(std::to_string(cur) + ".mp3");
        if (cur * 10 <= n) {
            // Append '0' to the number
            cur *= 10;
        } else {
            while (cur % 10 == 9 || cur == n) {
                cur /= 10;
            }
            if (cur == 0) {
                break;
            }
            // Increment last digit
            cur++;
        }
    }
    return ans;
}
