import random

def binary_search_recursive(data, key):
    """make sure 'data' is sorted in ascending order"""
    print '>>binary search recursive: {}'.format(data)

    def _binary_search(data, l, r, key):
        """l => left, r => right, not including"""
        if l >= r:
            return -1 if key != data[l] else l
        m = l + (r - l) / 2
        if key == data[m]:
            return m
        elif key > data[m]:
            return _binary_search(data, m + 1, r, key)
        else:
            return _binary_search(data, l, m, key)

    index = _binary_search(data, 0, len(data), key)
    print '>>found {} at index {}'.format(key, index)

def binary_search_iterative(data, key):
    """make sure 'data' is sorted in ascending order"""
    print '>>binary search iterative: {}'.format(data)

    def _binary_search(data, l, r, key):
        """l => left, r => right, not including"""
        if l >= r:
            return -1 if key != data[l] else l
        while l < r:
            m = l + (r - l) / 2
            if key == data[m]:
                return m
            elif key > data[m]:
                l = m + 1
            else:
                r = m
        return -1

    index = _binary_search(data, 0, len(data), key)
    print '>>found {} at index {}'.format(key, index)

if __name__ == '__main__':
    num = 21
    data = [random.randint(0, 100) for i in xrange(0, num)]
    key = data[random.randint(0, num)]
    data = sorted(data)
    binary_search_recursive(data, key)
    binary_search_iterative(data, key)
