//
//  vector.hpp
//  my_tinySTL
//
//  Created by wb on 2018/1/12.
//  Copyright © 2018年 wb. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp
#include <initializer_list>
#include "iterator.h"
#include "type_traits.h"
#include "uninitialized.h"
#include "allocator.h"
#include "safe_iterator.h"
#include <iostream>
namespace mySTL{
    template<class T, class Alloc=alloc>
    class vector{
    public:
        //定义变量
        typedef T value_type;
        typedef T* pointer;
        typedef T* iterator;
        typedef const T* const const_iterator;
        typedef T&  reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef safe_iterator_list<value_type> safe_it_list;
        
    protected:
        //空间配置器
        typedef simple_alloc<value_type, Alloc> data_allocator;
        
        iterator start_place; //已用空间头
        iterator end_place; //已用空间尾
        iterator end_of_storage; //可用空间尾
        
        void insert_aux(iterator position, const T& x);
        void insert(iterator position, size_type n, const T& x);
        //safe_it_list init_safe_iterator_list(iterator it);
        //void add_iterator_safe(iterator it, safe_it_list &list);
        void insert_safe_aux(iterator position, const T& x,iterator *safe_it);
        void insert_safe_aux(iterator position, const T& x,safe_it_list &safe_it);
        
        void deallocate(){
            if(start_place)//已经使用
            {
                data_allocator::deallocate(start_place, end_of_storage-start_place);
            }
        }
        
        void fill_initialize(size_type n, const T & value)
        {
            start_place=allocate_and_fill(n,value);
            end_place=start_place+n;
            end_of_storage=end_place;
        }
        
    public:
        
        
        iterator begin() const{
            //返回vector 头
            return start_place;
        }
        iterator end() const{
            //返回vector 尾
            return end_place;
        }
        //vector 使用所占的容量
        size_type size() const {
            return size_type(end_place-start_place);
        }
        //vector 使用和剩余的容量
        size_type capacity() const{
            return size_type(end_of_storage-start_place);
        }
        bool empty() const{
            return (start_place==end_place)?1:0;
        }
        //获取vector下标为n的元素
        reference operator[](size_type n) const{
            return *(start_place+n);
        }
        //判断两个vector是否相等
        bool operator==(const vector &other) const{
            iterator first=begin(),last=end();
            iterator first_other=other.begin(), last_other=other.end();
            if(size()!=other.size())
            {
                return false;
            }
            while(first!=last&&first_other!=last_other)
            {
                if(*first!=first_other)
                {
                    return false;
                }
                ++first;
                ++first_other;
            }
            return (first==first_other);
        }
        
        //vector 构造函数
        vector():start_place(0), end_place(0),end_of_storage(0)
        {
            
        }
        
        vector(size_type n, const T &value) {
            fill_initialize(n, value);
        }
        
        vector(const std::initializer_list<T> value)
        {
            auto start_value=value.begin();
            auto end_value=value.end();
            
            size_type n=value.size();
            fill_initialize(n, T());
            end_place=mySTL::copy(start_value, end_value, start_place);
        }
        
        explicit vector(size_type n){
            fill_initialize(n, T());
        }
        
        ~vector(){
            destroy(start_place, end_place);
            deallocate();
        }
        
        reference front()
        {
            return *(start_place);
        }
        
        reference back(){
            return *(end_place);
        }
        
        void push_back(const T& x)
        {
            if(end_place != end_of_storage)
            {
                construct(end_of_storage, x);
                end_place++;
            }
            else{
                insert_aux(end_of_storage, x);
            }
        }
        
        void push_back_safe(const T& x, iterator *it)
        {
            if(end_place != end_of_storage)
            {
                construct(end_of_storage, x);
                end_place++;
            }
            else{
                insert_safe_aux(end_of_storage, x, it);
            }
        }
        
        void push_back_safe(const T& x, safe_it_list &sl)
        {
            if(end_place != end_of_storage)
            {
                construct(end_of_storage, x);
                end_place++;
            }
            else{
                insert_safe_aux(end_of_storage, x, sl);
            }
        }
        
        void pop_back(){
            --end_place;
            destroy(end_place);
        }
        
        iterator erase(iterator position)
        {
            if(position+1!=end_place)
                mySTL::copy(position+1, end_place, position);
            end_place--;
            destroy(end_place);
            return position;
        }
        
        iterator erase(iterator pos1, iterator pos2)
        {
            size_type erase_size=pos2-pos1;
            
            if(pos2!=end())
            {
                size_type left=pos2-pos1;
                copy(pos2, end_place,pos1);
                destroy(pos1+left,end_place);
            }
            else{
                destroy(pos1, end_place);
            }
            
            end_place=end_place-erase_size;
            return pos1;
        }
        
        void resize(size_type new_size, const T &x)
        {
            if(new_size<size())
            {
                destroy(start_place+new_size, end_place);
            }
            else{
                insert(end_place, new_size-size(), x);
            }
            
        }
        
        void resize(size_type new_size)
        {
            resize(new_size, T());
        }
        
        
        void clear(){
            erase(begin(),end());
        }
        
