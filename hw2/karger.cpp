#include <iostream>
#include <memory>

#include <cassert>

template <typename T>
class set {
public:
  set(T x): _tag(x), _rank(0) {
    _parent = std::make_shared(this);
  }

  T &parent() const {
    return *_parent;
  }

  int rank() const {
    return _rank;
  }

  void link(set &that) {
    if (this->rank() > that->rank()) {
      that->parent(this);
    } else {
      this->parent(that);

      if (this->rank() == that->rank()) {
        that.inc_rank();
      }
    }
  }

  void set_union(set &that) {
    find_set(this).link(find_set(that));
  }

  set &find_set() const {
    if (this != parent()) {
      parent(parent()->find_set());
    }
    return parent();
  }

private:
  T _tag;
  std::shared_ptr<set> _parent;
  int _rank;

  void parent(T &p) {
    this->_parent = std::make_shared<T>(p);
  }

  void inc_rank() {
    _rank++;
  }

};

int main () {
  // int nedges, nvertices;

  // std::cin >> nvertices;
  // std::cin >> nedges;


  // std::cout << nvertices << nedges << std::endl;

  set<int> s1(0);
  set<int> s2(1);



  return 0;
}
