#pragma once
#include "common.h"
#include <memory>
#include <vector>
#include <cassert>

namespace vgui
{
    template<class T>
    class CanvasTreeNode : public std::enable_shared_from_this<CanvasTreeNode<T>>
    {
    public:
        CanvasTreeNode(T _data) : data(_data) {};

        T data;
        uint64_t id;
        std::weak_ptr<CanvasTreeNode<T>> parent;
        std::vector<std::shared_ptr<CanvasTreeNode<T>>> children;
    private:
        template<class T>
        friend class CanvasTree;

		// traverse node's children trying to match the id
        std::shared_ptr<CanvasTreeNode<T>> traverse(uint64_t id);
    };

	template<class T>
	std::shared_ptr<CanvasTreeNode<T>> CanvasTreeNode<T>::traverse(uint64_t id)
	{
		// check if the current node's id matches the id
		if (this->id == id)
		{
			return shared_from_this();
		}
		// check the node's children for a match
		for (auto child : this->children)
		{
			if (auto result = child->traverse(id))
			{
				return result;
			}
		}
		return {};
	}

    // alias to provide a more readable node type
    template<class T>
    using Node = CanvasTreeNode<T>;

    template<class T>
    class CanvasTree
    {
    public:
        CanvasTree() = default;

        // allocate and set the node data to the specified 'data' parameter
        static std::unique_ptr<Node<T>> makeNode(T data);
        // insert a node into the tree,if no root exists the node becomes the root node
        std::weak_ptr<CanvasTreeNode<T>> insertNode(std::unique_ptr<Node<T>> node, std::weak_ptr<Node<T>> parent);
        // find a node by using the id it was given by insertNode()
        std::weak_ptr<CanvasTreeNode<T>> findNodeById(uint64_t id);
        // remove a node from the tree
        bool removeNode();
        // returns the tree root node, empty if the tree is empty
        std::weak_ptr<Node<T>> getRoot();

    private:
        // a static variable is used to assign ids to nodes on insertion
        static u64 s_id;
        std::shared_ptr<Node<T>> m_root;
    };

    // initialize the id static member
    template<class T>
    u64 CanvasTree<T>::s_id = 0;

    template<class T>
    std::unique_ptr<Node<T>> CanvasTree<T>::makeNode(T data)
    {
        return std::make_unique<Node<T>>(data);
    }

    template<class T>
    std::weak_ptr<Node<T>> CanvasTree<T>::getRoot()
    {
        return { m_root };
    }

    template<class T>
    bool CanvasTree<T>::removeNode()
    {
        return false;
    }

    template<class T>
    std::weak_ptr<Node<T>> CanvasTree<T>::insertNode(std::unique_ptr<Node<T>> node, std::weak_ptr<Node<T>> parent)
    {
        if (!node)
            return {};

        if (!m_root && !parent.lock())
        {
            // make the node the root node, and ignore the parent argument
			// note: ++ operator returns the previous value not the incremented one!
            node->id = s_id++;
            // add an empty parent since it's now the root node, traversing should account for this
            node->parent = {};
            // move the ownership to CanvasTree
            m_root = std::move(node);
			// return a weak_ptr to the root
            return { m_root };
        }

        // if parent node is valid, add node to it
        if (auto parent_node = parent.lock())
        {
            node->id = s_id++;
            // create a weak_ptr to the parent
            node->parent = { parent_node };
            // move the node to the parent's children
            parent_node->children.push_back(std::move(node));
            // return a weak_ptr to the added node
            return { parent_node->children.back() };
        }
        else
        {
            assert(false && "Invalid parent node! it may have been destroyed early or doesn't exist!");
            return {};
        }

        assert(false && "Returning an empty weak_ptr!");
        return {};
    }

    template<class T>
    std::weak_ptr<CanvasTreeNode<T>> CanvasTree<T>::findNodeById(uint64_t id)
    {
        // check if the root node has that id
        if (m_root)
        {
            // if root node has that id, return weak_ptr of the root
            if (m_root->id == id)
                return { m_root };
        }
        else
        {
            // return an empty weak_ptr because the tree is empty
            return {};
        }

        if (auto found = m_root->traverse(id))
        {
            // create a weak_ptr from the shared_ptr that traverse() returned
            return { found };
        }
        else
        {
            // return empty weak_ptr because we didn't find a node with such id
            return {};
        }
    }
}