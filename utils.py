def num2binlist(num):
    return [int(x) for x in bin(num)[2:]]

def binlist2num(l):
    return int(''.join([str(i) for i in l]), 2)

def append_fill(l, n):
    l.extend([0] * n)

def prepend_fill(l, n):
    for _ in xrange(n):
        l.insert(0, 0)
