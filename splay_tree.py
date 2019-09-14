import random

import binary_search_tree
from binary_search_tree import *

"""implementation of splay tree
https://www.geeksforgeeks.org/splay-tree-set-2-insert-delete/
has different implementation for insert/delete using recursive method, so that will not use node's parent
"""

class SplayTree(BSTree):
    def __init__(self):
        super(SplayTree, self).__init__()

    def insert(self, key):
        print '>>insert key {}'.format(key)
        if self.root == None:
            self.root = TreeNode(key)
        else:
            node = self.root
            while node:
                p = node
                if key < node.key:
                    node = node.left
                else:
                    node = node.right
            node = TreeNode(key)
            node.parent = p
            if key < p.key:
                p.left = node
            else:
                p.right = node
            self.root = self._splay(node)
        print self
        assert self.isBST()

    def find(self, key):
        print '>>find key {}'.format(key)
        node = super(SplayTree, self).find(key)
        if node == None: return None
        #splay this found node to root
        self.root = self._splay(node)
        print self
        assert self.isBST()
        return node

    def _splay(self, node):
        #rotate this found node to root
        while node.parent:
            y = node.parent
            if y.left == node:
                if not y.parent or y.parent.left == y:
                    node = self._left_left_rotate(node)
                elif not y.parent or y.parent.right == y:
                    node = self._right_left_rotate(node)
            else:
                if not y.parent or y.parent.right == y:
                    node = self._right_right_rotate(node)
                elif not y.parent or y.parent.left == y:
                    node = self._left_right_rotate(node)
        assert node.parent == None
        return node

    def _leftRotate(self, x):
        if x == None: return
        p = x.parent
        r = x.right
        # update r.left
        x.right = r.left
        if r.left: r.left.parent = x

        # update r
        x.parent = r
        r.left = x
        r.parent = p

        if p:
            if p.left == x: p.left = r
            else: p.right = r
        return r

    def _rightRotate(self, x):
        if x == None: return x
        p = x.parent
        r = x.left
        # update r.right
        x.left = r.right
        if r.right: r.right.parent = x
        # update r
        x.parent = r
        r.right = x
        r.parent = p

        if p:
            if p.left == x: p.left = r
            else: p.right = r
        return r

    def _left_left_rotate(self, x):
        """
        Zig-Zig (Left Left Case):
            Z                        Y                           X
            / \                     /   \                        / \
            Y  T4   rightRotate(Z)  X     Z     rightRotate(Y)  T1   Y
            / \      ============>  / \   / \    ============>       / \
        X  T3                   T1 T2 T3 T4                      T2  Z
        / \                                                          / \
        T1 T2
        """
        if x.parent.parent:
            self._rightRotate(x.parent.parent)
        self._rightRotate(x.parent)
        return x

    def _right_right_rotate(self, x):
        """
        Zag-Zag (Right Right Case):
        Z                          Y                           X
        /  \                      /   \                        / \
        T1   Y     leftRotate(Z)  Z     X     leftRotate(Y)    Y   T4
            / \    ============> / \   / \    ============>   / \
        T2   X               T1 T2 T3 T4                  Z   T3
            / \                                          / \
            T3 T4
        """
        if x.parent.parent:
            self._leftRotate(x.parent.parent)
        self._leftRotate(x.parent)
        return x

    def _left_right_rotate(self, x):
        """
        Zag-Zig (Left Right Case):
            Z                        Z                            X
            / \                     /   \                        /   \
            Y   T4  leftRotate(Y)   X     T4    rightRotate(Z)   Y     Z
        /  \      ============>  / \          ============>   / \   /  \
        T1   X                   Y  T3                       T1  T2 T3  T4
            / \                 / \
            T2  T3              T1   T2
        """
        self._leftRotate(x.parent)
        if x.parent:
            self._rightRotate(x.parent)
        return x

    def _right_left_rotate(self, x):
        """
        Zig-Zag (Right Left Case):
        Z                          Z                           X
        /  \                      /  \                        /   \
        T1   Y    rightRotate(Y)  T1   X     leftRotate(Z)    Z     Y
            / \   =============>      / \    ============>   / \   / \
        X  T4                    T2   Y                 T1  T2 T3  T4
        / \                           / \
        T2  T3                        T3  T4
        """
        self._rightRotate(x.parent)
        if x.parent:
            self._leftRotate(x.parent)
        return x

    def delete(self, key):
        print '>>delete key {}'.format(key)
        node = self.find(key)
        if not node: return
        #find will swin the deleted node to the root
        assert node.parent == None
        if node.left == None:
            self.root = node.right
        elif node.right == None:
            self.root = node.left
        else:
            succ = self._successor(node)
            succ.right = self._delete(node.right, succ.key)
            succ.left = node.left
            node.left.parent = succ
            node.right.parent = succ
            self.root = succ
        self.root.parent = None
        print self

if __name__ == '__main__':
    lst = [random.randint(0, 100) for i in xrange(10)]
    #lst = [82, 39, 86, 91, 18, 15, 66, 59, 97, 58]
    print '>>random list: {}'.format(lst)
    splayt = SplayTree()
    map(lambda x: splayt.insert(x), lst)
    print '>>Splay tree structure:\n{}'.format(splayt)
    print '>>Splay tree inorder:'
    splayt.inorder()
    print
    assert splayt.isBST()

    #splayt.find(2)
    finds = [random.randint(0, 100) for _ in xrange(10)]
    #finds = [74, 93, 58, 89, 43, 91, 88, 98, 55, 56]
    print 'finds {}'.format(finds)
    map(lambda x: splayt.find(x), finds)

    print '>> test delete'
    deletes = [random.randint(0, 100) for i in xrange(10)]
    #deletes = [91, 58]
    print 'deletes: {}'.format(deletes)
    map(lambda x: splayt.delete(x), deletes)
    print 'after bunch of deletes: '
    print '>>Splay tree structure:\n{}'.format(splayt)
    print '>>Splay tree inorder:'
    splayt.inorder()
    print
    assert splayt.isBST()
