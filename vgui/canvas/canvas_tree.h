#pragma once
#include "canvas_tree_node.h"
#include "vgui/common.h"

namespace vgui
{
    class CanvasTree
    {
    public:
        CanvasTree()
        {
            m_root = std::make_shared<CanvasTreeNode>(nullptr);
        }
        CanvasTreeNode* getRoot()
        {
            return m_root.get();
        }

    private:
        SPtr<CanvasTreeNode> m_root = nullptr;
    };
}