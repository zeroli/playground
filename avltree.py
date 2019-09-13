import os, sys, random

class Node(object):
    def __init__(self, key):
        self.left = None
        self.right = None
        self.key = key
        self.height = 1

    def __repr__(self):
        return '{}({})'.format(self.key, self.height)

class AVLTree(object):
    def __init__(self):
        self.root = None

    def _getbalance(self, node):
        """return height(left) - height(right)"""
        if node == None: return 0
        return self._height(node.left) - self._height(node.right)

    def insert(self, key):
        def _insert(node, key):
            if node == None:
                node = self.createNode(key)
            else:
                if key < node.key:
                    node.left = _insert(node.left, key)
                elif key > node.key:
                    node.right = _insert(node.right, key)
            #rebalance
            self._update_height(node)
            balance = self._getbalance(node)
            if balance > 1:
                if self._getbalance(node.left) >= 0:
                    node = self._left_left_rotate(node)
                else:
                    node = self._left_right_rotate(node)
            elif balance < -1:
                if self._getbalance(node.right) <= 0:
                    node = self._right_right_rotate(node)
                else:
                    node = self._right_left_rotate(node)

            return node

        print '>>insert {}'.format(key)
        self.root = _insert(self.root, key)
        print self

    def _left_left_rotate(self, k2):
        k1 = k2.left
        k2.left = k1.right
        k1.right = k2
        self._update_height(k2)
        self._update_height(k1)
        return k1

    def _right_right_rotate(self, k2):
        k1 = k2.right
        k2.right = k1.left
        k1.left = k2
        self._update_height(k2)
        self._update_height(k1)
        return k1

    def _left_right_rotate(self, k3):
        k3.left = self._right_right_rotate(k3.left)
        return self._left_left_rotate(k3)

    def _right_left_rotate(self, k3):
        k3.right = self._left_left_rotate(k3.right)
        return self._right_right_rotate(k3)

    def createNode(self, key):
        return Node(key)

    def _update_height(self, n):
        if not n: return
        n.height = 1 + max(self._height(n.left), self._height(n.right))

    def _height(self, n):
        if not n: return 0
        return n.height

    def delete(self, key):
        def _findMinKey(n):
            while n:
                if not n.left: return n
                n = n.left
            return None

        def _delete(t, key):
            if not t:
                print 'AVL delete: could not find key {}'.format(key)
                return
            if key < t.key:
                t.left = _delete(t.left, key)
            elif key > t.key:
                t.right = _delete(t.right, key)
            else: # found the key node
                # have 2 children
                if t.left and t.right:
                    succ = _findMinKey(t.right)
                    t.key = succ.key
                    t.right = _delete(t.right, t.key)
                else: # have 1 child or leaf node
                    if t.left == None:
                        t = t.right
                    elif t.right == None:
                        t = t.left
            # rebalance node t up to root
            self._update_height(t)
            balance = self._getbalance(t)
            if balance > 1:
                if self._getbalance(t.left) >= 0:
                    t = self._left_left_rotate(t)
                else:
                    t = self._left_right_rotate(t)
            elif balance < -1:
                if self._getbalance(t.right) <= 0:
                    t = self._right_right_rotate(t)
                else:
                    t = self._right_left_rotate(t)

            return t
        print '>>delete key {}'.format(key)
        self.root =  _delete(self.root, key)
        print self
        assert self.verify()

    def verify(self):
        cn = self.root
        def _verify(n):
            if not n: return True

            left_h = self._height(n.left)
            right_h = self._height(n.right)
            print 'node {}, height {}, left height {}, right height {}'.format(
                n.key, n.height, left_h, right_h)
            return abs(left_h - right_h) <= 1 and _verify(n.left) and _verify(n.right)

        return _verify(cn)

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

if __name__ == '__main__':
    lst = [random.randint(0, 100) for i in xrange(50)]
    lst = [74, 20, 45, 68, 98, 95, 86, 71, 51, 2, 55, 23, 37, 90, 76, 33, 74, 65, 45, 65, 37, 70, 38, 4, 40, 82, 25, 74, 2, 9, 27, 2, 31, 68, 40, 72, 51, 78, 100, 25, 31, 13, 2, 81, 82, 80, 14, 72, 70, 48]
    print '>>random list: {}'.format(lst)
    avlt = AVLTree()
    map(lambda x: avlt.insert(x), lst)
    print '>>AVL tree structure:\n{}'.format(avlt)
    print '>>AVL tree inorder:'
    avlt.inorder()
    print
    assert avlt.verify()

    print 'min:', avlt.minKey(), ', max:', avlt.maxKey()

    map(lambda x: avlt.find(x), [random.randint(0, 30) for i in xrange(10)])

    print '>> test delete'
    deletes = [random.randint(0, 30) for i in xrange(10)]
    deletes = [23, 3, 16, 24, 22, 15, 28, 25, 18, 20]
    print 'deletes: {}'.format(deletes)
    map(lambda x: avlt.delete(x), deletes)
    print 'after bunch of deletes: '
    print '>>AVL tree structure:\n{}'.format(avlt)
    print '>>AVL tree inorder:'
    avlt.inorder()
    print
    assert avlt.verify()
