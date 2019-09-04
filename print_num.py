import random

def str_integer(x):
    def _str_integer(x, s):
        if x // 10:
            _str_integer(x//10, s)
        s.append(str(x%10))

    s = []
    if x < 0:
        s.append('-')
        x = -x
    _str_integer(x, s)
    return ''.join(s)

def str_float(x):
    def _str_float(x, s):
        if x // 10:
            _str_float(x/10, s)
        s.append(str(x%10))
    
    s = []
    if x < 0:
        s.append('-')
        x = -x
    _str_float(x, s)
    return ''.join(s)

if __name__ == '__main__':
    x = random.randint(-100, 100)
    print '>>str {}'.format(x)
    print str_integer(x)
    x = random.randint(-100, 100) / 4.
    print '>>str {}'.format(x)
    print str_float(x)