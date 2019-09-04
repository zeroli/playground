def expr_infix_to_postfix(expr):
    precedence = {
        '+' : 0,
        '-' : 0,
        '*' : 1,
        '/' : 1,
        '(' : 2,
    }

    ops = ('+', '-', '*', '/', '(', ')')
    print '>>infix expr: {}'.format(expr)
    s = []
    o = []
    for c in expr:
        if c == ' ': continue
        if c not in ops:
            o.append(c)
        else:
            if c == ')':
                while len(s) and s[-1] != '(':
                    o.append(s.pop())
                assert len(s), 'ERROR: no ( to pair'
                s.pop()
            else:
                while (len(s) and s[-1] != '(' and
                    precedence[s[-1]] >= precedence[c]):
                    o.append(s.pop())
                s.append(c)
    while len(s):
        o.append(s.pop())
    ret = ''.join(o)
    print '>>postfix expr: {}'.format(ret)
    return ret

if __name__ == '__main__':
    expr = 'a + b * c + (d * e + f) * g'
    expr_infix_to_postfix(expr)
