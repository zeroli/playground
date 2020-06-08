import os, sys, random

def kmp_match(T, P):
    """
    running time is O(|T| + |P|) in worst case
    """
    print 'kmp matching...'
    n = len(T)
    m = len(P)

    def build_failfunc(P):
        m = len(P)
        fs = [0] * m
        j = 0
        i = 1
        fs[0] = 0
        while i < m:
            if P[i] == P[j]:
                fs[i] = j + 1
                j += 1
                i += 1
            elif j > 0:
                j = fs[j-1]
            else: # j == 0
                fs[i] = 0
                i += 1

        return fs

    fs = build_failfunc(P)
    i = 0
    j = 0
    while i < n:
        if T[i] == P[j]:
            if j == m - 1:
                print 'found at {}'.format(i - m + 1)
                return i - m + 1
            i += 1
            j += 1
        elif j > 0:
            j = fs[j-1]
        else: # j == 0
            i += 1
    print 'failed to match'
    return -1

def bm_match(T, P):
    """
    running time is O(|T|*|P|) in worst case
    """
    print 'bm match ...'
    n = len(T)
    m = len(P)

    def build_last(P):
        last = [-1] * 256
        pos = 0
        for i in P:
            last[ord(i)] = pos
            pos += 1
        return last

    last = build_last(P)
    i = m - 1
    j = m - 1
    while i < n:
        if T[i] == P[j]:
            if j == 0:
                print 'found at {}'.format(i)
                return i
            j -= 1
            i -= 1
        else:
            i += m - min(j, 1 + last[ord(T[i])])
            j = m - 1
    print 'failed to match'
    return -1

if __name__ == '__main__':
    text = 'xadafdababc1234'
    pat = 'xababc'
    kmp_match(text, pat)
    bm_match(text, pat)
