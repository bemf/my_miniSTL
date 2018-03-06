//
//  list.hpp
//  my_tinySTL
//
//  Created by wb on 2018/2/22.
//  Copyright © 2018年 wb. All rights reserved.
//

#ifndef list_hpp
#define list_hpp
#include "listIterator.h"
#include "algorithm.h"
#include "construct.h"
#include "allocator.h"
#include <iostream>

namespace mySTL {
    template <class T, class Alloc = alloc>
    class list {
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        
        typedef _list_node<T> list_node;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        
        typedef list_node* link_type;
        typedef simple_alloc<list_node, Alloc> list_node_allocator;
        
        typedef _list_iterator<T, T&, T*>   iterator;
        link_type get_node() {
            return list_node_allocator::allocate();
        }
        
        void put_node(link_type x) {
            list_node_allocator::deallocate(x);
        }
        
        link_type create_node(const T& x) {
            link_type newListNode = get_node();
            construct(&newListNode->data, x); //所指的数据，创建
            return newListNode;
        }
        
        void destroy_node(link_type d) {
            destroy(&d->data);
            put_node(d);
        }
        
    public:
        iterator begin() const {return node->next;}
        iterator end() const {return node;}
        bool empty() const {return node->next == node;}
        size_type size() const {
            size_type result = 0;
            result = distance(begin(), end());
            return result;
        }
        
        reference front() {return *begin();}
        reference back() {return *(--end());}
        
        //构造函数
        list() { empty_initialize();}
        ~list() {
            clear();
            erase(end());
        }
        void push_back(const T& x) {
            insert(end(), x);
        }
        
        void push_front(const T& x) {
            insert(begin(), x);
        }
        
        void pop_front() {
            erase(begin());
        }
        
        void pop_back() {
            erase(--end());
        }
        
        void clear() {
            iterator s = begin();
            while(s != end()) {
                s = erase(s);
            }
            node->next=node;
            node->prev=node;
        }
        
        void remove(const T& x) {
            iterator s = begin();
            while(s != end()) {
                if(*s == x)
                    s = erase(s);
                else
                    s++;
            }
        }
        
        void unique() {
            iterator first = begin();
            iterator last  = end();
            if(first == last) return;
            iterator next = first;
            while(++next != last) {
                if (*first == *next)
                    erase(next);
                else
                    first = next;
                next = first;
            }
        }
        
        iterator erase(iterator position) {
            link_type next_node = position.node->next;
            link_type prev_node = position.node->prev;
            prev_node->next = next_node;
            destroy_node(position.node);
            return iterator(next_node);
        }
        
        iterator insert(iterator position, const T& x) {
            link_type tmp = create_node(x);
            tmp->next = position.node;
            tmp->prev = position.node->prev;
            position.node->prev->next = tmp;
            position.node->prev = tmp;
            return tmp;
        }
        
        void transfer(iterator position, iterator first, iterator last) {
            if (last == position)
                return;
            
            link_type last_node = last.node->prev;
            first.node->prev->next = last.node;
            last.node->prev = first.node->prev;
            
            
            link_type prev_node = position.node->prev;
            prev_node->next = first.node;
            first.node->prev = prev_node;
            
            last_node->next = position.node;
            position.node->prev = last_node;
        }
        
        void splice(iterator position, list& x) {
            if(x.empty())
                return;
            transfer(position, x.begin(), x.end());
        }
        
        void splice(iterator position, iterator i) {
            iterator j = i;
            j++;
            transfer(position, i, j);
        }
        

        void splice(iterator position, iterator first, iterator last) {
            if(position == last)
                return;
            transfer(position, first, last);
        }
        
        void merge(list& x) {
            iterator p = begin();
            iterator x_start = x.begin();
            
            while(p != end() && x_start != x.end()) {
                std::cout<<*p<<std::endl;
                if(*x_start > *p)
                    p++;
                else {
                    iterator next = x_start + 1;
                    splice(p, x_start);
                    x_start = next;
                }
            }
            

            if(!x.empty())
                splice(end(), x_start, x.end());
        }
        
        //reverse
        void reverse() {
            iterator start = begin();
            iterator stop  = end();
            if(size() == 0 || size() == 1)
                return;
            start++;
            while(start != stop) {
                iterator next = start + 1;
                splice(begin(), start);
                start = next;
            }
        }
        
        void swap(list& x) {
            link_type tmp = x.node;
            x.node = this->node;
            this->node = tmp;
        }
        
        
    protected:
        link_type node;
        
        void empty_initialize() {
            node = get_node();
            node->next = node;
            node->prev = node;
        }
    };
}

#endif /* list_hpp */
