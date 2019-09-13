import os, sys, random

import binary_search_tree
from binary_search_tree import *

class AVLTree(BSTree):
    def __init__(self):
        super(AVLTree, self).__init__()

    def _getbalance(self, node):
        """return height(left) - height(right)"""
        if node == None: return 0
        return self._height(node.left) - self._height(node.right)

    def insert(self, key):
        def _insert(node, key):
            node = super(AVLTree, self)._insert(node, key)
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

    def _update_height(self, n):
        if not n: return
        n.height = 1 + max(self._height(n.left), self._height(n.right))

    def _height(self, n):
        if not n: return 0
        return n.height

    def delete(self, key):
        def _delete(t, key):
            t = super(AVLTree, self)._delete(t, key)
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

if __name__ == '__main__':
    lst = [random.randint(0, 100) for i in xrange(50)]
    #lst = [74, 20, 45, 68, 98, 95, 86, 71, 51, 2, 55, 23, 37, 90, 76, 33, 74, 65, 45, 65, 37, 70, 38, 4, 40, 82, 25, 74, 2, 9, 27, 2, 31, 68, 40, 72, 51, 78, 100, 25, 31, 13, 2, 81, 82, 80, 14, 72, 70, 48]
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
    #deletes = [23, 3, 16, 24, 22, 15, 28, 25, 18, 20]
    print 'deletes: {}'.format(deletes)
    map(lambda x: avlt.delete(x), deletes)
    print 'after bunch of deletes: '
    print '>>AVL tree structure:\n{}'.format(avlt)
    print '>>AVL tree inorder:'
    avlt.inorder()
    print
    assert avlt.verify()
