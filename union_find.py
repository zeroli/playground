import random

"""implementation of data structure that support quick union-find operations
"""

class DisjointSet(object):
    def __init__(self, num):
        self.data = [-1] * num
        """each slot records the parent of current location"""

    def union(self, k1, k2):
        print '>>union ({}, {})'.format(k1, k2)
        if k1 == k2: return
        r1 = self.find(k1)
        r2 = self.find(k2)
        if r1 == r2: return
        self.data[r2] = r1
        print self

    def find(self, k1):
        """find the root where 'k1' resides in"""
        if self.data[k1] < 0:
            return k1
        else:
            return self.find(self.data[k1])

    def __str__(self):
        s = ','.join([str(d) for d in self.data])
        return s

if __name__ == '__main__':
    lst = [random.randint(0, 9) for _ in xrange(20)]
    print '>>random list:\n{}'.format(lst)

    ds = DisjointSet(10)
    i = 0
    while i < 10:
        ds.union(random.choice(lst), random.choice(lst))
        i += 1
    print '>> ds \n{}'.format(ds)
