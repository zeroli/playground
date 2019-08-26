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
                while True:
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
        nn = _insert(key)
        self._rebalance(nn)
    
    def createNode(self, key):
        return Node(key)

    def _height(self, n):
        if not n: return 0
        return n.height

    def _rebalance(self, nn):
        """keep in-order position"""
        
        def _higher_child(n):
            left_h = self._height(n.left)
            right_h = self._height(n.right)
            return n.left if left_h > right_h else n.right

        def _update_height(n):
            if not n: return
            cn = _higher_child(n)
            n.height = 1 + self._height(cn)

        def _restructure(x, y, z):
            """do trinode restructure, input z is parent of y, which is parent of x
            return new root node
            """
            def _left_left_rotate(x, y, z):
                """do single right rotation"""
                parent = z.parent
                z.parent = y                
                z.left = y.right
                y.right = z
                y.parent = parent
                _update_height(x)
                _update_height(z)
                _update_height(y)
                return y

            def _right_right_rotate(x, y, z):
                print x, y, z
                """do single left rotation"""
                parent = z.parent
                z.parent = y
                z.right = y.left
                y.left = z
                y.parent = parent
                _update_height(x)
                _update_height(z)
                _update_height(y)
                return y

            def _left_right_rotate(x, y, z):
                """do single right rotation, and then single left rotation"""
                r = _right_right_rotate(x.right, x, y)
                r.parent.left = r
                return _left_left_rotate(y, r, z)

            def _right_left_rotate(x, y, z):
                """do single left rotation, and then single right rotation"""
                r = _left_left_rotate(x.left, x, y)
                r.parent.right = r
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

        print 'insert {}'.format(nn.key),
        _update_height(nn)
        cn = nn.parent
        while cn:
            print cn,
            if abs(self._height(cn.left) - self._height(cn.right)) > 1:
                z = cn
                y = _higher_child(z)
                x = _higher_child(y)
                parent = z.parent
                cn = _restructure(x, y, z)
                if z == parent.left:
                    parent.left = cn
                else:
                    parent.right = cn
            _update_height(cn)
            print cn,
            cn = cn.parent
        print 
        print 'preorder: ',
        self.preorder()
        print

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

def main():
    lst = [10, 19, 1, 11, 18, 8, 18, 15, 5, 20] #[random.randint(0, 30) for i in xrange(10)]
    print lst
    avlt = AVLTree()
    map(lambda x: avlt.insert(x), lst)
    avlt.inorder()
    print
    assert avlt.verify()

    print 'min:', avlt.minKey(), ', max:', avlt.maxKey()
    
    map(lambda x: avlt.find(x), [random.randint(0, 30) for i in xrange(10)])
    
    print '>> test delete'
    map(lambda x: avlt.delete(x), [random.randint(0, 30) for i in xrange(10)])
    print 'after delete: '
    avlt.inorder()
    print

main()
