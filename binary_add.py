import random
import utils

base = 2 # could be changed to any positive number
def binary_add(A, B):
    if len(A) > len(B):
        utils.prepend_fill(B, len(A) - len(B))
    else:
        utils.prepend_fill(A, len(B) - len(A))

    print 'A:    {}'.format(A)
    print 'B:    {}'.format(B)
    print '===A + B==='

    A.reverse()
    B.reverse()
    c = 0
    C = [0] * len(A)

    for i in xrange(0, len(A)):
        C[i] = A[i] + B[i] + c
        c = 0
        if C[i] >= base:
            C[i] -= base
            c = 1
    if c > 0:
        C.append(c)
    C.reverse()
    print 'C: {}{} = {}'.format(' ' if c > 0 else '   ', C, utils.binlist2num(C))
    return C


if __name__ == '__main__':
    Anum = random.randint(0, 100)
    Bnum = random.randint(0, 100)
    print 'Anum: {}, Bnum: {}'.format(Anum, Bnum)
    A = utils.num2binlist(Anum)
    B = utils.num2binlist(Bnum)
    C = binary_add(A, B)
    assert Anum + Bnum == utils.binlist2num(C)
