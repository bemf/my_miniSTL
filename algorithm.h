//
//  algorithm.h
//  my_tinySTL
//
//  Created by wb on 2018/1/25.
//  Copyright © 2018年 wb. All rights reserved.
//

#ifndef algorithm_h
#define algorithm_h

#include <cstring>
#include <utility>

#include "iterator.h"
#include "type_traits.h"

namespace mySTL{
    //填充元素
    //fill first-last
    template<class Forward_iterator, class T>
    void fill(Forward_iterator first, Forward_iterator last, const T& value)
    {
        for(;first!=last;first++)
        {
            *first=value;
        }
    }
    
    inline void fill(char *first, char *last, const char& value)
    {
        memset(first, static_cast<char> (value), last-first);
    }
    
    //fill first size-n
    template<class Forward_iterator, class Size, class T>
    Forward_iterator fill_n(Forward_iterator first, Size n, const T&value)
    {
        for(;n>0;n--,first++)
        {
            *first=value;
        }
        return first;
    }
    
    template<class Size>
    char * fill_n(char *first, Size n, char &value)
    {
        memset(first, static_cast<char> (value), n);
        return first+n;
    }
    
    //计算距离
    
    template<class Input_iterator>
    typename iterator_traits<Input_iterator>::difference_type
    _distance(Input_iterator first, Input_iterator last, input_iterator_tag)
    {
        typename iterator_traits<Input_iterator>::difference_type dist=0;
        while(first++!=last)
        {
            ++dist;
        }
        return dist;
    }
    
    template<class Random_iterator>
    typename iterator_traits<Random_iterator>::difference_type
    _distance(Random_iterator first, Random_iterator last, random_access_iterator_tag)
    {
        //typename iterator_traits<Random_iterator>::difference_type dist=0;
        
        auto dist=last-first;
        return dist;
    }
    
    template<class Iterator>
    typename iterator_traits<Iterator>::difference_type
    distance(Iterator first, Iterator last)
    {
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        return _distance(first, last, iterator_category());
    }
    
    /*************************************************
     PUSH
     *************************************************/
    template <class RandomAccessIterator, class Distance, class T>
    inline void _push_heap(RandomAccessIterator first, RandomAccessIterator last,
                           Distance holeIndex, Distance topIndex, T value)
    {
        Distance parent=(holeIndex-1)/2;
        while(holeIndex>topIndex&&*(first+parent)<value)
        {
            //父节点的值下降
            *(first+holeIndex)=*(first+parent);
            holeIndex=parent;
            parent=(holeIndex-1)/2;
        }
        *(first+holeIndex)=value;
    }
    
    /*************************************************
     ADVANCE
     *************************************************/

    
    template<class InputIterator, class Distance>
    void _advance(InputIterator& it, Distance n, input_iterator_tag){
        assert(n >= 0);
        while (n--){
            ++it;
        }
    }
    template<class BidirectionIterator, class Distance>
    void _advance(BidirectionIterator& it, Distance n, bidirectional_iterator_tag){
        if (n < 0){
            while (n++){
                --it;
            }
        }else{
            while (n--){
                ++it;
            }
        }
    }
    template<class RandomIterator, class Distance>
    void _advance(RandomIterator& it, Distance n, random_access_iterator_tag){
        if (n < 0){
            it -= (-n);
        }else{
            it += n;
        }
    }
    
    template <class InputIterator, class Distance>
    void advance(InputIterator& it, Distance n){
        typedef typename iterator_traits<InputIterator>::iterator_category iterator_category;
        _advance(it, n, iterator_category());
    }
    
    /*************************************************
     COPY
     *************************************************/
    inline char *copy (char *first, char *last, char *result)
    {
        auto dist=last-first;
        memcpy(result, first, sizeof(*first)*dist);
        return result+dist;
    }
    
    template<class InputIterator, class OutputIterator>
    OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _false_type){
        
        while (first != last){
            *result = *first;
            ++result;
            ++first;
        }
        
        return result;
        
    }
    
    template<class InputIterator, class OutputIterator>
    OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _true_type){
        
        auto dist = distance(first, last);
        memcpy(result, first, sizeof(*first) * dist);
        advance(result, dist);
        return result;
        
    }
    
    template<class InputIterator, class OutputIterator, class T>
    OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result, T*){
        
        typedef typename _type_traits<T>::is_POD_type is_pod;
        return __copy(first, last, result, is_pod());
        
    }
    
    
    template <class InputIterator, class OutputIterator>
    OutputIterator copy_backward(InputIterator first, InputIterator last, OutputIterator result){
        
        OutputIterator new_result = result - (last - first);
        return _copy(first, last, new_result, value_type(first));
        
    }
    
    
    
}



#endif /* algorithm_h */
