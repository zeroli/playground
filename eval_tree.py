class Tree(object):
    def __init__(self, val, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right

    def inorder(self):
        def _inorder(tree):
            if not tree: return
            _inorder(tree.left)
            print tree.val,
            _inorder(tree.right)
        _inorder(self)

    def postorder(self):
        def _postorder(tree):
            if not tree: return
            _postorder(tree.left)
            _postorder(tree.right)
            print tree.val,
        _postorder(self)

def build_eval_tree(postfix_expr):
    print '>>postfix expr: {}'.format(postfix_expr)
    ops = ('+', '-', '*', '/')
    s = []
    for c in postfix_expr:
        if c == ' ': continue
        if c not in ops: # operand
            s.append(Tree(c))
        else:
            assert len(s) >= 2, 'Error: no operands in stack for operator {}'.format(c)
            t1 = s.pop()
            t2 = s.pop()
            s.append(Tree(c, t2, t1))
    assert len(s) == 1, 'Error: postfix expr {} invalid'.format(postfix_expr)
    s[0].inorder()

if __name__ == '__main__':
    postfix_expr = 'a b + c d e + * *'
    build_eval_tree(postfix_expr)


