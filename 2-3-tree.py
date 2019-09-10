import random

"""implementation of 2-3 balanced search tree
"""

M = 3 # maximum M children for one node

class TreeNode(object):
    def __init__(self):
        # keys# is 1 smaller than children#
        self.keys = [] # in ascending order
        self.children = []

    def slot(self, key):
        i = 0
        """find first item larger than this 'key'"""
        while i < len(self.keys) and self.keys[i] < key:
            i += 1
        """if search to end, return number of keys"""
        return i

    def leaf(self):
        """check if current node is leaf or not"""
        return len(self.children) == 0 or not any(self.children)

    def overflow(self):
        """check if current node is overflow: > 3-node (2 keys, 3 children)"""
        return len(self.keys) == M

    def traverse(self):
        n = len(self.keys)
        i = 0
        while i < n:
            if self.children[i]:
                self.children[i].traverse()
            print str(self.keys[i]) + ',',
            i += 1
        if self.children[i]:
            self.children[i].traverse()

# 2 (Two)-3(Three) tree class
# there are maximum 3 children for one node
class TTTree(object):
    def __init__(self):
        self.root = TreeNode()

    def search(self, key):
        """given key, return its TreeNode object, otherwise, return None, if not found
        """
        def _search(node, key):
            if node == None: return None
            iloc = node.slot(key)
            if iloc < len(node.keys) and node.keys[iloc] == key:
                return node
            else:
                return _search(node.children[iloc], key)
        return _search(self.root, key)

    def traverse(self):
        """traverse all node in inorder way, and print each node's key
        """
        self.root.traverse()
        print

    def insert(self, key):
        def _insert(node, key):
            iloc = node.slot(key)
            u, mv = None, key
            if not node.leaf():
                (u, mv) = _insert(node.children[iloc], key)
                if not u: return (None, None)

            node.keys.insert(iloc, mv)
            node.children.insert(iloc, u)
            if len(node.keys) == 1:
                node.children.append(None)

            if node.overflow():
                return self._split(node)
            return (None, None)

        (u, mv) = _insert(self.root, key)
        if not u: return

        root = TreeNode()
        root.keys.insert(0, mv)
        root.children.insert(0, u)
        root.children.insert(1, self.root)
        self.root = root

    def _split(self, node):
        """split one node by half, the middle key goes up and return new first half node and this middle key
        """
        m = M / 2 # specifically it is 1
        mv = node.keys[m]
        u = TreeNode()
        u.keys = node.keys[0:m]
        u.children = node.children[0:m+1]

        node.keys = node.keys[m+1:]
        node.children = node.children[m+1:]

        return (u, mv)

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
    print '>>random list:\n{}'.format(lst)

    tttree = TTTree()
    map(lambda x: tttree.insert(x), lst)

    tttree.traverse()
    print '>>2-3 tree structure:\n{}'.format(tttree)

    print '>>search 2-3 tree'
    for x in [random.randint(0, 100) for _ in xrange(20)]:
        print 'search {} => '.format(x),
        y = tttree.search(x)
        if y: print y.keys
        else: print 'None'
