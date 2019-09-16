import random

"""implementation of graph structure
"""

class Graph(object):
    def __init__(self, m):
        self.adjlist = [None] * m
        for _ in xrange(m):
            self.adjlist[_] = []
    
    def addEdge(self, v, w):
        self.adjlist[v].insert(0, w)

    def adj(self, v):
        """return list of vertices that are adjacent to this 'v' vertex
        """
        return self.adjlist[v]

    def __str__(self):
        s = ''
        for iv in xrange(len(self.adjlist)):
            if self.adjlist[iv]:
                s += '{}: {}\n'.format(iv, self.adjlist[iv])
        return s

if __name__ == '__main__':
    lst = [random.randint(0, 100) for _ in xrange(20)]
    #lst = [10, 20, 30, 40, 50, 45, ]
    print '>>random list:\n{}'.format(lst)

    g = Graph(101)
    edges = [(random.randint(0, 100), random.randint(0, 100)) for _ in xrange(10)]
    edges = [(16, 93), (87, 9), (14, 23), (73, 24), (79, 33), (66, 82), (36, 31), (17, 29), (92, 65), (77, 89)]
    print '>>edges:\n{}'.format(edges)
    map(lambda (v,w): g.addEdge(v, w), edges)

    print '>>graph:\n{}'.format(g)