import random

"""
multiple and divide algorithm for integer with n bits
"""

def multiply(x, y):
    """
    x * y = 2 * x * (y/2), if y is even
    x * y = x + 2 * x * (y/2), if y is odd
    """
    if y == 1: return x
    t = multiply(x, y >> 1)
    t *= 2
    if y & 1:
        t += x
    return t

def divide(x, y):
    """
    x / y = 2 * ((x/2) / y), if x is even
    x / y = 2 * ((x/2) / y) + 1 * y, if x is odd
    """
    assert y != 0
    if x == 1: return 0, 1
    q, r = divide(x >> 1, y)
    q *= 2
    r *= 2
    if x & 1: r += 1
    if r >= y:
        q += 1
        r -= y
    return q, r

if __name__ == '__main__':
    x = random.randint(1, 100)
    y = random.randint(1, 100)
    z = x * y
    t = multiply(x, y)
    print 'multiply({}, {}) = {}'.format(x, y, t)
    assert z == t, 'multiply({}, {}) = {}, different from {}*{}={}'.format(x, y, t, x, y, z)

    z = x / y, x % y
    t = divide(x, y)
    print 'divide({}, {}) = {}'.format(x, y, t)
    assert z == t, 'divide({}, {}) = {}, different from {}/{}={}'.format(x, y, t, x, y, z)
