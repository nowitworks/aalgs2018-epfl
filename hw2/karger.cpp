#include <iostream>
#include <vector>

struct subset {
  int parent;
  int rank;
};

class sets {
  std::vector<subset> _subsets;
public:
  sets(int n) {
    for (int i = 0; i < n; i++) {
      _subsets[i].parent = i;
      _subsets[i].rank = 0;
    }
  }

  int rank(int x) const {
    return _subsets[x].rank;
  }

  void rank(int x, int r) {
    _subsets[x].rank = r;
  }

  int parent(int x) const {
    return _subsets[x].parent;
  }

  void parent(int x, int p) {
    _subsets[x].parent = p;
  }

  void set_union(int x, int y) {
    x = find(x);
    y = find(y);

    if (rank(x) == rank(y)) {
      parent(y, x);
    } else {
      parent(x, y);
        if (rank(x) == rank(y)) {
          rank(y, rank(y) + 1);
        }
    }
  }

  int find(int x) {
    if (x != parent(x)) {
      parent(x, find(parent(x)));
    }

    return parent(x);
  }
};

struct spec {
  int n, m;

  // Edges
  std::vector<int> src;
  std::vector<int> dst;

  spec() {
    std::cin >> n;
    std::cin >> m;

    src.reserve(m);
    dst.reserve(m);

    for (int i = 0; i < m; i++) {
      std::cin >> src[i];
      std::cin >> dst[i];
    }
  }
};

int main () {
  spec s;

  std::cout << s.n << " " << s.m << "\n";

  for (int i = 0; i < s.m; i++) {
    std::cout << "(" << s.src[i] << "," << s.dst[i] << ")";
  }

  std::cout << std::endl;
  return 0;
}
