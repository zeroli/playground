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
        def _insert(node, key):
            if node == None:
                node = self.createNode(key)
            else:
                if key < node.key:
                    node.left = nn = _insert(node.left, key)
                    nn.parent = node
                    if self._height(node.left) - self._height(node.right) > 1:
                        if key < node.left.key:
                            node = self._left_left_rotate(node)
                        else:
                            node = self._left_right_rotate(node)
                elif key > node.key:
                    node.right = nn = _insert(node.right, key)
                    nn.parent = node
                    if self._height(node.right) - self._height(node.left) > 1:
                        if key > node.right.key:
                            node = self._right_right_rotate(node)
                        else:
                            node = self._right_left_rotate(node)

            self._update_height(node)
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

    def _higher_child(self, n):
        left_h = self._height(n.left)
        right_h = self._height(n.right)
        return n.left if left_h >= right_h else n.right

    def _update_height(self, n):
        if not n: return
        cn = self._higher_child(n)
        n.height = 1 + self._height(cn)

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
                if self._height(t.right) - self._height(t.left) > 1:
                    if t.right.right:
                        t = self._right_right_rotate(t)
                    else:
                        t = self._right_left_rotate(t)
            elif key > t.key:
                t.right = _delete(t.right, key)
                if self._height(t.left) - self._height(t.right) > 1:
                    if t.left.left:
                        t = self._left_left_rotate(t)
                    else:
                        t = self._left_right_rotate(t)
            else: # found the key node
                # have 2 children
                if t.left and t.right:
                    succ = _findMinKey(t.right)
                    t.key = succ.key
                    t.right = _delete(t.right, t.key)
                    if self._height(t.left) - self._height(t.right) > 1:
                        if t.left.left:
                            t = self._left_left_rotate(t)
                        else:
                            t = self._left_right_rotate(t)
                else: # have 1 child or leaf node
                    if t.left == None:
                        t = t.right
                    elif t.right == None:
                        t = t.left
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
