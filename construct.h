//
//  construct.h
//  my_tinySTL
//
//  Created by wb on 2018/1/12.
//  Copyright © 2018年 wb. All rights reserved.
//

#ifndef construct_h
#define construct_h

#include <new>

#include "type_traits.h"

namespace mySTL {
    template<class T1, class T2>
    inline void construct(T1 *ptr1, const T2 &value)
    {
        new (ptr1) T1(value);//在ptr1上创建T1对象
    }
    
    template<class T>
    inline void destroy(T *ptr)
    {
        ptr->~T();//析构指针所指的对象
    }
    
    //如果类型是trait类型，无需destroy
    template<class FIterator>
    inline void _destroy(FIterator first, FIterator last, _true_type){}
    
    template<class FIterator>
    inline void _destroy(FIterator first, FIterator last, _false_type){
        for(; first!=last; first++)
        {
            destroy(&*first);
        }
    }
    
    template<class FIterator>
    inline void destroy(FIterator first, FIterator last)
    {
        typedef typename _type_traits<FIterator>::is_POD_type is_POD;
        _destroy(first, last, is_POD());
    }
    
}

#endif /* construct_h */
