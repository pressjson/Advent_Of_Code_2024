#include <algorithm>
#include <climits>
#include <csignal>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int MOVE_FORWARD = 1;
const int ROTATE = 1000;
map<int, int> used_indexes;
map<int, int> trace_score;

void print_maze(const vector<vector<char>> maze) {
  // for (auto i : maze) {
  //   for (auto j : i) {
  //     cout << j;
  //   }
  //   cout << endl;
  // }
  int i, j = 0;
  while (i < maze.size()) {
    while (j < maze[0].size()) {
      cout << maze[i][j];
      j++;
    }
    cout << endl;
    j = 0;
    i++;
  }
  cerr << "find_start: could not find start character!" << endl;
  raise(1);
}

int my_min(int a, int b, int c) { return min({a, b, c}); }

void find_start(const vector<vector<char>> &maze, int &i, int &j) {
  // update i and j to be the start pos
  while (i < maze.size()) {
    while (j < maze[i].size()) {
      // cout << "(" << i << ", " << j << ") = " << maze[i][j] << endl;
      if (maze[i][j] == 'S') {
        return;
      }
      j++;
    }
    j = 0;
    i++;
  }
  cerr << "find_start: could not find start character!" << endl;
  raise(1);
}

int score(vector<vector<char>> &maze, int i, int j, int previous,
          const char dir, vector<int> &prev_trace) {
  if (!(0 <= i && i < maze.size()) || !(0 <= j && j <= maze[0].size())) {
    cerr << "score: i, j = " << i << ", " << j << " out of bounds" << endl;
    return -2;
  }
  int current_location = i * maze[0].size() + j;

  if (maze[i][j] == 'E') {
    cout << "E at (" << i << ", " << j << ") with score " << previous << endl;

    used_indexes[current_location] = previous;
    for (int location : prev_trace) {
      if (trace_score[location] == 0)
        trace_score[location] = previous;
      else
        trace_score[location] = min(trace_score[location], previous);
    }
    return previous;
  }
  if (maze[i][j] == '#') {
    return INT_MAX;
  }
  if (used_indexes[current_location] < previous &&
      used_indexes[current_location] != 0) {
    return INT_MAX;
  }
  // cout << previous << endl;
  used_indexes[current_location] = previous;

  int forward_score = previous + MOVE_FORWARD;
  int rotate_score = previous + MOVE_FORWARD + ROTATE;

  auto trace = prev_trace;
  trace.push_back(current_location);

  switch (dir) {
  case 'u':
    return my_min(score(maze, i + 1, j, forward_score, 'u', trace),
                  score(maze, i, j + 1, rotate_score, 'r', trace),
                  score(maze, i, j - 1, rotate_score, 'l', trace));
  case 'r':
    return my_min(score(maze, i, j + 1, forward_score, 'r', trace),
                  score(maze, i + 1, j, rotate_score, 'u', trace),
                  score(maze, i - 1, j, rotate_score, 'd', trace));
  case 'l':
    return my_min(score(maze, i, j - 1, forward_score, 'l', trace),
                  score(maze, i - 1, j, rotate_score, 'd', trace),
                  score(maze, i + 1, j, rotate_score, 'u', trace));
  case 'd':
    return my_min(score(maze, i - 1, j, forward_score, 'd', trace),
                  score(maze, i, j - 1, rotate_score, 'l', trace),
                  score(maze, i, j + 1, rotate_score, 'r', trace));
  }
  return -1;
}

int main() {
  // load file
  ifstream infile;
  infile.open("example.txt");
  string line;
  vector<vector<char>> maze;
  int height_of_maze = 0;
  while (getline(infile, line)) {
    vector<char> row(line.begin(), line.end());
    maze.push_back(row);
  }

  int i, j, min_score = 0;
  // print_maze(maze);
  find_start(maze, i, j);
  vector<int> trace;

  cout << "Calculating score, starting at (" << i << ", " << j << ")" << endl;
  min_score = score(maze, i, j, 0, 'r', trace);

  cout << "Min score = " << min_score << endl;
  int num_unique_locations = 0;
  for (auto traverser = trace_score.begin(); traverser != trace_score.end();
       traverser++) {
    if (traverser->second == min_score)
      num_unique_locations++;
  }

  // idk why + 1

  cout << "Num unique locations = " << num_unique_locations + 1 << endl;

  return 0;
}
