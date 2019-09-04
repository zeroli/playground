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
            s.append(Tree(c, s.pop(), s.pop()))
    assert len(s) == 1, 'Error: postfix expr {} invalid'.format(postfix_expr)
    s[0].inorder()

if __name__ == '__main__':
    postfix_expr = 'a b + c d e + * *'
    build_eval_tree(postfix_expr)