    protected:
        iterator allocate_and_fill(size_type n, const T &x)
        {
            iterator result=data_allocator::allocate(n);
            unitilized_fill_n(result, n, x);
            return result;
        }
    };
    
    template<class T, class Alloc>
    void vector<T, Alloc>::insert(iterator position, size_type n, const T & x)
    {
        T x_copy=x;
        if(n!=0)
        {
            //备用空间足够
            if(end_of_storage-end_place>=n)
            {
                unitilized_fill_n(end_place, n, x_copy);
                mySTL::copy(position, end_place, position+n);
                mySTL::fill(position, n, x_copy);
                
                end_place+=n;
            }
            
            else{
                const size_type old_size=size();
                //扩充方式为2倍空间，不够则延长到够
                const size_type new_size=old_size+std::max(old_size,n);
                iterator new_start=data_allocator::allocate(new_size);
                if(!new_start)
                {
                    printf("out of memory!\n");
                }
                
                iterator new_finish=new_start;
                
                try{
                    new_finish=unitialized_copy(start_place, end_place, new_start);
                    size_type m=position-start_place;
                    auto new_postion=new_start+m;
                    unitilized_fill_n(new_finish, n, x_copy);
                    mySTL::copy(new_postion, new_finish, new_finish+n);
                    mySTL::fill(new_postion,new_postion+n, x_copy);
                    
                }
                catch(...)
                {
                    destroy(new_start,new_finish);
                    data_allocator::deallocate(new_start,new_size);
                    throw;
                }
                clear();
                deallocate();
                start_place=new_start;
                end_place=new_finish;
                end_of_storage=new_start+new_size;
            }
        }
    }
    
    template<class T, class Alloc>
    void vector<T, Alloc>::insert_aux(iterator position, const T& x) {
        if (end_place != end_of_storage) {
            construct(end_place, *(end_place - 1));
            ++end_place;
            T x_copy = x;
            copy_backward(position, end_place - 2, end_place - 1);
            *position = x_copy;
        }
        else {
            const size_type old_size = size();
            const size_type new_size = old_size != 0 ? 2 * old_size : 1;
            
            iterator new_start = data_allocator::allocate(new_size);
            iterator new_finish = new_start;
            try {
                new_finish=unitialized_copy(start_place, position, new_start);
                construct(new_finish ,x);  //未构造的内存，需要调用construct
                new_finish++;
                //new_finish = uninitialized_copy(position, finish_, new_finish);
                new_finish=unitialized_copy(position, end_place, new_finish);
            } catch (...) {

                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, new_size);
                throw;
            }
            
            destroy(begin(), end());
            deallocate();
            
            start_place = new_start;
            end_place = new_finish;
            end_of_storage = new_start + new_size;
        }
    }
    template<class T, class Alloc>
    void vector<T, Alloc>::insert_safe_aux(iterator position, const T& x,iterator* safe_it) {
        if (end_place != end_of_storage) {//还有备用空间
            construct(end_place, *(end_place - 1));
            ++end_place;
            T x_copy = x;
            copy_backward(position, end_place - 2, end_place - 1);
            *position = x_copy;
        }
        else {
            const size_type old_size = size();
            const size_type new_size = old_size != 0 ? 2 * old_size : 1;
            
            iterator new_start = data_allocator::allocate(new_size);
            iterator new_finish = new_start;
            try {
                new_finish=unitialized_copy(start_place, position, new_start);
                construct(new_finish ,x);  //未构造的内存，需要调用construct
                new_finish++;
                //new_finish = uninitialized_copy(position, finish_, new_finish);
                new_finish=unitialized_copy(position, end_place, new_finish);
            } catch (...) {
                
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, new_size);
                throw;
            }
            
            destroy(begin(), end());
            deallocate();
            start_place = new_start;
            end_place = new_finish;
            *safe_it = new_start;
            end_of_storage = new_start + new_size;
        }
    }
    
    template<class T, class Alloc>
    void vector<T, Alloc>::insert_safe_aux(iterator position, const T& x,safe_it_list &safe_it) {
        if (end_place != end_of_storage) {//还有备用空间
            construct(end_place, *(end_place - 1));
            ++end_place;
            T x_copy = x;
            copy_backward(position, end_place - 2, end_place - 1);
            *position = x_copy;
        }
        else {
            const size_type old_size = size();
            const size_type new_size = old_size != 0 ? 2 * old_size : 1;
            
            iterator new_start = data_allocator::allocate(new_size);
            iterator new_finish = new_start;
            try {
                new_finish=unitialized_copy(start_place, position, new_start);
                construct(new_finish ,x);  //未构造的内存，需要调用construct
                new_finish++;
                new_finish=unitialized_copy(position, end_place, new_finish);
            } catch (...) {
                
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, new_size);
                throw;
            }
            if(safe_it.first!=NULL)
            {
                ListNode<T> *node=safe_it.first;
                *(node->it)=new_start;
                node=node->next;
            }
            destroy(begin(), end());
            deallocate();
            start_place = new_start;
            end_place = new_finish;
            end_of_storage = new_start + new_size;
        }
    }
    
    
}









#endif /* vector_hpp */
