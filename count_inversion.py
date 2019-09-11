import random
import copy
import sys

def mergeInversion(data):
    print '<<merge inversion count>>\n{}'.format(data)
    def _mergeInversion(data, l, r):
        if r - l == 1: return 0
        p = l + (r - l) / 2
        cnt = 0
        cnt += _mergeInversion(data, l, p)
        cnt += _mergeInversion(data, p, r)

        #append a sentinel to simplify code, refer to <<Introducton to algorithms>> book, section 2.3
        data1 = [data[i] for i in xrange(l, p)]
        data1.append(sys.maxint)
        data2 = [data[i] for i in xrange(p, r)]
        data2.append(sys.maxint)
        #print 'data1: {}, data2: {}'.format(data1, data2)
        print 'l: {}, r: {}, data: {}'.format(l, r, data[l:r]),
        i = 0
        j = 0
        m = l
        while m < r:
            """
            if location 'i' in data1 is bigger than location 'j' in data2, then any location >= i in data1
            will be bigger than location 'j' in data2, due to data1 is in increasing order
            """
            if data1[i] > data2[j]:
                cnt += len(data1) - i - 1 # here we append maxint to data1, so we minus 1 finally
            if data1[i] < data2[j]:
                data[m] = data1[i]
                i += 1
            else:
                data[m] = data2[j]
                j += 1
            m += 1
        print 'cnt: {}'.format(cnt)
        return cnt

    cnt = _mergeInversion(data, 0, len(data))
    print '>>>\n{}'.format(data)
    print '>>>inversion cnt: {}'.format(cnt)
    return data

if __name__ == '__main__':
    data = [2, 3, 0, -1, 8, 6, 1, -2] #[random.randint(1, 100) for i in xrange(1, 20)]
    data1 = mergeInversion(copy.deepcopy(data))
    assert sorted(data) == data1
