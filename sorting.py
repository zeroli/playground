import os, sys, random
import copy

def insertionSort(data):
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

if __name__ == '__main__':
    data = [random.randint(1, 100) for i in xrange(1, 20)]
    data1 = insertionSort(copy.deepcopy(data))
    data2 = insertionSortBS(copy.deepcopy(data))
    data3 = mergeSort(copy.deepcopy(data))
    assert data1 == data2
    assert data2 == data3
