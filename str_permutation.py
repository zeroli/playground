"""print all permutation of given string"""
def permutation(slist):
    def _permutation(slist, start):
        if start == len(slist):
            print slist
        else:
            for i in xrange(start, len(slist)):
                slist[start], slist[i] = slist[i], slist[start]
                _permutation(slist, start+1)
                slist[start], slist[i] = slist[i], slist[start]

    _permutation(slist, 0)

if __name__ == '__main__':
    permutation(list('abc'))
