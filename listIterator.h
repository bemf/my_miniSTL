//
//  listIterator.h
//  my_tinySTL
//
//  Created by wb on 2018/2/22.
//  Copyright © 2018年 wb. All rights reserved.
//

#ifndef listIterator_h
#define listIterator_h
#include "listNode.h"
#include "iterator.h"
namespace mySTL {

    template<class T, class Ref, class Ptr>
    struct _list_iterator {
        typedef _list_iterator<T, T&, T*>   iterator;
        typedef _list_iterator<T, Ref, Ptr> self;
        typedef bidirectional_iterator_tag iterator_category;
        typedef T   value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef _list_node<T>* link_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        
        link_type node;
        _list_iterator(link_type x) : node(x) {}
        _list_iterator() {}
        _list_iterator(const iterator& x) : node(x.node) {}
        bool operator==(const self& x) const {return node == x.node;}
        bool operator!=(const self& x) const {return node != x.node;}
        
        //deference
        reference operator*() const {return (*node).data;}
        pointer   operator->() const {return &(operator*());} //???
        
        self& operator++() {
            node = node->next;
            return *this;
        }
        
        self operator++(int) {
            self tmp = *this;
            ++*this;
            return tmp;
        }
        
        //(--i)
        self& operator--() {
            node = node->prev;
            return *this;
        }
        
        //(i--)
        self operator--(int) {
            self tmp = *this;
            --*this;
            return tmp;
        }
        
        self operator+(int dis){
            self tmp = *this;
            while(dis-- > 0) {
                tmp = tmp.node->next;
            }
            return tmp;
        }
        
        self operator-(int dis){
            self tmp = *this;
            while(dis-- > 0) {
                tmp = tmp.node->prev;
            }
            return tmp;
        }
    };
}


#endif /* listIterator_h */
