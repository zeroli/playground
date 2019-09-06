import random

"""implementation for hash table using open addressing strategy with linear probing
"""
class HashTable(object):
    def __init__(self, M):
        self.M = M # table size
        self.K = [None] * M # keys table
        self.V = [None] * M  # values table
        self.n = 0 # number of keys stored in table

    def __str__(self):
        s = []
        for ik in xrange(len(self.K)):
            if self.K[ik]:
                s.append(str((self.K[ik], self.V[ik])))
        ret = 'total {}: '.format(self.n) + ','.join(s)
        return ret

    def put(self, key, value):
        h = self.hashCode(key)
        while self.K[h]:
            if self.K[h] == key: # update it
                self.V[h] = value
                return
            else:
                h = (h + 1) % self.M
        self.K[h] = key
        self.V[h] = value
        self.n += 1

    def get(self, key):
        """get the value which is paired with the 'key'
        return None if the value not found for that queried 'key'
        """
        h = self.hashCode(key)
        while self.K[h]:
            if self.K[h] == key: return self.V[h]
            h = (h + 1) % self.M
        return None

    def hashCode(self, key):
        """use simplest modular hashing to compuate the hash code"""
        return hash(key) % self.M

    def clear(self):
        self.K = [None] * self.M
        self.V = [None] * self.M
        self.n = 0

if __name__ == '__main__':
    lst = [random.randint(0, 100) for _ in xrange(20)]
    print '>>random list:\n{}'.format(lst)
    ht = HashTable(100)
    map(lambda x: ht.put(x, 2*x), lst)
    print '>>after insert to hashtable:\n{}'.format(ht)
    for (x,y) in map(lambda x: (x, ht.get(x)),
        [random.randint(0, 100) for _ in xrange(10)]):
        print '>>get {} for key {}'.format(y, x)
    ht.clear()

    import glob
    pyfiles = glob.glob('*.py')
    print '>>glob py files: {}'.format(pyfiles)
    map(lambda x: ht.put(x, len(x)), pyfiles)
    print '>>after insert to hashtable:\n{}'.format(ht)
