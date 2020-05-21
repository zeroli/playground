import random

def binary_search_recursive(data, key):
    """make sure 'data' is sorted in ascending order"""
    print '>>binary search recursive: {}'.format(data)

    def _binary_search(data, l, r, key):
        """l => first one element index
            r => last one element index including
        """
        if l > r:
            return -1
        m = l + (r - l) / 2
        if key == data[m]:
            return m
        elif key > data[m]:
            return _binary_search(data, m + 1, r, key)
        else:
            return _binary_search(data, l, m - 1, key)

    index = _binary_search(data, 0, len(data) - 1, key)
    print '>>found {} at index {}'.format(key, index)

def binary_search_iterative(data, key):
    """make sure 'data' is sorted in ascending order"""
    print '>>binary search iterative: {}'.format(data)

    def _binary_search(data, l, r, key):
        """l => first one element index
            r => last one element index including
        """
        while l <= r:
            m = l + (r - l) / 2
            if key == data[m]:
                return m
            elif key > data[m]:
                l = m + 1
            else:
                r = m - 1
        return -1

    index = _binary_search(data, 0, len(data) - 1, key)
    print '>>found {} at index {}'.format(key, index)

#if searched 'key' found, lower bound is the first one equal to it
#otherwise, the smallest one larger than it
#in other words, the first one larger than or equal to 'key'
def bs_lowerbound(data, key):
    def _binary_search(data, l, r, key):
        """l => first one element index
            r => last one element index including
        """
        while l <= r:
            m = l + (r - l) / 2
            if key > data[m]:
                l = m + 1
            else:  # key <= data[m]
                r = m - 1
        return l
    index = _binary_search(data, 0, len(data) - 1, key)
    print '>>found lower bound {} at index {}'.format(key, index)

#the smallest one larger than searched 'key'
#the first one larger than 'key'
def bs_upperbound(data, key):
    def _binary_search(data, l, r, key):
        """l => first one element index
            r => last one element index including
        """
        while l <= r:
            m = l + (r - l) / 2
            if key < data[m]:
                r = m - 1
            else:  # key >= data[m]
                l = m + 1
        return l
    index = _binary_search(data, 0, len(data) - 1, key)
    print '>>found upper bound {} at index {}'.format(key, index)

if __name__ == '__main__':
    num = 21
    data = [random.randint(0, 100) for i in xrange(0, num)]
    key = data[random.randint(0, num-1)]
    data = sorted(data)
    binary_search_recursive(data, key)
    binary_search_iterative(data, key)
    bs_lowerbound(data, key)
    bs_upperbound(data, key)
