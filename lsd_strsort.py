import copy

def lsd_strsort(str_list):
    N = len(str_list)
    assert N > 0

    print '>>lsd sort:\n{}'.format(str_list)
    M = len(str_list[0])

    for m in xrange(M-1, -1, -1):
        count = [0] * 256
        for i in xrange(N):
            c = ord(str_list[i][m])
            count[c] += 1
        for ic in xrange(255):
            count[ic+1] += count[ic]

        aux_str_list = [None] * N
        # loop from end to begining, consistent with count
        # place ordered str from end to begining
        for i in xrange(N-1, -1, -1):
            c = ord(str_list[i][m])
            count[c] -= 1
            pos = count[c]
            aux_str_list[pos] = str_list[i]
        str_list = aux_str_list

        print '>>{}:'.format(m),
        for i in xrange(N):
            print str_list[i],
        print
    return str_list

if __name__ == '__main__':
    data = [
        '4PGC938',
        '2IYE230',
        '3CIO720',
        '1ICK750',
        '1OHV845',
        '4JZY524',
        '1ICK750',
        '3CIO720',
        '1OHV845',
        '1OHV845',
        '2RLA629',
        '2RLA629',
        '3ATW723',
    ]

    data1 = lsd_strsort(copy.deepcopy(data))

