import random
import copy

"""implementation of trie data structure
"""

R = 256

"""each node contains R links to childrens, which take excessive spaces
we will address this issue in ternary search trie structure
"""
class TrieNode(object):
    def __init__(self):
        self.next = [None] * R
        self.val = None #Not None means ending of one key string

class Trie(object):
    def __init__(self):
        self.root = TrieNode()

    def put(self, key, val):
        """key is specifically a string, val is assigned specific value for that string key"""
        def _put(node, key, val, d):
            if d == len(key):
                node.val = val # update the value
            else:
                ic = ord(key[d])
                if node.next[ic] == None:
                    # build the chain for the rest of key chars
                    for k in xrange(d, len(key)):
                        ik = ord(key[k])
                        node.next[ik] = nn = TrieNode()
                        node = nn
                        if k == len(key) - 1:
                            nn.val = val
                else:
                    _put(node.next[ic], key, val, d+1)
        print '>>put key={}, val={}'.format(key, val)
        _put(self.root, key, val, 0)
        print '>>trie: {}'.format(self)

    def _get(self, node, key, d):
        if d == len(key): return node
        ic = ord(key[d])
        if node.next[ic] == None:
            return None
        else:
            return self._get(node.next[ic], key, d+1)

    def get(self, key):
        """find the value which is associated with this given 'key', otherwise, return None"""
        print '>>get key={} => '.format(key),
        node = self._get(self.root, key, 0)
        val = node.val if node else None
        print val
        return val

    def _collect(self, node, coll, keys):
        if node.val != None:
            keys.append(''.join(coll))
        for ic, n in enumerate(node.next):
            if not n: continue
            coll.append(chr(ic))
            self._collect(n, coll, keys)
            coll.pop()

    def keys(self):
        keys = []
        coll = []
        self._collect(self.root, coll, keys)
        return keys

    def size(self):
        """lazy implementation of size"""
        def _size(node):
            if node == None: return 0
            size = 1 if node.val != None else 0
            for n in node.next:
                size += _size(n)
            return size
        return _size(self.root)

    def keysWithPrefix(self, prefix):
        """return all keys which contain 'prefix' as prefix
        """
        print '>>keys with prefix "{}"'.format(prefix)
        n = self._get(self.root, prefix, 0)
        if n:
            keys = []
            coll = [c for c in prefix]
            self._collect(n, coll, keys)
            return keys
        else:
            return []

    def longestPrefixOf(self, s):
        """return the key which is longest prefix of given string 's'
        """
        print '>>longest prefix of "{}"'.format(s)
        # length: record longest key which match prefix of this key until now
        def _search(node, key, d, length):
            if node.val != None: length = d
            if d == len(key): return length
            ic = ord(key[d])
            if node.next[ic] == None:
                return length
            else:
                return _search(node.next[ic], key, d+1, length)
        length = _search(self.root, s, 0, 0)
        prefix = s[0:length]
        return prefix

    def delete(self, key):
        print '>>delete key "{}"'.format(key)
        def _delete(node, key, d):
            if node == None: return None
            if d < len(key) or node.val == None:
                ic = ord(key[d])
                node.next[ic] = _delete(node.next[ic], key, d+1)

            if any(node.next):  # there is children continuing, do nothing, but just set val=None
                node.val = None
                return node
            else: # delete it and check its parent recursively
                return None
        self.root = _delete(self.root, key, 0)
        if self.root == None:
            self.root = TrieNode()

    def __str__(self):
        s = ''
        node = self.root
        if node == None or not any(node.next): return '<EMPTY>'
        s = ' '.join(self.keys())
        return s

if __name__ == '__main__':
    data = [
        'she',
        'sells',
        'sea',
        'shells',
        'by',
        'the',
        'sea',
        'shore',
    ]
    trie = Trie()
    for i in xrange(len(data)):
        trie.put(data[i], i)
    print '>>trie: size={}, {}'.format(trie.size(), trie)

    print '>>test get'
    for i in xrange(len(data)):
        trie.get(data[i])

    print '>>test keysWithPrefix'
    for i in xrange(len(data)):
        print trie.keysWithPrefix(data[i])

    print '>>test longestPrefixOf'
    for i in xrange(len(data)):
        print trie.longestPrefixOf(data[i])

    for i in xrange(len(data)):
        s = data[i] + ''.join([str(random.randint(0, 9)) for _ in xrange(5)])
        print trie.longestPrefixOf(s)
        s = ''.join([str(random.randint(0, 9)) for _ in xrange(5)]) + data[i]
        print trie.longestPrefixOf(s)
        s = list(data[i])
        s.insert(random.randint(0, len(data[i])), str(random.randint(0, 9)))
        s = ''.join(s)
        print trie.longestPrefixOf(s)

    print '>>before delete, trie: {}'.format(trie)
    for i in xrange(len(data)):
        trie.delete(data[i])
        print '>>trie: {}'.format(trie)
