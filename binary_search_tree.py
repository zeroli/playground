import os, sys
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

    def delete(self, key):
        cn = self.find(key)
        if not cn:
            print 'delete: could not find key {}'.format(key)
            return

        def _findMinKey(n):
            while n:
                if not n.left: return n
                n = n.left
            return None
        def _findMaxKey(n):
            while n:
                if not n.right: return n
                n = n.right
            return None

        def _replaceNode(n, newn=None):
            parent = n.parent
            if parent:
                if parent.left == n:
                    parent.left = newn
                if parent.right == n:
                    parent.right = newn
            if newn:
                newn.parent = parent

        def _deleteNode(n):
            if n.left and n.right:
                rn = _findMinKey(n.right)
                assert rn
                n.key = rn.key
                _deleteNode(rn)
            elif n.left:
                _replaceNode(n, n.left)
            elif n.right:
                _replaceNode(n, n.right)
            else:
                _replaceNode(n)
        _deleteNode(cn)


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

    def successor(self, key):
        x = self.find(key)
        if not x:
            raise 'ERROR: not found key {}'.format(key)

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
            return y.key

        y = x.parent
        while y and x == y.right:
            x = y
            y = y.parent
        return y.key

    def predecessor(self, key):
        x = self.find(key)
        if not x:
            raise 'ERROR: not found key {}'.format(key)

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
            return y.key

        y = x.parent
        while y and x == y.left:
            x = y
            y = y.parent
        return y.key

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


def test():
    lst = [random.randint(0, 30) for i in xrange(10)]
    print lst
    bst = BSTree()
    map(lambda x: bst.insert(x), lst)
    bst.inorder()
    print
    print 'min:', bst.minKey(), ', max:', bst.maxKey()

    map(lambda x: bst.find(x), [random.randint(0, 30) for i in xrange(10)])

    print '>> test delete'
    map(lambda x: bst.delete(x), [random.randint(0, 30) for i in xrange(10)])
    print 'after delete: '
    bst.inorder()
    print

    print '>> test rangeQuery'
    for i in xrange(10):
        key1 = random.randint(0, 30)
        key2 = key1 + random.randint(0, 10)
        print 'range query: [{}, {}]'.format(key1, key2)
        print bst.rangeQuery(key1, key2)


    map(lambda x: bst.insert(x), lst)
    print '>> tree traversal: ',
    bst.inorder()
    print
    print '>> test successor'
    print bst.successor(lst[0])

    print '>> test predecessor'
    print bst.predecessor(lst[0])
    print


if __name__ == '__main__':
    test()
