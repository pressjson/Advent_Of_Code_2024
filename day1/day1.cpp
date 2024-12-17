#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {

  // part 1
  std::ifstream inFile;
  std::vector<int> col_1 = {};
  std::vector<int> col_2 = {};

  inFile.open("day1.txt");
  std::string line = "";
  bool is_col_1 = true;

  // get ints
  while (std::getline(inFile, line, ' ')) {
    try {
      int num = std::stoi(line);
      // std::cout << line << " | " << num << std::endl;
      if (is_col_1) {
        col_1.push_back(num);
      } else {
        col_2.push_back(num);
      }
      is_col_1 = !is_col_1;
    } catch (std::exception) {
      // std::cout << "Warning: input for stoi is " << line << std::endl;
    }
  }

  // sort lists

  std::sort(col_1.begin(), col_1.end());
  std::sort(col_2.begin(), col_2.end());

  int sum_of_diffs = 0;
  for (int i = 0; i < col_1.size(); ++i) {
    sum_of_diffs += std::abs(col_2[i] - col_1[i]);
  }

  std::cout << "Sum of differences is " << sum_of_diffs << std::endl;

  // part 2

  int similarity_score = 0;
  for (int i = 0; i < col_1.size(); ++i) {
    int appearances = 0;
    for (int j : col_2) {
      if (j == col_1[i])
        appearances++;
    }
    // std::cout << col_1[i] << " * " << appearances << std::endl;
    similarity_score += std::abs(col_1[i] * appearances);
  }

  std::cout << "Similarity score is " << similarity_score << std::endl;

  inFile.close();
  return 0;
}
