import os, sys
import copy
import random

class TreeNode(object):
    def __init__(self, key, left=None, right=None):
        self.key = key
        self.left = left
        self.right = right
        self.parent = None
        self.height = 1

    def __repr__(self):
        return '{}({})'.format(self.key, self.height)

class BSTree(object):
    def __init__(self):
        self.root = None

    def _insert(self, node, key):
        if not node:
            node = TreeNode(key)
        elif key < node.key:
            node.left = self._insert(node.left, key)
            node.left.parent = node
        else:
            node.right = self._insert(node.right, key)
            node.right.parent = node
        return node

    def insert(self, key):
        print 'insert key {}'.format(key)
        self.root = self._insert(self.root, key)

    """
    def delete2(self, key):
       #algo comes from <introduction to algorithms>
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
    """
    def delete(self, key):
        print '>>delete key {}'.format(key)
        self.root =  self._delete(self.root, key)

    def _delete(self, node, key):
        if not node:
            print 'delete: could not find key {}'.format(key)
            return
        if key < node.key:
            node.left = self._delete(node.left, key)
        elif key > node.key:
            node.right = self._delete(node.right, key)
        else: # found the key node
            # have 2 children
            if node.left and node.right:
                succ = self._successor(node)
                node.key = succ.key
                node.right = self._delete(node.right, key)
            else: # have 1 child or leaf node
                if node.left == None:
                    node = node.right
                elif node.right == None:
                    node = node.left
        return node

    def inorder(self):
        print '>>inorder traverse'
        if not self.root: return
        def _inorder(n):
            if not n: return
            _inorder(n.left)
            print n.key,
            _inorder(n.right)

        _inorder(self.root)

    def preorder(self):
        print '>>preorder traverse'
        if not self.root: return

        def _preorder(n):
            if not n: return
            print n.key,
            _preorder(n.left)
            _preorder(n.right)

        _preorder(self.root)

    def postorder(self):
        print '>>postorder traverse'
        if not self.root: return

        def _postorder(n):
            if not n: return
            _postorder(n.left)
            _postorder(n.right)
            print n.key,

        _postorder(self.root)

    def minKey(self):
        node = self._minNode(self.root)
        if node: return node.key
        else: return None

    def maxKey(self):
        node = self._maxNode(self.root)
        if node: return node.key
        else: return None

    def _minNode(self, node):
        while node.left:
            node = node.left
        return node

    def _maxNode(self, node):
        while node.right:
            node = node.right
        return node

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

    def _successor(self, node):
        if node.right:
            return self._minNode(node.right)

        y = node.parent
        while y and node == y.right:
            node = y
            y = y.parent
        return y

    def successor(self, key):
        node = self.find(key)
        if not node:
            raise 'ERROR: not found key {}'.format(key)

        y = self._successor(node)
        if y: return y.key
        else: print '>>>>: no successor for key {}'.format(key)

    def _predecessor(self, node):
        if node.left:
            return self._maxNode(node.left)

        y = node.parent
        while y and node == y.left:
            node = y
            y = y.parent
        return y

    def predecessor(self, key):
        node = self.find(key)
        if not node:
            raise 'ERROR: not found key {}'.format(key)

        y = self._predecessor(node)
        if y: return y.key
        else: print '>>>>: no predecessor for key {}'.format(key)

    def floor(self, key):
        """given key, return the largest node that is smaller than this 'key'
        """
        def _floor(x, key):
            if x == None: return None
            if x.key == key:
                return x
            elif key < x.key:
                return _floor(x.left, key)
            else:
                y = _floor(x.right, key)
                if y: return y
                else: return x
        return _floor(self.root, key)

    def ceiling(self, key):
        """given key, return the smallest node that is larger than this 'key'
        """
        def _ceiling(x, key):
            if x == None: return None
            if x.key == key:
                return x
            elif key > x.key:
                return _ceiling(x.right, key)
            else:
                y = _ceiling(x.left, key)
                if y: return y
                else: return x
        return _ceiling(self.root, key)

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

    def rank(self, key):
        """given key, return its ranking index
        """
        def _count(node):
            if node == None: return 0
            cnt = 1
            if node.left:
                cnt += _count(node.left)
            if node.right:
                cnt += _count(node.right)
            return cnt

        def _rank(node, key):
            if node == None: return -1
            if key == node.key:
                return _count(node.left)
            elif key < node.key:
                return _rank(node.left, key)
            else:
                r = _rank(node.right, key)
                if r >= 0:
                    return _count(node.left) + 1 + _rank(node.right, key)
                else:
                    return r
        return _rank(self.root, key)

    def deleteMin(self):
        """delete minimum node
        """
        def _deleteMin(node):
            if node == None: return None
            if node.left == None:
                return node.right
            node.left = _deleteMin(node.left)
            return node
        self.root = _deleteMin(self.root)

    def deleteMax(self):
        """delete maximum node
        """
        def _deleteMax(node):
            if node == None: return None
            if node.right == None:
                return node.left
            node.right = _deleteMax(node.right)
            return node
        self.root = _deleteMax(self.root)

    def isBST(self):
        def _isBST(node, minv, maxv):
            if node == None: return True
            if minv <= node.key <= maxv:
                return _isBST(node.left, minv, node.key) and _isBST(node.right, node.key, maxv)
            else:
                return False
        return _isBST(self.root, -sys.maxint-1, sys.maxint)

    def __str__(self):
        if self.root == None: return '<EMPTY>'
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
    lst = [random.randint(0, 100) for _ in xrange(10)]
    print '>>random list: {}'.format(lst)
    bst = BSTree()
    map(lambda x: bst.insert(x), lst)
    print '>>bstree structure:\n{}'.format(bst)
    assert bst.isBST() == True, 'ERROR: the tree is not binary search tree'
    bst.inorder()
    print
    print 'min:', bst.minKey(), ', max:', bst.maxKey()

    map(lambda x: bst.find(x), [random.randint(0, 30) for _ in xrange(10)])

    print '>> test delete'
    bst.inorder()
    print
    deletes = [random.randint(0, 30) for _ in xrange(10)]
    print 'deletes: {}'.format(deletes)

    bst3 = copy.deepcopy(bst)
    map(lambda x: bst3.delete(x), deletes)
    print 'after delete3: '
    print '>>bstree structure:\n{}'.format(bst)
    assert bst3.isBST() == True, 'ERROR: the tree is not binary search tree'
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

    x = random.randint(0, 100)
    print '>> test floor({})'.format(x)
    y = bst.floor(x)
    if y: print '>> {}'.format(y.key)
    else: print '>> NONE'

    x = random.randint(0, 100)
    print '>> test ceiling({})'.format(x)
    y = bst.ceiling(x)
    if y: print '>> {}'.format(y.key)
    else: print '>> NONE'

    print '>> test rank({})'.format(1000)
    print bst.rank(1000)

    print '>> test rank({})'.format(lst[0])
    print bst.rank(lst[0])

    print 'bst structure:\n{}'.format(bst)
    print '>> test deleteMin'
    bst.deleteMin()
    print 'bst structure:\n{}'.format(bst)
    assert bst.isBST() == True, 'ERROR: the tree is not binary search tree'
    print '>> test deleteMax'
    bst.deleteMax()
    print 'bst structure:\n{}'.format(bst)
    assert bst.isBST() == True, 'ERROR: the tree is not binary search tree'
    print 'bst traversal:'
    bst.inorder()

if __name__ == '__main__':
    test()
