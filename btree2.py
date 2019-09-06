import random

"""my implementation for B tree
refer to https://www.cs.usfca.edu/~galles/visualization/BTree.html animation
"""
class BTreeNode(object):
    def __init__(self, M):
        self.M = M # maxnum number of keys in this node
        self.children = []
        self.keys = []

    def isFull(self):
        return len(self.keys) == self.M

    def isLeaf(self):
        """all children are None or no children means node is a leaf"""
        return len(self.children) == 0 or not any(self.children)

    def findSlot(self, key):
        n = len(self.keys)
        iloc = 0
        # find the first key not smaller than this 'key'
        while iloc < n and self.keys[iloc] < key:
            iloc += 1
        return iloc

    def traverse(self):
        n = len(self.keys)
        for i in xrange(n):
            if self.children[i]:
                self.children[i].traverse()
            print str(self.keys[i]) + ',',
        if len(self.children) and self.children[-1]:
            self.children[-1].traverse()

    def search(self, key):
        iloc = self.findSlot(key)
        n = len(self.keys)
        if iloc < n and self.keys[iloc] == key:
            return True
        elif self.children[iloc]:
            return self.children[iloc].search(key)
        else:
            return False

class BTree(object):
    def __init__(self, M):
        self.M = M
        self.root = BTreeNode(M)

    def insert(self, key):
        (u, mkey) = self._insert(self.root, key)
        if not u: return
        # now, we have new root
        root = BTreeNode(self.M)
        root.keys.append(mkey)
        root.children.append(u)
        root.children.append(self.root)
        self.root = root

    def _insert(self, node, key):
        """insert one key starting from node
        if this node is split, return tuple of (the first new half node, key that will move up)
        otherwise, return (None, None)
        """
        t = None # new child node
        n = len(node.keys)
        iloc = node.findSlot(key)
        if not node.isLeaf():
            (t, key) = self._insert(node.children[iloc], key)
            if not t: return (None, None)

        node.keys.insert(iloc, key)
        node.children.insert(iloc, t)
        if n == 0:
            node.children.append(None)

        if node.isFull():
            return self._split(node)
        return (None, None)

    def _split(self, node):
        """when call split, gurantee the node is full
        return tuple of (new first half node, key that will move up)
        """
        m = node.M / 2
        left = BTreeNode(node.M)
        left.keys = node.keys[0:m]
        left.children[0:m] = node.children[0:m+1]

        mkey = node.keys[m]
        node.keys = node.keys[m+1:]
        node.children = node.children[m+1:]
        return (left, mkey)

    def search(self, key):
        print '>>search key {}'.format(key)
        ret = self.root.search(key)
        if ret: print ' >>> OK'
        else: print ' >>> FAIL'

    def traverse(self):
        if self.root:
            self.root.traverse()
            print

    def __str__(self):
        from collections import deque
        s = []
        q = deque()
        q.append(self.root)
        q.append(None) # special element to identify level ending
        ilevel = 0
        levelstr = []
        while len(q):
            node = q.popleft()
            if node:
                levelstr.append(str(node.keys))
                for c in node.children:
                    if c: q.append(c)
            else:
                s.append('L{}: {}'.format(ilevel, ' '.join(levelstr)))
                ilevel += 1
                levelstr = []
                if len(q): q.append(None)
        return '\n'.join(s)

if __name__ == '__main__':
    lst = [random.randint(0, 100) for _ in xrange(20)]
    #lst = [10, 20, 30, 40, 50, 45, ]
    print '>>random list:\n{}'.format(lst)
    M = 3
    btree = BTree(M)
    map(lambda x: btree.insert(x), lst)
    print '>>btree traverse:'
    btree.traverse()
    print '>>btree structure:\n{}'.format(btree)
    print
    print '>>DO search 1<<'
    map(lambda x: btree.search(x), lst)
    print '>>DO search 2<<'
    map(lambda x: btree.search(x), [random.randint(0, 100) for _ in xrange(20)])