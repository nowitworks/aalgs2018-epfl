package karger

class Node(id: Int) {
  var parent = this
  var rank = 0

  def findSet(): Node = {
    if (this != parent) {
      parent = parent.findSet()
    }

    parent
  }

  def ++(y: Node) {
    Node.link(this.findSet(), y.findSet())
  }

  def +(y: Int) {
    this ++ new Node(y)
  }

  override def toString: String = "Node(" + id + ")"
}

object Node {
  def link(x: Node, y: Node) {
    if (x.rank > y.rank) {
      y.parent = x
    } else {
      x.parent = y
      if (x.rank == y.rank) {
        y.rank += 1
      }
    }
  }
}

object App {
  // Problem: this was not really running multiple times.
  // Idea: Divide responsibilities cleanly into a Spec and a Solver, so that we
  // can run the Solver multiple times on the same Spec

  def main(args: Array[String]): Unit = {
    def read = readLine.split(" ").map(_.toInt)

    val Array(n, m) = read

    val vertices = for (i <- 1 to n) yield new Node(i)
    val edges = scala.util.Random.shuffle {
      for (i <- 1 to m) yield {
        val Array(u, v) = read
        (vertices(u - 1), vertices(v - 1))
      }
    }

    for ((u, v) <- edges.take(n - 2); if u.findSet() != v.findSet()) {
      u ++ v
    }

    val cut = edges.drop(n - 2).filter((x: (Node, Node)) => x._1.findSet() != x._2.findSet())
    println(cut.size)
  }
}

