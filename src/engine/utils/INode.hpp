//
// Created by Earth_Studio on 2026/5/6.
//

#pragma once


namespace cmaterial::utils {
    class INode{
    public:
        virtual ~INode() = default;
        INode * parent = nullptr;
    };
}