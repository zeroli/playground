import random

"""implementation for max subsum problems"""

"""runtime: O(n^3)"""
def naive_maxsubsum(data):
    maxsum = 0
    maxrange = (-1, -1)
    for i in xrange(len(data)):
        for j in xrange(i, len(data)):
            thissum = 0
            for k in xrange(i, j+1):
                thissum += data[k]
            if thissum > maxsum:
                maxsum = thissum
                maxrange = (i, k)
    print '>>naive method: sum {}, range {}'.format(maxsum, maxrange)
    return maxsum, maxrange

"""runtime improved to O(n^2)"""
def naive_maxsubsum_improved(data):
    maxsum = 0
    maxrange = (-1, -1)
    for i in xrange(len(data)):
        thissum = 0
        for j in xrange(i, len(data)):
            thissum += data[j]
            if thissum > maxsum:
                maxsum = thissum
                maxrange = (i, j)
    print '>>naive method improved: sum {}, range {}'.format(maxsum, maxrange)
    return maxsum, maxrange

"""runtime improved to O(nlg(n))"""
def maxsubsum_divide_conque(data):
    def _maxsubsum(data, l, r):
        if l >= r:
            return data[l], (l, l)

        mid = l + (r-l) / 2
        leftmaxsum, leftrange = _maxsubsum(data, l, mid)
        rightmaxsum, rightrange = _maxsubsum(data, mid+1, r)

        leftborder_maxsum = 0
        leftborder_sum = 0
        leftborder_range = (-1, -1)
        left_i = mid
        while left_i >= l:
            leftborder_sum += data[left_i]
            if leftborder_sum > leftborder_maxsum:
                leftborder_maxsum = leftborder_sum
                leftborder_range = (left_i, mid)
            left_i -= 1

        rightborder_maxsum = 0
        rightborder_sum = 0
        rightborder_range = (-1, -1)
        right_i = mid + 1
        while right_i <= r:
            rightborder_sum += data[right_i]
            if rightborder_sum > rightborder_maxsum:
                rightborder_maxsum = rightborder_sum
                rightborder_range = (mid+1, right_i)
            right_i += 1
        if leftmaxsum >= max(rightmaxsum, leftborder_maxsum+rightborder_maxsum):
            return leftmaxsum, leftrange
        elif rightmaxsum >= max(leftmaxsum, leftborder_maxsum+rightborder_maxsum):
            return rightmaxsum, rightrange
        elif leftborder_maxsum+rightborder_maxsum >= max(leftmaxsum, rightmaxsum):
            return leftborder_maxsum+rightborder_maxsum, (leftborder_range[0], rightborder_range[1])
        else:
            return -1, (-1, -1)

    maxsum, maxrange = _maxsubsum(data, 0, len(data)-1)
    print '>>divide-concur method: sum {}, range {}'.format(maxsum, maxrange)
    return maxsum, maxrange

"""runtime improved to O(n)"""
def maxsubsum_linear(data):
    maxsum = 0
    maxrange = [-1, -1]
    subrange = -1
    thissum = 0
    for i in xrange(len(data)):
        thissum += data[i]
        if thissum > maxsum:
            maxsum = thissum
            if subrange >= 0:
                maxrange[0] = subrange
            else:
                if maxrange[0] < 0: maxrange[0] = 0
            maxrange[1] = i
        elif thissum < 0:
            thissum = 0
            subrange = i + 1
    maxrange = tuple(maxrange)
    print '>>linear method: sum {}, range {}'.format(maxsum, maxrange)
    return maxsum, maxrange

if __name__ == '__main__':
    data = [random.randrange(-100, 100) for i in xrange(1, 20)]
    #data = [4, -3, 5, -2, -1, 2, 6, -2]
    print '>>max subsum, input: {}'.format(data)
    maxsum1, maxrange1 = naive_maxsubsum(data)
    maxsum2, maxrange2 = naive_maxsubsum_improved(data)
    maxsum3, maxrange3 = maxsubsum_divide_conque(data)
    maxsum4, maxrange4 = maxsubsum_linear(data)
    assert maxsum1 == maxsum2 and maxrange1 == maxrange2
    assert maxsum1 == maxsum3 and maxrange1 == maxrange3
    assert maxsum1 == maxsum4 and maxrange1 == maxrange4
