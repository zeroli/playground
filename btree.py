class BTreeNode(object):
    def __init__(self, t, isleaf):
        self.t = t
        self.isleaf = isleaf
        self.children = [None] * (2*t)
        self.keys = [None] * (2*t-1)
        self.n = 0 # number of keys in this node

    def full(self):
        return self.n == 2*self.t - 1

    def __repr__(self):
        return ','.join(self.keys)

    def traverse(self):
        n = self.n
        for i in xrange(n):
            if not self.isleaf:
                self.children[i].traverse()
            print self.keys[i], ',',
        if not self.isleaf and n > 0:
            self.children[n].traverse()

    def search(self, key):
        i = 0
        # find the first key which is >= key
        while i < self.n and key > self.keys[i]:
            i += 1
        if i < self.n and self.keys[i] == key:
            return self
        if self.isleaf:
            return None # no children to continue
        return self.children[i].search(key)

    def splitChild(self, i, y):
        z = BTreeNode(y.t, y.isleaf)
        z.n = self.t - 1

        # copy last half of keys in y to new node z
        z.keys[0 : self.t-1] = y.keys[self.t : 2*self.t-1]

        if not y.isleaf:
            # copy last half of childrens in y to new node z
            z.children[0 : self.t] = y.children[self.t : 2*self.t]
        y.n = self.t - 1

        # move back to spare one more slot for new child
        self.children.insert(i+1, z)
        self.keys.insert(i, y.keys[self.t-1])
        self.n += 1

    def insertNonFull(self, key):
        i = self.n - 1
        if self.isleaf:
            while i >= 0 and self.keys[i] > key:
                self.keys[i+1] = self.keys[i]
                i -= 1
            self.keys[i+1] = key
            self.n += 1
        else:
            while i >= 0 and self.keys[i] > key:
                i -= 1
            if self.children[i+1].full():
                self.splitChild(i+1, self.children[i+1])
                if self.keys[i+1] < key:
                    i += 1
            self.children[i+1].insertNonFull(key)

class BTree(object):
    def __init__(self, t):
        self.t = t
        self.root = None

    def insert(self, key):
        if self.root == None:
            self.root = BTreeNode(self.t, True)
            self.root.keys[0] = key
            self.root.n = 1
        else:
            if self.root.full():
                s = BTreeNode(self.t, False)
                s.children[0] = self.root
                s.splitChild(0, self.root)
                i = 0
                if s.keys[0] < key:
                    i += 1
                s.children[i].insertNonFull(key)
                self.root = s
            else:
                self.root.insertNonFull(key)

    def build(self, lst):
        for e in lst:
            self.insert(e)

    def traverse(self):
        self.root.traverse()

if __name__ == '__main__':
    btree = BTree(3)
    btree.build([10, 20, 5, 6, 12, 30, 7, 17])
    btree.traverse()
