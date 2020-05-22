import random

"""
vertical sum of binary tree
"""

class TreeNode(object):
    def __init__(self, data, left = None, right = None):
        self._data = data
        self._left = left
        self._right = right

    @property
    def left(self):
        return self._left

    @property
    def right(self):
        return self._right

class BinaryTree(object):
    def __init__(self, root):
        self._root = root

    def __str__(self):
        def preorder(root, s):
            if not root: return
            s.append(str(root._data))
            preorder(root.left, s)
            preorder(root.right, s)
        s = []
        preorder(self._root, s)
        return ' '.join(s)

    def printVerticalSum(self):
        def _printVerticalSum(root, d, move):
            if not root: return

            _printVerticalSum(root.left, d, move - 1)

            if move in d:
                d[move] += root._data
            else:
                d[move] = root._data

            _printVerticalSum(root.right, d, move + 1)
        d = dict()
        _printVerticalSum(self._root, d, 0)
        import collections
        d = collections.OrderedDict(sorted(d.items()))
        print 'vertical sums: {}'.format(d.values())

if __name__ == '__main__':
    root = TreeNode(40,
                    TreeNode(20,
                            TreeNode(10),
                            TreeNode(30, TreeNode(5))),
                    TreeNode(60,
                            TreeNode(50, None, TreeNode(55)),
                            TreeNode(70))
                )
    bt = BinaryTree(root)
    print 'binary tree preorder: {}'.format(bt)
    bt.printVerticalSum()
