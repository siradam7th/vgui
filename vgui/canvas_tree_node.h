#pragma once
#include "common.h"
#include "element.h"
#include <functional>
#include <vector>

namespace vgui
{
    class CanvasTreeNode
    {
    public:
        CanvasTreeNode() = default;
        CanvasTreeNode(Element* element) : m_pElement(element) {}

        bool insert(SPtr<CanvasTreeNode> node)
        {
            if (node == nullptr)
            {
                return false;
            }

            m_children.push_back(node);
            return true;
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
            for (auto child : node->m_children)
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

        void setElement(Element* pElement)
        {
            m_pElement = pElement;
        }

        Element* const getElement()
        {
            return m_pElement;
        }

    private:
        Element* m_pElement = nullptr;
        std::vector<SPtr<CanvasTreeNode>> m_children;
    };
}