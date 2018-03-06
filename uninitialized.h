//
//  uninitialized.h
//  my_tinySTL
//
//  Created by wb on 2018/1/18.
//  Copyright © 2018年 wb. All rights reserved.
//

#ifndef uninitialized_h
#define uninitialized_h
#include "construct.h"
#include "algorithm.h"
namespace mySTL {
    //对于trait类型的数据
    template<class Input_iterator, class Forward_iterator>
    Forward_iterator _unitialized_copy_aux(Input_iterator first, Input_iterator last,
                                       Forward_iterator res, _true_type)
    {
        memcpy(res ,first,(last-first)*sizeof(*first));
        return res +(last-first);
    }
    
    //对于non-trait类型的数据
    template<class Input_iterator, class Forward_iterator>
    Forward_iterator _unitialized_copy_aux(Input_iterator first, Input_iterator last,
                                           Forward_iterator res, _false_type)
    {
        int i=0;
        for(;first!=last; first++,i++)
        {
            construct((res+i),*first);
        }
        return (res+i);
    }
    
    template<class Input_iterator, class Forward_iterator,class T>
    Forward_iterator _unitialized_copy(Input_iterator first, Input_iterator last,
                                      Forward_iterator res, T)
    {
        typedef typename _type_traits<T>::is_POD_type isPOD;
        return _unitialized_copy_aux(first, last, res, isPOD());
    }
    
    template<class InputIterator, class ForwardIterator>
    ForwardIterator unitialized_copy(InputIterator first, InputIterator last,
                                     ForwardIterator result) {
        return _unitialized_copy(first, last, result, value_type(result));
        
    }
    
    template<class ForwardIterator, class Size, class T>
    ForwardIterator _unitialized_fill_n_aux(ForwardIterator first, Size n,
                                            const T& x, _true_type) {
        return fill_n(first, n, x);
    }
    
    template<class ForwardIterator, class Size, class T>
    ForwardIterator _unitialized_fill_n_aux(ForwardIterator first, Size n,
                                            const T& x, _false_type) {
        int i = 0;
        for(; i != n; ++i) {
            construct((T*)(first + i), x);
        }
        return (first + i);
    }
    
    template<class ForwardIterator, class Size, class T>
    inline ForwardIterator unitilized_fill_n(ForwardIterator first, Size n, const T &x)
    {
        typedef typename _type_traits<T>::is_POD_type isPOD;
        return _unitialized_fill_n_aux(first, n, x, isPOD());
    }
    
}

#endif /* uninitialized_h */
