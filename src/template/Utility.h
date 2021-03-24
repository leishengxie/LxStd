#pragma once

#ifdef WIN32
    #include <iostream>
#else
    #include <stdio.h>
#endif


template <class T>
static inline void swap(T & x, T & y)
{
    T t = x;
    x = y;
    y = t;
}

#ifndef min
template <class T>
static inline T min(T x, T y)
{
    return (x < y) ? x : y;
}
#endif

#ifndef max
template <class T>
static inline T max(T x, T y)
{
    return (x > y) ? x : y;
}
#endif

//template <class S, class T>
//static inline void clone(T* & dst, S* src, int n)
//{
//    dst = new T[n];
//    memcpy((void*)dst, (void*)src, sizeof(T)*n);
//}

