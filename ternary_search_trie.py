import random

"""implementation of ternary search trie data structure
to address issue of excessive space in regular trie structure
"""

R = 3

class TSTNode(object):
    def __init__(self, c):
        self.val = None
        self.key = c
        """links contains
        1) link to substrings whose first char is smaller than current 'key'
        2) link to substrings that continue with current 'key'
        3) link to substrings whose first char is greater than current 'key'
        """
        self.left = None
        self.mid = None
        self.right = None

class TSTrie(object):
    def __init__(self):
        """the root will hold some real key character, different from regular trie implementation"""
        self.root = None

    def put(self, key, val):
        """key is specifically a string, val is assigned specific value for that string key"""
        def _put(node, key, val, d):
            c = key[d] # we guarantee d will not be out of range
            if node == None:
                node = TSTNode(c)

            if c < node.key: # put it in left link
                node.left = _put(node.left, key, val, d)
            elif c > node.key:
                node.right = _put(node.right, key, val, d)
            elif d < len(key) - 1:
                node.mid = _put(node.mid, key, val, d+1)
            else:
                node.val = val # update the value
            return node

        print '>>put key={}, val={}'.format(key, val)
        self.root = _put(self.root, key, val, 0)
        print '>>tstrie: {}'.format(self)

    def _get(self, node, key, d):
        if node == None: return None
        c = key[d]
        if c < node.key:
            return self._get(node.left, key, d)
        elif c > node.key:
            return self._get(node.right, key, d)
        elif d < len(key) - 1:
            return self._get(node.mid, key, d+1)
        else:
            return node

    def get(self, key):
        print '>>get key={} => '.format(key),
        node = self._get(self.root, key, 0)
        val = node.val if node else None
        print val
        return val

    def size(self):
        """lazy implementation of size"""
        def _size(node):
            if node == None: return 0
            size = 1 if node.val != None else 0
            size += _size(node.left)
            size += _size(node.mid)
            size += _size(node.right)
            return size
        return _size(self.root)

    def _collect(self, node, coll, keys):
        if node == None: return
        self._collect(node.left, coll, keys)

        coll.append(node.key)
        if node.val != None:
            keys.append(''.join(coll))
        self._collect(node.mid, coll, keys)
        coll.pop()

        self._collect(node.right, coll, keys)

    def keys(self):
        keys = []
        coll = []
        self._collect(self.root, coll, keys)
        return keys

    def keysWithPrefix(self, prefix):
        """return all keys which contain 'prefix' as prefix
        """
        print '>>keys with prefix "{}"'.format(prefix)
        n = self._get(self.root, prefix, 0)
        if n:
            keys = []
            coll = [c for c in prefix]
            coll.pop() # different from trie implementation
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
            if node == None: return length
            c = key[d]
            if c < node.key:
                return _search(node.left, key, d, length)
            elif c > node.key:
                return _search(node.right, key, d, length)
            else:
                if node.val != None: length = d + 1
                if d < len(key) - 1:
                    return _search(node.mid, key, d+1, length)
                else:
                    return length

        length = _search(self.root, s, 0, 0)
        prefix = s[0:length]
        return prefix

    def _maxNode(self, node):
        while node.right:
            node = node.right
        return node

    def delete(self, key):
        def _delete(node, key, d):
            if node == None: return None
            c = key[d]
            if c < node.key:
                node.left = _delete(node.left, key, d)
            elif c > node.key:
                node.right = _delete(node.right, key, d)
            elif d < len(key) - 1:
                node.mid = _delete(node.mid, key, d+1)
            else: # we find it
                if node.val != None:
                    if node.mid == None:
                        if node.left and node.right: # both children there
                            #use left node, and attach right node to this new node's right-most node
                            x = self._maxNode(node.left)
                            x.right = node.right
                            node = node.left
                        else: # only one child there
                            if node.left == None:
                                node = node.right
                            else:
                                node = node.left
                    else:
                        # mid is there, we won't do anything, but reset its val
                        node.val = None
                else:
                    print '>>>not find "{}" to delete'.format(key)
            return node
        print '>>delete key "{}"'.format(key)
        self.root = _delete(self.root, key, 0)

    def __str__(self):
        s = ''
        node = self.root
        if node == None or not any([node.left, node.mid, node.right]): return '<EMPTY>'
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
    tstrie = TSTrie()
    for i in xrange(len(data)):
        tstrie.put(data[i], i)
    print '>>tstrie: size={}, {}'.format(tstrie.size(), tstrie)

    print '>>test get'
    for i in xrange(len(data)):
        tstrie.get(data[i])

    print '>>test keysWithPrefix'
    for i in xrange(len(data)):
        print tstrie.keysWithPrefix(data[i])

    print '>>test longestPrefixOf'
    for i in xrange(len(data)):
        print tstrie.longestPrefixOf(data[i])

    for i in xrange(len(data)):
        s = data[i] + ''.join([str(random.randint(0, 9)) for _ in xrange(5)])
        print tstrie.longestPrefixOf(s)
        s = ''.join([str(random.randint(0, 9)) for _ in xrange(5)]) + data[i]
        print tstrie.longestPrefixOf(s)
        s = list(data[i])
        s.insert(random.randint(0, len(data[i])), str(random.randint(0, 9)))
        s = ''.join(s)
        print tstrie.longestPrefixOf(s)

    print '>>before delete, tstrie: {}'.format(tstrie)
    for i in xrange(len(data)):
        tstrie.delete(data[i])
        print '>>trie: {}'.format(tstrie)
