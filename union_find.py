import random

"""implementation of data structure that support quick union-find operations
"""

class DisjointSet(object):
    def __init__(self, num):
        """each slot records the parent of current location
        negative value for root means minus of height of joint tree
        """
        self.data = [-1] * num

    def union(self, k1, k2):
        """union by height"""
        print '>>union ({}, {})'.format(k1, k2)
        if k1 == k2: return
        r1 = self.find(k1)
        r2 = self.find(k2)
        if r1 == r2: return
        """shadow tree attaches to deeper tree"""
        if -self.data[r1] > -self.data[r2]: # r1 tree is deeper
            self.data[r2] = r1
        else:
            if self.data[r1] == self.data[r2]: # same height
                self.data[r2] -= 1
            self.data[r1] = r2

        print self

    def find(self, k):
        """find the root where 'k' resides in"""
        if k < 0 or k >= len(self.data): return None
        if self.data[k] < 0:
            return k
        else:
            """path compression
            all traversed nodes will be assigned the root directly
            """
            self.data[k] = self.find(self.data[k])
            return self.data[k]

    def __str__(self):
        d = dict()
        for i in xrange(len(self.data)):
            r = self.find(i)
            if r not in d: d[r] = []
            d[r].append(i)
        import pprint
        return pprint.pformat(d)

if __name__ == '__main__':
    lst = [random.randint(0, 19) for _ in xrange(20)]
    print '>>random list:\n{}'.format(lst)

    ds = DisjointSet(20)
    i = 0
    while i < 10:
        ds.union(random.choice(lst), random.choice(lst))
        i += 1
    print '>>ds\n{}'.format(ds)

    print '>>bunch of finds'
    for x in [random.randint(0, 50) for _ in xrange(20)]:
        print '>>find {} => {}'.format(x, ds.find(x))
    print '>>ds\n{}'.format(ds)