import random

"""
find min/max from one sequence, together.
runtime complexitiy: O(3n/2)
"""

def find_minmax(data):
    print '>> find min/max together: {}'.format(data)
    n = len(data)

    def _find_minmax(data, i, minval, maxval):
        while i < n:
            if data[i] < data[i+1]:
                minval = minval if minval < data[i] else data[i]
                maxval = maxval if maxval > data[i+1] else data[i+1]
            else:
                minval = minval if minval < data[i+1] else data[i+1]
                maxval = maxval if maxval > data[i] else data[i]
            i += 2
        return minval, maxval

    if n & 1 == 0:
        minval, maxval = min(data[0], data[1]), max(data[0], data[1])
        minval, maxval = _find_minmax(data, 2, minval, maxval)
    else:
        minval, maxval = data[0], data[0]
        minval, maxval = _find_minmax(data, 1, minval, maxval)

    print 'min: {}, max: {}'.format(minval, maxval)
    return minval, maxval

if __name__ == '__main__':
    data = [random.randint(1, 100) for i in xrange(1, 20)]
    minval, maxval = find_minmax(data)
    assert minval == min(data)
    assert maxval == max(data)
