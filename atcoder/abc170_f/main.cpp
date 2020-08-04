// AFTER EDITORIAL

//
// NOTE: Culling all the rest when "d_old < d" was crutial
//

#include <bits/stdc++.h>

using namespace std;

int main() {
  // Input
  int h, w, k;
  int x1, y1, x2, y2;
  cin >> h >> w >> k;
  cin >> x1 >> y1 >> x2 >> y2;
  x1--; y1--; x2--; y2--;  // Zero-based index

  vector<bool> field(h * w, 0);
  auto __ = [&](int i, int j) { return i * w + j; };
  char c;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cin >> c;
      field[__(i, j)] = c == '.';
    }
  }
  #ifdef DEBUG
    for (auto x : field) {
      printf("%s", x ? "." : "@");
    }
    puts("");
  #endif

  // Admissible heuristics
  auto heuristics = [&](int x, int y) {
    return (abs(x2 - x) + (k - 1)) / k + (abs(y2 - y) + (k - 1)) / k;
  };
  // Consistent heuristics (with floating point)
  // auto heuristics = [&](int x, int y) {
  //   return (abs(x2 - x) + abs(y2 - y)) / (double)k;
  // };

  // Define A* star search queue
  // [ min-heap ]
  // using pq_v_t = tuple<int, int, int>;
  // using pq_c_t = vector<pq_v_t>;
  // priority_queue<pq_v_t, pq_c_t, std::greater<pq_v_t>> pq; // "greater" for min-heap

  // [ Balanced tree for "decrease-key" ]
  set<tuple<int, int, int>> pq;

  // Initialize
  vector<int> distance(h * w, -1);
  distance[__(x1, y1)] = 0;
  // pq.push({heuristics(x1, y1), x1, y1}); // MIN HEAP
  pq.insert({heuristics(x1, y1), x1, y1}); // BALANCED TREE

  // Iterate search
  int result = -1;
  while (!pq.empty()) {
    // auto [score, x, y] = pq.top(); // MIN HEAP
    // pq.pop();                      // MIN HEAP
    auto top = pq.begin();     // BALANCED TREE
    auto [score, x, y] = *top; // BALANCED TREE
    pq.erase(top);             // BALANCED TREE

    #if DEBUG >= 2
      printf("(%d, %d) [%d]\n", x, y, score);
    #endif

    if (x == x2 && y == y2) {
      result = score;
      break;
    }
    auto d = distance[__(x, y)] + 1;
    constexpr tuple<int, int> dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto [dir_x, dir_y] : dirs) {
      for (int i = 1; i <= k; i++) {
        int xx = x + dir_x * i;
        int yy = y + dir_y * i;
        // Check boundaries
        if (xx < 0 || xx >= h || yy < 0 || yy >= w) {
          break;
        }
        // Check obstacles
        if (!field[__(xx, yy)]) {
          break;
        }
        int d_old = distance[__(xx, yy)];
        if (d_old != -1 && d_old < d) {
          // NOTE: AFTER EDITORIAL
          // Cull all the rest if old path is shorter
          break;
        }
        if (d_old != -1 && d_old == d) {
          continue;
        }
        distance[__(xx, yy)] = d;
        #ifdef DEBUG
          printf("(%d, %d) => (%d, %d) [%d]\n", x, y, xx, yy, d);
        #endif

        int heu = heuristics(xx, yy);
        // pq.push({d + heu, xx, yy}); // MIN HEAP
        pq.erase({d_old + heu, xx, yy}); // BALANCED TREE
        pq.insert({d + heu, xx, yy});    // BALANCED TREE
      }
    }
  }

  // Output
  cout << result << endl;
  return 0;
}

/*
python misc/run.py atcoder/abc170_f/main.cpp --check

%%%% begin
3 5 2
3 2 3 4
.....
.@..@
..@..
%%%%
5
%%%% end

%%%% begin
1 6 4
1 1 1 6
......
%%%%
2
%%%% end

%%%% begin
3 3 1
2 1 2 3
.@.
.@.
.@.
%%%%
-1
%%%% end
*/
