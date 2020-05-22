import random

"""
get the minimum free id based on allocated ids
ids are positive numbers starting from 0
"""

def naive_min_free(ids):
    x = 0
    while True:
        if x not in ids:
            return x
        x += 1

def better_min_free(ids):
    n = len(ids)
    exists = [False] * (n+1)
    for x in ids:
        if x < n:
            exists[x] = True
    for i, e in enumerate(exists):
        if e == False:
            return i
    return n

#use divide-and-conquer method
def divide_and_conquer(ids):
    n = len(ids)
    lo, hi = 0, n-1
    while lo <= hi:
        m = lo + (hi - lo) / 2
        print 'lo: {}, hi {}, m: {}, ids: {}'.format(lo, hi, m, ids[lo:hi+1])
        #partition based on m
        left = lo # how many <= m for location
        for right in xrange(lo, hi+1):
            if ids[right] <= m: # try to make m place exact number at that location
                ids[left], ids[right] = ids[right], ids[left]
                left += 1
        print 'left: {}'.format(left)
        if left == m + 1: # left part is full, all ids are there, so free id is in right part
            lo = m + 1
        else:  # first free is in left part
            hi = left - 1 # NOT m - 1
    return lo

if __name__ == '__main__':
    #ids = [random.randint(0, 100000) for i in xrange(1000)]
    #ids = list(set(ids))
    ids = [1, 4, 0, 3, 2, 6, 7, 9, 10, 5, 11, 12, 19, 8, 13, 14, 15, 20]
    print 'ids: {}'.format(ids)
    print 'naive min-free: {}'.format(naive_min_free(ids))
    print 'better min-free: {}'.format(better_min_free(ids))
    print 'divide-and-conquer min-free: {}'.format(divide_and_conquer(ids))
