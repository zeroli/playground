def buildPrefixTable(p):
    next = [-1] * len(p)
    if len(p) <= 1: return next
    j = 0
    i = 1
    next[i] = 0
    while (i < len(p)-1):
        print j, i
        if j < 0 or p[i] == p[j]:
            i += 1
            j += 1
            next[i] = j
        else:
            j = next[j]
    return next

def naiveSearch(t, p):
    print 'naive sarch algo'
    i = 0
    j = 0
    while i < len(t) and j < len(p):
        if t[i] == p[j]:
            i += 1
            j += 1
        else:
            i -= j - 1
            j = 0
    if j == len(p):
        return i - j
    return -1

def kmpSearch(t, p):
    print 'kmp serach algo'
    next = buildPrefixTable(p)
    print 'next : {}'.format(next)

    i = 0
    j = 0
    while i < len(t) and j < len(p):
        if t[i] == p[j] or j < 0:
            i += 1
            j += 1
        else:
            j = next[j]

    if j == len(p):
        return i - j
    return -1

if __name__ == '__main__':
    s = "acabaabaabcacaabc"
    p = "abaabc"
    print "s: '{}'".format(s)
    print "p: '{}'".format(p)
    print naiveSearch(s, p)
    print kmpSearch(s, p)
