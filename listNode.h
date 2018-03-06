//
//  listNode.h
//  my_tinySTL
//
//  Created by wb on 2018/2/22.
//  Copyright © 2018年 wb. All rights reserved.
//

#ifndef listNode_h
#define listNode_h
template <class T>
struct _list_node {
    //list是双向的
    typedef _list_node* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};
#endif /* listNode_h */
