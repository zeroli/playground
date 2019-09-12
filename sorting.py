import os, sys, random
import copy

def insertionSort(data):
    """
    runtime complixity:
    1) average: O(N^2/4) for comparison, and O(N^2/4) for exchange
    2) worst case: O(N^2/2) for comparison, and O(N^2/2) for exchange, inversed order
    3) best case: O(N) for comparison, and 0 exchange: sorted order
    faster than any other sorting algo, for partially sorted data or sorted data
    """
    print '<<insertion sort>>\n{}'.format(data)
    for j in xrange(1, len(data)):
        k = data[j]
        i = j - 1
        while i >= 0 and data[i] > k:
            data[i+1] = data[i]
            i -= 1
        data[i+1] = k
    print '>>>\n{}'.format(data)
    return data

def insertionSortBS(data):
    print '<<insertion sort with binary search insertion location>>\n{}'.format(data)
    for j in xrange(1, len(data)):
        k = data[j]
        i = 0 # insertion location where smaller than k, and will insert before this one
        l = 0
        r = j
        while l < r:
            i = l + (r - l) / 2 # insertion position
            if k > data[i]:
                i += 1 # if only one element left, need insert before the next one
                l = i
            elif k < data[i]:
                r = i
            else:
                break
        while j > i:
            data[j] = data[j-1]
            j -= 1
        data[i] = k
    print '>>>\n{}'.format(data)
    return data

def mergeSort(data):
    print '<<merge sort>>\n{}'.format(data)
    def _mergeSort(data, l, r):
        #print 'l: {}, r: {}'.format(l, r)
        if r - l == 1: return
        p = l + (r - l) / 2
        _mergeSort(data, l, p)
        _mergeSort(data, p, r)

        #append a sentinel to simplify code, refer to <<Introducton to algorithms>> book, section 2.3
        data1 = [data[i] for i in xrange(l, p)]
        data1.append(sys.maxint)
        data2 = [data[i] for i in xrange(p, r)]
        data2.append(sys.maxint)
        #print 'data1: {}, data2: {}'.format(data1, data2)

        i = 0
        j = 0
        m = l
        while m < r:
            if data1[i] < data2[j]:
                data[m] = data1[i]
                i += 1
            else:
                data[m] = data2[j]
                j += 1
            m += 1
        # original implementation code
        # while i < len(data1) and j < len(data2):
        #     if data1[i] < data2[j]:
        #         data[l+m] = data1[i]
        #         i += 1
        #     else:
        #         data[l+m] = data2[j]
        #         j += 1
        #     m += 1

        # for k in xrange(i, len(data1)):
        #     data[l+m] = data1[k]
        #     m += 1
        # for k in xrange(j, len(data2)):
        #     data[l+m] = data2[k]
        #     m += 1

    _mergeSort(data, 0, len(data))
    print '>>>\n{}'.format(data)
    return data

def countSort(data):
    print '<<count sort>>\n{}'.format(data)

    # pre-calcuate the data distribution range
    K = max(data) + 1
    C = [0] * K
    for x in data:
        C[x] = C[x] + 1
    for i in xrange(1, len(C)):
        C[i] = C[i-1] + C[i]
    data1 = [0] * len(data)
    for x in data:
        data1[C[x]-1] = x
        C[x] -= 1
    data = data1
    print '>>>\n{}'.format(data)
    return data

def shellSort(data):
    """refer to book <<Algorithm 4>>, 2.1 section
    based on the truth that insertion sort is fast in partially sorted data
    we can make any random order data to be partially sorted, by using different sampling
    first sampling data using big interval, and then smaller and smaller interval, until the interval =1
    to run final insertion sort
    """
    print '<<shell sort>>\n{}'.format(data)
    N = len(data)
    h = 1
    while h < N/3: h = h * 3 + 1
    #first big interval, then smaller interval, etc, until h = 1 for regular insertion sort
    #the generated increasing intervals: 1, 4, 13, 40, 121, ... (N/3)
    while h >= 1:
        #perform h-sort the whole array
        #sort several sub-arrays (N/h) in parrallel
        for j in xrange(h, N):
            # i = j
            # while i >= h and data[i] < data[i-h]:
            #     data[i], data[i-h] = data[i-h], data[i]
            #     i -= h

            k = data[j]
            i = j - h
            while i >= 0 and data[i] > k:
                data[i + h] = data[i]
                i -= h
            data[i + h] = k
        h /= 3
    print '>>>\n{}'.format(data)
    return data

def quickSort(data):
    print '<<quick sort>>\n{}'.format(data)
    import selection as selectalgo
    def _quickSort(data, l, r):
        if r - l <= 1: return l
        p = selectalgo.partition(data, l, r)
        _quickSort(data, l, p)
        _quickSort(data, p+1, r)
    _quickSort(data, 0, len(data))
    print '>>>\n{}'.format(data)
    return data

def heapSort(data):
    print '<<heap sort>>\n{}'.format(data)
    import heap as heapalgo
    maxh = heapalgo.MaxHeap(data)
    N = len(data)
    while N > 0:
        data[N-1] = maxh.deleteMax()
        N -= 1
    print '>>>\n{}'.format(data)
    return data

if __name__ == '__main__':
    data = [random.randrange(0, 100) for i in xrange(1, 20)]
    data0 = sorted(data)
    data1 = insertionSort(copy.deepcopy(data))
    data2 = insertionSortBS(copy.deepcopy(data))
    data3 = mergeSort(copy.deepcopy(data))
    data4 = countSort(copy.deepcopy(data))
    data5 = shellSort(copy.deepcopy(data))
    data6 = quickSort(copy.deepcopy(data))
    data7 = heapSort(copy.deepcopy(data))
    assert data0 == data1
    assert data0 == data2
    assert data0 == data3
    assert data0 == data4
    assert data0 == data5
    assert data0 == data6
    assert data0 == data7
