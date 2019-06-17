#pragma once

#include <vector>
#include <memory>

namespace Algorithm
{
	template <typename distance_type>
	class INode
	{
	public:
		virtual unsigned GetID() const = 0;
		virtual const std::vector<INode*> Neiborhood() const = 0;
		virtual distance_type EstimateDistance(const INode& other) const = 0;
	};

	template <typename distance_type>
	class NodeGraph
	{
	public:
		void AddNode(std::unique_ptr<INode<distance_type>> node);
		INode<distance_type>* GetNode(unsigned id);
		const INode<distance_type>* GetNode(unsigned id) const;

	private:
		std::vector<std::unique_ptr<INode<distance_type>>> m_nodes;
	};

	template <typename distance_type>
	inline void Algorithm::NodeGraph<distance_type>::AddNode(std::unique_ptr<INode<distance_type>> node)
	{
		m_nodes.push_back(std::move(node));
	}

	template <typename distance_type>
	inline Algorithm::INode<distance_type>* Algorithm::NodeGraph<distance_type>::GetNode(unsigned id)
	{
		for (auto& node : m_nodes)
		{
			if (node->GetID() == id)
			{
				return node;
			}
		}

		return nullptr;
	}

	template <typename distance_type>
	inline const Algorithm::INode<distance_type>* Algorithm::NodeGraph<distance_type>::GetNode(unsigned id) const
	{
		for (auto& node : m_nodes)
		{
			if (node->GetID() == id)
			{
				return node;
			}
		}

		return nullptr;
	}

	template <typename distance_type>
	struct PathFindingResult
	{
		std::vector<INode<distance_type>> m_path;
	};

	template <typename distance_type>
	class AStarPathFinding
	{
	public:
		AStarPathFinding();
		void SetGraph(const NodeGraph* graph);
		PathFindingResult FindPath(unsigned start_node_id, unsigned end_node_id);

	private:
		const NodeGraph* m_graph;
	};

	template <typename distance_type>
	inline Algorithm::AStarPathFinding<distance_type>::AStarPathFinding()
		: m_graph(nullptr)
	{

	}

	template <typename distance_type>
	inline void Algorithm::AStarPathFinding<distance_type>::SetGraph(const NodeGraph<distance_type>* graph)
	{
		m_graph = graph;
	}


	template <typename distance_type>
	inline PathFindingResult<distance_type> Algorithm::AStarPathFinding<distance_type>::FindPath(unsigned start_node_id, unsigned end_node_id)
	{
		assert(m_graph);

		struct OpenNode

		auto start_node = m_graph->GetNode(start_node_id);
		auto end_node = m_graph->GetNode(end_node_id);

		std::vector<const INode<distance_type>*> open_node_list;
		std::vector<const INode<distance_type>*> close_node_list;

		open_node_list.push_back(start_node);

		while (true)
		{

		}
	}


}
