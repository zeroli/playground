import random
import copy

def partition(data, l, r):
    if l >= r: return l
    i, j = l, l
    p = r - 1
    while j < r:
        if data[j] < data[p]:
            data[i], data[j] = data[j], data[i]
            i += 1
        j += 1
    # need put pivot at i location
    data[i], data[p] = data[p], data[i]
    # all data before i smaller than p[i]
    return i

def select(data, k):
    """
    select k-th element from data sequence, return its data value
    """
    print '>>select {}-th small element from {}'.format(k, data)
    assert k < len(data), 'error: k-th {} must be smaller than len {}'.format(k, len(data))

    def _select(data, k, l, r):
        p = partition(data, l, r)
        if k == p:
            return data[p]
        elif k < p:
            # look up left smaller ones
            return _select(data, k, l, p)
        else:
            return _select(data, k, p+1, r)

    def _select_iterative(data, k, l, r):
        while l < r:
            p = partition(data, l, r)
            if k == p:
                return data[p]
            elif k < p:
                r = p
            else:
                l = p + 1
        return data[l]

    kval1 = _select(copy.copy(data), k, 0, len(data))
    kval2 = _select_iterative(copy.copy(data), k, 0, len(data))
    assert kval1 == kval2
    print 'k: {}-th value {}'.format(k, kval1)
    return kval1

if __name__ == '__main__':
    data = [random.randint(1, 100) for i in xrange(1, 20)]
    k = random.randint(1, 20)
    kval = select(data, k)
    data = sorted(data)
    print 'sorted data: {}'.format(data)
    assert data[k] == kval
