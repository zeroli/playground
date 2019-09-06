import os, sys
import copy
import random

class Node(object):
    def __init__(self, key):
        self.left = None
        self.right = None
        self.parent = None
        self.key = key

class BSTree(object):
    def __init__(self):
        self.root = None
        pass

    def insert(self, key):
        def _insert(root, key):
            print 'insert key {} with root {}'.format(key, root.key if root else None)
            if not root:
                return self.createNode(key)
            elif key < root.key:
                nn = _insert(root.left, key)
                nn.parent = root
                root.left = nn
                return root
            else:
                nn = _insert(root.right, key)
                nn.parent = root
                root.right = nn
                return root
        if not self.root:
            self.root = self.createNode(key)
        else:
            _insert(self.root, key)

    def createNode(self, key):
        return Node(key)

    def delete2(self, key):
        """algo comes from <introduction to algorithms>
        """
        print '>>delete2 key {}'.format(key)
        cn = self.find(key)
        if not cn:
            print 'delete2: could not find key {}'.format(key)
            return

        if cn.left == None or cn.right == None:
            y = cn
        else:
            y = self._successor(cn)
        if y.left:
            x = y.left
        else:
            x = y.right

        if x:
            x.parent = y.parent
        if y.parent == None:
            self.root = x
        elif y == y.parent.left:
            y.parent.left = x
        else:
            y.parent.right = x
        if cn != y:
            cn.key = y.key

    def delete3(self, key):
        print '>>delete3 key {}'.format(key)
        def _delete(key, t):
            if not t:
                print 'delete3: could not find key {}'.format(key)
                return
            if key < t.key:
                t.left = _delete(key, t.left)
            elif key > t.key:
                t.right = _delete(key, t.right)
            else: # found the key node
                # have 2 children
                if t.left and t.right:
                    succ = self._successor(t)
                    t.key = succ.key
                    t.right = _delete(t.key, t.right)
                else: # have 1 child or leaf node
                    if t.left == None:
                        t = t.right
                    elif t.right == None:
                        t = t.left
            return t
        self.root =  _delete(key, self.root)

    def inorder(self):
        if not self.root: return
        cn = self.root

        def _inorder(n):
            if not n: return
            _inorder(n.left)
            print n.key,
            _inorder(n.right)

        _inorder(cn)

    def preorder(self):
        if not self.root: return
        cn = self.root

        def _preorder(n):
            if not n: return
            print n.key,
            _preorder(n.left)
            _preorder(n.right)

        _preorder(cn)

    def postorder(self):
        if not self.root: return
        cn = self.root

        def _postorder(n):
            if not n: return
            _postorder(n.left)
            _postorder(n.right)
            print n.key,

        _postorder(cn)

    def minKey(self):
        cn = self.root
        while cn:
            key = cn.key
            cn = cn.left
        return key

    def maxKey(self):
        cn = self.root
        while cn:
            key = cn.key
            cn = cn.right
        return key

    def find(self, key):
        cn = self.root
        while cn:
            if key == cn.key:
                print 'found key {}'.format(key)
                return cn
            elif key < cn.key:
                cn = cn.left
            else:
                cn = cn.right
        print 'could not found key {}'.format(key)
        return cn

    def _successor(self, x):
        def _minNode(x):
            while x.left:
                x = x.left
            return x
        def _maxNode(x):
            while x.right:
                x = x.right
            return x
        if x.right:
            y = _minNode(x.right)
            return y

        y = x.parent
        while y and x == y.right:
            x = y
            y = y.parent
        return y

    def successor(self, key):
        x = self.find(key)
        if not x:
            raise 'ERROR: not found key {}'.format(key)

        y = self._successor(x)
        if y: return y.key
        else: print '>>>>: no successor for key {}'.format(key)

    def _predecessor(self, x):
        def _minNode(x):
            while x.left:
                x = x.left
            return x
        def _maxNode(x):
            while x.right:
                x = x.right
            return x

        if x.left:
            y = _maxNode(x.left)
            return y

        y = x.parent
        while y and x == y.left:
            x = y
            y = y.parent
        return y

    def predecessor(self, key):
        x = self.find(key)
        if not x:
            raise 'ERROR: not found key {}'.format(key)

        y = self._predecessor(x)
        if y: return y.key
        else: print '>>>>: no predecessor for key {}'.format(key)

    def rangeQuery(self, key1, key2):
        cn = self.root

        assert key1 <= key2

        def _rangeQuery(n, key1, key2):
            if not n: return []
            if key1 <= n.key <= key2:
                L = _rangeQuery(n.left, key1, n.key)
                R = _rangeQuery(n.right, n.key, key2)
                L.append(n.key)
                L.extend(R)
                return L
            elif key2 < n.key:
                return _rangeQuery(n.left, key1, key2)
            elif key1 > n.key:
                return _rangeQuery(n.right, key1, key2)
            else:
                return []
        return _rangeQuery(cn, key1, key2)

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
                levelstr.append(str(node.key))
                if node.left: q.append(node.left)
                if node.right: q.append(node.right)
            else:
                s.append('L{}: {}'.format(ilevel, ' '.join(levelstr)))
                ilevel += 1
                levelstr = []
                if len(q): q.append(None)
        return '\n'.join(s)

def test():
    #lst = [random.randint(0, 30) for _ in xrange(10)]
    lst = [4, 15, 3, 14, 5, 16, 7, 12, 6, 10]
    print '>>random list: {}'.format(lst)
    bst = BSTree()
    map(lambda x: bst.insert(x), lst)
    print '>>bstree structure:\n{}'.format(bst)
    bst.inorder()
    print
    print 'min:', bst.minKey(), ', max:', bst.maxKey()

    map(lambda x: bst.find(x), [random.randint(0, 30) for _ in xrange(10)])

    print '>> test delete'
    bst.inorder()
    print
    #deletes = [random.randint(0, 30) for _ in xrange(10)]
    deletes = [7, 3, 4, 7, 3, 19, 21, 24, 13, 13]
    print 'deletes: {}'.format(deletes)

    bst2 = copy.deepcopy(bst)
    map(lambda x: bst2.delete2(x), deletes)
    print 'after delete2: '
    bst2.inorder()
    print

    bst3 = copy.deepcopy(bst)
    map(lambda x: bst3.delete3(x), deletes)
    print 'after delete3: '
    bst3.inorder()
    print

    print '>> test rangeQuery'
    for _ in xrange(10):
        key1 = random.randint(0, 30)
        key2 = key1 + random.randint(0, 10)
        print 'range query: [{}, {}]'.format(key1, key2)
        print bst.rangeQuery(key1, key2)

    print '>> tree traversal: ',
    bst.inorder()
    print
    print '>> test successor'
    print bst.successor(lst[0])
    print
    print '>> test predecessor'
    print bst.predecessor(lst[0])
    print


if __name__ == '__main__':
    test()
