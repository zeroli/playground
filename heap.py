import sys
import random

"""implement min/max heap
"""

class MinHeap(object):
    def __init__(self, lst=None):
        # leave first slot as empty/sentinel
        #index starts from 1
        self.data = [-sys.maxint - 1]
        self.data.extend(lst if lst else [])
        self.n = len(lst) if lst else 0
        self._build()

    def _build(self):
        i = self.n / 2
        while i > 0:
            self._percolateDown(i)
            #print self.data[1:]
            i -= 1

    def _percolateDown(self, k):
        while k <= self.n / 2:
            child = k * 2
            if child < self.n and self.data[child+1] < self.data[child]:
                child += 1
            if self.data[child] < self.data[k]:
                self.data[k], self.data[child] = self.data[child], self.data[k]
                k = child
            else:
                break

    def _percolateUp(self, k):
        while k / 2 > 0:
            parent = k / 2
            if self.data[parent] > self.data[k]:
                self.data[parent], self.data[k] = self.data[k], self.data[parent]
                k = parent
            else:
                break

    def insert(self, key):
        self.n += 1
        self.data.append(key)
        self._percolateUp(self.n)

    def deleteMin(self):
        if self.n == 0: return None
        minv = self.data[1]

        d = self.data[self.n]
        self.n -= 1
        self.data.pop()
        if self.n == 0: return minv

        self.data[1] = d
        self._percolateDown(1)
        return minv

    def peek(self):
        if self.n == 0: return None
        return self.data[1]

    def __str__(self):
        from collections import deque
        if self.n == 0: return '<EMPTY>'
        s = []
        q = deque()
        q.append(1)
        q.append(None) # special element to identify level ending
        ilevel = 0
        levelstr = []
        while len(q):
            node = q.popleft()
            if node:
                levelstr.append(str(self.data[node]))
                if node * 2 <= self.n:
                    q.append(node * 2)
                if node * 2 + 1 <= self.n:
                    q.append(node * 2 + 1)
            else:
                s.append('L{}: {}'.format(ilevel, ' '.join(levelstr)))
                ilevel += 1
                levelstr = []
                if len(q): q.append(None)
        return '\n'.join(s)

class MaxHeap(object):
    def __init__(self, lst=None):
        # leave first slot as empty/sentinel
        #index starts from 1
        self.data = [sys.maxint]
        self.data.extend(lst if lst else [])
        self.n = len(lst) if lst else 0
        self._build()

    def _build(self):
        i = self.n / 2
        while i > 0:
            self._percolateDown(i)
            #print self.data[1:]
            i -= 1

    def _percolateDown(self, k):
        while k <= self.n / 2:
            child = k * 2
            if child < self.n and self.data[child+1] > self.data[child]:
                child += 1
            if self.data[child] > self.data[k]:
                self.data[k], self.data[child] = self.data[child], self.data[k]
                k = child
            else:
                break

    def _percolateUp(self, k):
        while k / 2 > 0:
            parent = k / 2
            if self.data[parent] < self.data[k]:
                self.data[parent], self.data[k] = self.data[k], self.data[parent]
                k = parent
            else:
                break

    def insert(self, key):
        self.n += 1
        self.data.append(key)
        self._percolateUp(self.n)

    def deleteMax(self):
        if self.n == 0: return None
        maxv = self.data[1]

        d = self.data[self.n]
        self.n -= 1
        self.data.pop()
        if self.n == 0: return maxv

        self.data[1] = d
        self._percolateDown(1)
        return maxv

    def peek(self):
        if self.n == 0: return None
        return self.data[1]

    def __str__(self):
        from collections import deque
        if self.n == 0: return '<EMPTY>'
        s = []
        q = deque()
        q.append(1)
        q.append(None) # special element to identify level ending
        ilevel = 0
        levelstr = []
        while len(q):
            node = q.popleft()
            if node:
                levelstr.append(str(self.data[node]))
                if node * 2 <= self.n:
                    q.append(node * 2)
                if node * 2 + 1 <= self.n:
                    q.append(node * 2 + 1)
            else:
                s.append('L{}: {}'.format(ilevel, ' '.join(levelstr)))
                ilevel += 1
                levelstr = []
                if len(q): q.append(None)
        return '\n'.join(s)

if __name__ == '__main__':
    #lst = [random.randint(0, 100) for _ in xrange(20)]
    lst = [23, 56, 95, 84, 1, 48, 84, 28, 26, 0, 29, 42, 33, 81, 90, 64, 68, 21, 36, 89]
    print '>>random list:\n{}'.format(lst)
    minh = MinHeap(lst)
    print 'min heap structure:\n{}'.format(minh)

    minvalues = []
    while True:
        minv = minh.deleteMin()
        if minv == None: break
        print 'delete minval: {}, min heap structure:\n{}'.format(minv, minh)
        minvalues.append(minv)
    assert minvalues == sorted(lst), 'ERROR: {} != {}'.format(minvalues, sorted(lst))

    map(lambda x: minh.insert(x), lst)
    print 'min heap structure:\n{}'.format(minh)

    maxh = MaxHeap()
    map(lambda x: maxh.insert(x), lst)
    print 'max heap structure:\n{}'.format(maxh)
    maxvalues = []
    while True:
        maxv = maxh.deleteMax()
        if maxv == None: break
        print 'delete maxval: {}, max heap structure:\n{}'.format(maxv, maxh)
        maxvalues.append(maxv)
    assert maxvalues == sorted(lst, reverse=True), 'ERROR: {} != {}'.format(maxvalues, sorted(lst, reverse=True))
