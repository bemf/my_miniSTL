//
//  type_traits.h
//  my_tinySTL
//
//  Created by wb on 2018/1/12.
//  Copyright © 2018年 wb. All rights reserved.
//

#ifndef type_traits_h
#define type_traits_h

namespace mySTL {
    struct _true_type{};
    struct _false_type{};
    
    //用来萃取传入的类型是否是traits
    
    template<class T>
    struct _type_traits
    
    {
        
        typedef _false_type		has_trivial_default_constructor;
        
        typedef _false_type		has_trivial_copy_constructor;
        
        typedef _false_type		has_trivial_assignment_operator;
        
        typedef _false_type		has_trivial_destructor;
        
        typedef _false_type		is_POD_type;
        
    };
    
    template<> struct _type_traits<bool>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<char>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<unsigned char>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<signed char>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<wchar_t>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<short>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<unsigned short>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<int>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<unsigned int>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<long>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<unsigned long>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<long long>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<unsigned long long>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<float>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<double>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<long double>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    
    //指针是POD类型
    template<class T>
    
    struct _type_traits<T*>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<class T>
    struct _type_traits<const T*>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<char*>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    template<>struct _type_traits<unsigned char*>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    
    template<>struct _type_traits<signed char*>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    
    template<>struct _type_traits<const char*>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    
    template<>struct _type_traits<const unsigned char*>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
    
    
    template<>struct _type_traits<const signed char*>
    
    {
        
        typedef _true_type		has_trivial_default_constructor;
        
        typedef _true_type		has_trivial_copy_constructor;
        
        typedef _true_type		has_trivial_assignment_operator;
        
        typedef _true_type		has_trivial_destructor;
        
        typedef _true_type		is_POD_type;
        
    };
}






#endif /* type_traits_h */
