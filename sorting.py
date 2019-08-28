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

def mergeSort(data):
    print '<<merge sort>>\n{}'.format(data)
    def _mergeSort(data, l, r):
        #print 'l: {}, r: {}'.format(l, r)
        if r - l == 1: return [data[l],]
        data1 = _mergeSort(data, l, l+(r-l)/2)
        data2 = _mergeSort(data, l+(r-l)/2, r)

        merged = []
        i = 0
        j = 0
        while i < len(data1) and j < len(data2):
            if data1[i] < data2[j]:
                merged.append(data1[i])
                i += 1
            else:
                merged.append(data2[j])
                j += 1
        
        for k in xrange(i, len(data1)):
            merged.append(data1[k])
        for k in xrange(j, len(data2)):
            merged.append(data2[k])
        return merged
    merged = _mergeSort(data, 0, len(data))
    print '>>>\n{}'.format(merged)

if __name__ == '__main__':
    data = [random.randint(1, 100) for i in xrange(1, 21)]
    insertionSort(copy.deepcopy(data))
    mergeSort(copy.deepcopy(data))