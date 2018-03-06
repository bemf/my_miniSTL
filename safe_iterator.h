//
//  safe_iterator.h
//  my_tinySTL
//
//  Created by wb on 2018/3/4.
//  Copyright © 2018年 wb. All rights reserved.
//

#ifndef safe_iterator_h
#define safe_iterator_h

namespace mySTL{
    template<class T>
    struct ListNode{
        ListNode *next;
        T**  it;
        ListNode(T** p):it(p),next(NULL){};
    };
    template<class T>
    class safe_iterator_list{
    public:
        typedef T* iterator;
        ListNode<T> *first=NULL;
        ListNode<T> *last=NULL;
        safe_iterator_list():first(NULL), last(NULL)
        {
            
        }
        
        void initialize(iterator *it)
        {
            first=new ListNode<T>(it);
            last=new ListNode<T>(it);
        }
        void add_iterator(iterator it)
        {
            if(first==NULL)
            {
                first=it;
                last=it;
            }
            else{
                //指向下一个
                last->next=it;
                last=last->next;
            }
        }
    };
}
#endif /* safe_iterator_h */
