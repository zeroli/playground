import random

def divide(x, y):
    """use recursive method to calculate division of x by y"""
    print 'x: {}, y: {}'.format(x, y)
    print 'x/y = '
    if x == 0:
        return (0, 0)
    q, r = divide(x//2, y)
    q *= 2
    r *= 2
    if x & 1: r += 1
    if r >= y:
        r -= y
        q += 1
    print 'q, r = {}, {}'.format(q, r)
    return (q, r)

if __name__ == '__main__':
    Anum = random.randint(1, 100)
    Bnum = random.randint(1, 100)
    q, r = divide(Anum, Bnum)
    assert q * Bnum + r == Anum
