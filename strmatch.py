import os, sys, random

def strmatch_bm(text, pat):
    def _build_last(pat):
        last = [-1] * 256
        for i in xrange(len(pat)):
            last[ord(pat[i])] = i
        return last
    print 'find "{}" in "{}"'.format(pat, text)
    last = _build_last(pat)
    
    n = len(text)
    m = len(pat)
    i,j = m-1, m-1
    while i < n:
        if text[i] == pat[j]:
            if j == 0:
                print 'match found at {} to {}'.format(i, i+m-1)
                return
            i -= 1
            j -= 1
        else:
            i += m - min(j, 1+last[ord(text[i])])
            j = m-1
    
    print 'not match found'
    
def main():
    text = 'Please help to take a look.'
    pat = 'lookaa'
    strmatch_bm(text, pat)
    
main()
