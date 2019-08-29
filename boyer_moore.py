import os, sys, random

def strmatch_bm(text, pat):
    """build bad characters heuristic"""
    def _build_last(pat):
        last = [-1] * 256
        for i in xrange(len(pat)):
            last[ord(pat[i])] = i
        return last
    print 'find "{}" in "{}"'.format(pat, text)
    last = _build_last(pat)
    
    n = len(text)
    m = len(pat)
    # do match from end to begin
    i,j = m-1, m-1
    while i < n:
        if text[i] == pat[j]:
            if j == 0:
                print 'match found at {} to {}'.format(i, i+m-1)
                return
            i -= 1
            j -= 1
        else:
            # shift i so that it could match with last same char before 'j'
            # while we could not guarantee next whole matching could succeed
            # still need match from end to begin
            k = last[ord(text[i])]
            if k < j: i += m - 1 - k
            else: i += m - 1
            j = m - 1
            print 'i={},j={}'.format(i,j)
    
    print 'not match found'
    
def main():
    text = 'xxdbc1234'
    pat = 'ababc'
    strmatch_bm(text, pat)
    
main()
