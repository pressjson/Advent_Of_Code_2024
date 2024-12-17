#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int LOWER_BOUND = 1;
int UPPER_BOUND = 3;

int is_safe_level(vector<int> &level) {

  bool is_ascending = level[0] <= level[1];
  for (int i = 0; i < level.size() - 1; ++i) {

    int difference = level[i + 1] - level[i];
    if (!is_ascending)
      difference *= -1;
    if (!(LOWER_BOUND <= difference && difference <= UPPER_BOUND)) {
      return i;
    }
  }

  return -1;
}

void print(vector<int> &vec) {
  string str = "<";
  for (int i = 0; i < vec.size() - 1; ++i) {
    str += to_string(vec[i]) + ", ";
  }
  str += to_string(vec[vec.size() - 1]) + ">";
  cout << str << endl;
}

int main() {
  ifstream file;
  file.open("day2.txt");
  string line;

  int num_safe_levels = 0;
  int dampened_safe = 0;

  while (getline(file, line)) {
    // get nums from line
    int report = 0;
    vector<int> level;
    for (char c : line) {
      int i = c - '0';
      if (0 <= i && i <= 9) {
        report = 10 * report + i;
      } else {
        level.push_back(report);
        report = 0;
      }
    }
    level.push_back(report);
    // print(level);
    if (level.size() <= 1)
      continue;

    const int is_safe = is_safe_level(level);
    if (is_safe == -1) {
      num_safe_levels++;
      dampened_safe++;
    } else {
      // part 2
      vector<int> remove_i, remove_next;
      for (int i = 0; i < level.size(); ++i) {
        if (i != is_safe)
          remove_i.push_back(level[i]);
      }
      for (int i = 0; i < level.size(); ++i) {
        if (i + 1 != is_safe)
          remove_next.push_back(level[i + 1]);
      }
      cout << is_safe << endl;
      print(level);
      print(remove_i);
      print(remove_next);

      if (is_safe_level(remove_next) || is_safe_level(remove_next))
        dampened_safe++;
      cout << dampened_safe << endl;
    }
  }

  cout << num_safe_levels << endl;
  cout << dampened_safe << endl;

  return 0;
}
