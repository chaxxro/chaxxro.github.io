#include "data_structure.h"

class Solution {
public:
};

int main() {
  std::cout << std::boolalpha;
  auto helper = [](vector<char> ch, char t) {
    Solution ss;
    print_data(ss.nextGreatestLetter(ch, t));
  };
  helper({'e','e','e','e','e','e','n','n','n','n'}, 'a');
  return 0;
}
