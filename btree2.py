"""B tree implementation"""
class BTreeNode(object):
    def __init__(self, t):
        self.t = t
        self.parent = None
        self.children = []
        self.keys = []

    def isFull(self):
        return len(self.keys) == self.t - 1

    def isLeaf(self):
        return len(self.children) == 0

    def findSlot(self, key):
        i = len(self.keys)
        # find the first key smaller than this 'key'
        # search from last to head
        while i > 0 and self.keys[i-1] > key:
            i -= 1
        return i
    
    def _insert(self, key):
        """insert one key, return its insertion location index"""
        iloc = self.findSlot(key)
        self.keys.insert(iloc, key)
        self.children.insert(iloc, None)
        if len(self.children) == 1:
            self.children.append(None)
        return iloc
    
    def insert(self, key):
        self._insert(key)
        if self.isFull():
            self.split()
        return 
    def split(self):
        """when call split, gurantee the node is full"""
        m = self.t / 2
        right = BTreeNode(self.t)
        right.keys = self.keys[m+1:]
        right.children = self.children[m+1:]

        mkey = self.keys[m]
        self.keys = self.keys[0:m]
        self.children = self.children[0:m]
        if self.parent == None:
            parent = BTreeNode(self.t)
        else:
            parent = self.parent
        iloc = parent.insert(mkey)
        parent.children[iloc] = self
        parent.children[iloc+1] = right
        self.parent = parent
        right.parent = parent
        return parent

    def traverse(self):
        n = len(self.keys)
        for i in xrange(n):
            if self.children[i]:
                self.children[i].traverse()
            print self.keys[i], ',',
        if self.children[-1]:
            self.children[-1].traverse()

