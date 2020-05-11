import os, sys, random

class TreeNode(object):
    def __init__(self, value, left=None, right=None):
        self.parent = None
        self.value = value
        self.left = self.right = None
        if left: self.assignleft(left)
        if right: self.assignright(right)

    def __repr__(self):
        return '{}'.format(str(self.value))

    def assignleft(self, left):
        self.left = left
        left.parent = self

    def assignright(self, right):
        self.right = right
        right.parent = self

    def isleaf(self):
        return self.left == None and self.right == None

class BinaryTree(object):
    def __init__(self, root):
        self.root = root

    def preorder(self):
        def _preorder(root):
            if root == None: return
            print root,
            _preorder(root.left)
            _preorder(root.right)
        _preorder(self.root)

    def preorder_iter(self):
        s = []
        p = self.root
        s.append(p)
        while len(s):
            p = s.pop()
            print p,
            if p.right:
                s.append(p.right)
            if p.left:
                s.append(p.left)

    def preorder_iter2(self):
        s = []
        p = self.root
        while p or len(s):
            if p:
                print p,
                s.append(p)
                p = p.left
            else:
                p = s.pop()
                p = p.right

    def postorder(self):
        def _postorder(root):
            if root == None: return
            _postorder(root.left)
            _postorder(root.right)
            print root,
        _postorder(self.root)

    def postorder_iter(self):
        s = []
        prev = None
        s.append(self.root)
        while len(s):
            p = s[-1]
            if ((p.left == None and p.right == None) or
                (prev and (prev == p.left or prev == p.right))):
                print p, # left node or 2 childrens traversed already
                s.pop()
                prev = p
            else:
                if p.right:
                    s.append(p.right)
                if p.left:
                    s.append(p.left)

    def postorder_iter2(self):
        s1 = []
        s2 = []
        s1.append(self.root)
        while len(s1):
            p = s1.pop()
            s2.append(p)
            if p.left:
                s1.append(p.left)
            if p.right:
                s1.append(p.right)
        while len(s2):
            p = s2.pop()
            print p,

    # use double push for one stack
    def postorder_iter3(self):
        s = []
        s.append(self.root)
        s.append(self.root)
        while len(s):
            p = s.pop()
            if len(s) and s[-1] == p:
                if p.right:
                    s.append(p.right)
                    s.append(p.right)
                if p.left:
                    s.append(p.left)
                    s.append(p.left)
            else:
                print p,

    def inorder(self):
        def _inorder(root):
            if root == None: return
            if root.isleaf():
                print root,
            else:
                print '(',
                _inorder(root.left)
                print root,
                _inorder(root.right)
                print ')',
        _inorder(self.root)

    def inorder_iter(self):
        s = []
        p = self.root
        while p or len(s):
            if p:
                s.append(p)
                p = p.left
            else:
                p = s.pop()
                print p,
                p = p.right

    def level_order(self):
        q = []
        q.append(self.root)
        while len(q):
            p = q.pop(0)
            print p,
            if p.left:
                q.append(p.left)
            if p.right:
                q.append(p.right)

def build_infix_expr():
    n1 = TreeNode('/',
                left=TreeNode('x',
                        left=TreeNode('+', TreeNode('3'), TreeNode('1')),
                        right=TreeNode('3')),
                right=TreeNode('+',
                        left=TreeNode('-', TreeNode('9'), TreeNode('5')),
                        right=TreeNode('2'))
                )
    n2 = TreeNode('+',
                left=TreeNode('x',
                            left=TreeNode('3'),
                            right=TreeNode('-', TreeNode('7'), TreeNode('4'))),
                right=TreeNode('6')
                )
    root = TreeNode('-', n1, n2)
    bt = BinaryTree(root)
    bt.inorder()
    print

def traverse_tree():
    root = TreeNode(1,
                left = TreeNode(2,
                            left = TreeNode(4),
                            right = TreeNode(5)),
                right = TreeNode(3,
                            left = TreeNode(6),
                            right = None)
                )
    bt = BinaryTree(root)
    bt.preorder()
    print
    bt.preorder_iter()
    print
    bt.preorder_iter2()
    print
    bt.inorder_iter()
    print
    bt.postorder()
    print
    bt.postorder_iter()
    print
    bt.postorder_iter2()
    print
    bt.postorder_iter3()
    print
    bt.level_order()
    print

if __name__ == '__main__':
    build_infix_expr()
    traverse_tree()
