import os, sys, random

class Node(object):
    def __init__(self, key):
        self.parent = None
        self.left = None
        self.right = None
        self.key = key
        self.height = 1

    def __repr__(self):
        return '{}({})'.format(self.key, self.height)

class AVLTree(object):
    def __init__(self):
        self.root = None

    def insert(self, key):
        def _insert(key):
            nn = self.createNode(key)
            if not self.root:
                self.root = nn
            else:
                cn = self.root
                while cn:
                    if key <= cn.key:
                        if cn.left is None:
                            nn.parent = cn
                            cn.left = nn
                            break
                        else: cn = cn.left
                    else:
                        if cn.right is None:
                            nn.parent = cn
                            cn.right = nn
                            break
                        else: cn = cn.right
            return nn
        nn = _insert(key) # nn is newly inserted node
        if nn.parent:
            self.root = self._rebalance(nn.parent)
        print self

    def createNode(self, key):
        return Node(key)

    def _height(self, n):
        if not n: return 0
        return n.height

    def _rebalance(self, nn):
        """keep in-order position"""
        if nn == None: return self.root

        def _higher_child(n):
            left_h = self._height(n.left)
            right_h = self._height(n.right)
            return n.left if left_h >= right_h else n.right

        def _update_height(n):
            if not n: return
            cn = _higher_child(n)
            n.height = 1 + self._height(cn)

        def _restructure(x, y, z):
            """do trinode restructure, input z is parent of y, which is parent of x
            return new root node
            """
            def _left_left_rotate(x, y, z):
                """do single right rotation
                        z                       y
                      /                      /   \
                    y          =>          x      z
                  /   \                          /
                x       K                       K
                """
                p = z.parent
                y.parent = p
                if p:
                    if p.left == z: p.left = y
                    else: p.right = y

                K = y.right
                y.right = z
                z.parent = y
                z.left = K
                if K: K.parent = z

                #post-order to update height (in order)
                _update_height(x)
                _update_height(z)
                _update_height(y)
                return y

            def _right_right_rotate(x, y, z):
                """do single left rotation
                z                           y
                  \                      /   \
                    y          =>      z      x
                 /   \                  \
                K       x                 K
                """
                p = z.parent
                y.parent = p
                if p:
                    if p.left == z: p.left = y
                    else: p.right = y

                K = y.left
                y.left = z
                z.parent = y
                z.right = K
                if K: K.parent = z

                #post-order to update height (in order)
                _update_height(z)
                _update_height(x)
                _update_height(y)
                return y

            def _left_right_rotate(x, y, z):
                """do single right rotation, and then single left rotation"""
                r = _right_right_rotate(x.right, x, y)
                return _left_left_rotate(y, r, z)

            def _right_left_rotate(x, y, z):
                """do single left rotation, and then single right rotation"""
                r = _left_left_rotate(x.left, x, y)
                return _right_right_rotate(y, r, z)

            if z.left == y and y.left == x:
                print '<left-left>'
                return _left_left_rotate(x, y, z)
            if z.left == y and y.right == x:
                print '<left-right>'
                return _left_right_rotate(x, y, z)
            if z.right == y and y.left == x:
                print '<right-left>'
                return _right_left_rotate(x, y, z)
            if z.right == y and y.right == x:
                print '<right-right>'
                return _right_right_rotate(x, y, z)

        cn = nn
        while cn:
            print cn,
            if abs(self._height(cn.left) - self._height(cn.right)) > 1:
                z = cn
                y = _higher_child(z)
                x = _higher_child(y)
                cn = _restructure(x, y, z)
            _update_height(cn)
            print cn,
            nn = cn
            cn = cn.parent
        print
        return nn

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
            return newn

        def _deleteNode(n):
            if n.left and n.right:
                rn = _findMinKey(n.right)
                assert rn
                n.key = rn.key
                return _deleteNode(rn)
            elif n.left:
                newn = _replaceNode(n, n.left)
                return self._rebalance(newn.parent)
            elif n.right:
                newn = _replaceNode(n, n.right)
                return self._rebalance(newn.parent)
            else:
                _replaceNode(n)
                return self._rebalance(n.parent)
        self.root = _deleteNode(cn)
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
    lst = [random.randint(0, 30) for i in xrange(10)]
    lst = [8, 7, 28, 18, 23, 14, 4, 18, 18, 8]
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
    deletes = [8, 18]
    print 'deletes: {}'.format(deletes)
    map(lambda x: avlt.delete(x), deletes)
    print 'after bunch of deletes: '
    print '>>AVL tree structure:\n{}'.format(avlt)
    print '>>AVL tree inorder:'
    avlt.inorder()
    print
    assert avlt.verify()
