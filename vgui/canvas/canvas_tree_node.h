#pragma once
#include "vgui/common.h"
#include "vgui/elements/element.h"

#include <functional>
#include <vector>

namespace vgui
{
    class CanvasTreeNode : public std::enable_shared_from_this<CanvasTreeNode>
    {
    public:
        CanvasTreeNode() = default;
        CanvasTreeNode(Element* element) : m_pElement(element) {}

        // insert a node as a child of this node
        bool insert(SPtr<CanvasTreeNode> node)
        {
            // check if it is nullptr, or if we are inserting a node into itself
            // because that causes endless recursion (we don't want that, causes stack overflow)
            if (node == nullptr || this == node.get())
            {
                return false;
            }

            // since we are adding this node as our child, we are the parent
            node->m_parent = shared_from_this();
            m_children.push_back(node);
            return true;
        }

        // return the parent of this node
        // NOTE: the parent node can be empty or nullptr
        SPtr<CanvasTreeNode> getParent()
        {
            return m_parent.lock();
        }

        // remove all child nodes and deallocate their memory
        void remove_all()
        {
            // removes all vector items (doesn't release memory)
            m_children.clear();
            // shrink vector to release memory that was allocated
            m_children.shrink_to_fit();
        }

        static void walkCanvasTreeNode(CanvasTreeNode* node,
            std::function<bool(CanvasTreeNode*)> func)
        {
            if (!node)
            {
                return;
            }
            if (func(node))
            {
                return;
            }
            for (auto& child : node->m_children)
            {
                walkCanvasTreeNode(child.get(), func);
            }
            return;
        }

        void traverse(std::function<bool(CanvasTreeNode* node)> func)
        {
            walkCanvasTreeNode(this, func);
            return;
        }

        Element* const getElement()
        {
            return m_pElement;
        }

    protected:
        // don't allow setting the Element ptr from the outside
        void setElement(Element* pElement)
        {
            m_pElement = pElement;
        }

    private:
        WPtr<CanvasTreeNode> m_parent = {};
        Element* m_pElement = nullptr;
        std::vector<SPtr<CanvasTreeNode>> m_children;
    };
}