#!/usr/bin/python
#coding=utf-8

def quick_sort(arr, left, right):
    if (left >= right):
        return
    
    beg = left
    end = right
    key = arr[left]

    while (beg < end):
        while (beg < end and arr[end] >= key):
            end -= 1
        arr[beg] = arr[end]

        while (beg < end and arr[beg] < key):
            beg += 1
        arr[end] = arr[beg]

    arr[beg] = key

    quick_sort(arr, left, beg-1)
    quick_sort(arr, beg+1, right)

if (__name__ == "__main__"):
    l = [4, 2, 1, 8, 6, 5]
    print "before sort: ", l
    quick_sort(l, 0, len(l)-1)
    print "after sort: ", l
