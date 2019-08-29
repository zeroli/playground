import random

digit = 2 # could be changed to any positive number
def binary_add(A, B):
    assert len(A) == len(B)
    print 'A:    {}'.format(A)
    print 'B:    {}'.format(B)

    A.reverse()
    B.reverse()
    c = 0
    C = [0] * len(A)

    for i in xrange(0, len(A)):
        C[i] = A[i] + B[i] + c
        c = 0
        if C[i] >= digit:
            C[i] -= digit
            c = 1
    if c > 0:
        C.append(c)
    C.reverse()
    print 'C: {}{}'.format(' ' if c > 0 else '   ', C)
    return C


if __name__ == '__main__':
    A = [random.randint(0, digit-1) for i in xrange(1, 20)]
    B = [random.randint(0, digit-1) for i in xrange(1, 20)]
    binary_add(A, B)
