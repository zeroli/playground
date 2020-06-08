import random

"""
find min/max element in one array
"""

def min_max_elements(arr):
    min_, max_ = arr[0], arr[0]

    for i in xrange(1, len(arr)):
        if arr[i] < min_:
            min_ = arr[i]
        elif arr[i] > max_:
            max_ = arr[i]
    return min_, max_

#compare one pair by one pair to reduce loop by 2
#if n is odd, 3 * (n-1) / 2
#if n is even, 1 + 3*(n-2)/2 = 3n/2-2
def min_max_elements_pairbypair(arr):
    n = len(arr)
    beg = 0
    if n % 2 == 0:  # even
        min_ = min(arr[0], arr[1])
        max_ = max(arr[0], arr[1])
        beg = 2
    else: # odd
        min_, max_ = arr[0], arr[0]
        beg = 1

    # loop most (n-1)/2 * 3 iterations
    for i in xrange(beg, n, 2):
        if arr[i] > arr[i+1]:
            if arr[i] > max_:
                max_ = arr[i]
            if arr[i+1] < min_:
                min_ = arr[i+1]
        else:
            if arr[i+1] > max_:
                max_ = arr[i+1]
            if arr[i] < min_:
                min_ = arr[i]
    return min_, max_

if __name__ == '__main__':
    data = [random.randrange(-100, 100) for i in xrange(1, 21)]
    print 'input: {}'.format(data)
    print 'naive: min: {}, max: {}'.format(*min_max_elements(data))
    print 'pair/pair: min: {}, max: {}'.format(*min_max_elements_pairbypair(data))
