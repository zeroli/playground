import random
import utils
import binary_add

def binary_multiply(A, B):
    if len(A) > len(B):
        utils.prepend_fill(B, len(A) - len(B))
    else:
        utils.prepend_fill(A, len(B) - len(A))

    print 'A: {}'.format(A)
    print 'B: {}'.format(B)
    print '===A * B==='

    n = len(A)
    A.reverse()
    B.reverse()

    C = [0] * 2 * n
    for i in xrange(0, n):
        K = [B[i] * A[j] for j in xrange(0, n)]
        utils.prepend_fill(K, i)
        utils.append_fill(K, 2*n - len(K))
        K.reverse()
        C = binary_add.binary_add(K, C)

    print 'C: {} = {}'.format(C, utils.binlist2num(C))
    return C

if __name__ == '__main__':
    Anum = random.randint(0, 100)
    Bnum = random.randint(0, 100)
    print 'Anum: {}, Bnum: {}'.format(Anum, Bnum)
    A = utils.num2binlist(Anum)
    B = utils.num2binlist(Bnum)
    C = binary_multiply(A, B)
    assert Anum * Bnum == utils.binlist2num(C)
