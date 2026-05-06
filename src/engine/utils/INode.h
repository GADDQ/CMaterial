//
// Created by Earth_Studio on 2026/5/6.
//

#ifndef CMATERIAL_INODE_H
#define CMATERIAL_INODE_H


namespace camterial::utils {
    class INode{
    public:
        virtual ~INode() = default;
        INode * parent = nullptr;
    };
}



#endif //CMATERIAL_INODE_H
