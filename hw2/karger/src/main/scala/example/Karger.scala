import scala.collection.mutable.HashSet

object Karger extends App {
  val spec = new Spec()
  val n = spec.n
  val times = n * n * math.ceil(math.log(n)).toInt // O(n^2 * log(n))

  val cuts: HashSet[Set[(Int, Int)]] = HashSet()

  for (_ <- 1 to times) {
    val solver = new Solver(spec)
    val cut = solver.run()

    cuts += cut
  }

  val minSize = cuts.minBy(_.size).size
  val count   = cuts.count(_.size == minSize)

  println(minSize + " " + count)
}

// Union-find
class Node(val id: Int) {
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

class Spec {
  def read = io.StdIn.readLine.split(" ").map(_.toInt)

  val Array(n, m) = read
  val edges = for (_ <- 1 to m) yield {
    val Array(u, v) = read
    (u, v)
  }
}

class Solver(spec: Spec) {
  val vertices = for (i <- 1 to spec.n) yield new Node(i)

  var edges = for ((u, v) <- spec.edges.toList) yield {
    (vertices(u - 1), vertices(v - 1))
  }

  def run(): Set[(Int, Int)] = {
    for (_ <- 1 to spec.n - 2) {
      val (u, v) = pickEdge()
      u ++ v
      removeLoops()
    }

    edges.map(x => (x._1.id, x._2.id)).toSet
  }

  private def pickEdge(): (Node, Node) = {
    val probabilities = List.tabulate(spec.m) { (x: Int) => 1.0 / (x + 1.0) }
    val dummy = (new Node(0), new Node(0))

    edges.zip(probabilities).foldLeft(dummy) {
      case (z, (e, p)) => if (util.Random.nextDouble() <= p) e else z
    }
  }

  private def removeLoops() {
    edges = edges filter {
      x => x._1.findSet() != x._2.findSet()
    }
  }

}

