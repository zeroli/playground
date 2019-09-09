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
        """Refer to <<Data structure and algorithm analysis in C>>
        The runtime complexity will be O(N)
        """
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

    def _select_maxheap(data, k):
        """Refer to <<Data structure and algorithm analysis in C>>
        The runtime complexity will be O(k + (N-k) * log(k)) = O(Nlog(k))
        """
        import heap
        m = k+1
        maxh = heap.MaxHeap(data[0:m])
        while m < len(data):
            if data[m] < maxh.peek():
                maxh.deleteMax()
                maxh.insert(data[m])
            m += 1
        return maxh.peek()

    kval1 = _select(copy.deepcopy(data), k, 0, len(data))
    kval2 = _select_iterative(copy.deepcopy(data), k, 0, len(data))
    kval3 = _select_maxheap(copy.deepcopy(data), k)

    assert kval1 == kval2, 'ERROR: kva1 ({}) != kval2 ({})'.format(kval1, kval2)
    assert kval1 == kval3, 'ERROR: kva1 ({}) != kval3 ({})'.format(kval1, kval3)
    print 'k: {}-th value {}'.format(k, kval1)
    return kval1

if __name__ == '__main__':
    #data = [random.randint(1, 100) for i in xrange(1, 20)]
    data = [77, 84, 40, 35, 5, 12, 63, 33, 77, 94, 19, 100, 96, 16, 66, 77, 91, 11, 21]
    print '>>random data: {}'.format(data)
    print 'sorted data: {}'.format(sorted(data))
    k = 11 #random.randint(1, 20)
    kval = select(data, k)

    assert sorted(data)[k] == kval
