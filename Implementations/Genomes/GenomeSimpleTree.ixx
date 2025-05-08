export module GenomeSimpleTree;

export import GenomeTree;

namespace Geneticxx
{
	export template<typename T>
	class GenomeSimpleTree : public GenomeTree {
		std::vector<std::unique_ptr<Genome>> m_children;
		T m_data;

	public:
		explicit GenomeSimpleTree<T>(T data)
		{
			m_data = data;
		}
		~GenomeSimpleTree() override = default;

        std::unique_ptr<Genome> createNew() const override
        {
        	return std::make_unique<GenomeSimpleTree<T>>(m_data);
        }
        std::unique_ptr<Genome> clone() const override
        {
        	auto clone = new GenomeSimpleTree<T>(m_data);
        	clone->m_children.resize(m_children.size());
        	for (size_t i = 0; i < m_children.size(); ++i)
        	{
        		if (m_children[i])
        			clone->m_children[i] = m_children[i]->clone();
        		else
        			clone->m_children[i] = nullptr;
        	}
        	return std::unique_ptr<GenomeSimpleTree<T>>(clone);
        }
        double distance(Genome *other) const override {
        	// Dynamic cast for checking type
        	if (auto otherTree = dynamic_cast<GenomeSimpleTree<T>*>(other))
        	{
        		if constexpr (std::is_arithmetic_v<T>)
        		{
        			return std::abs(static_cast<double>(m_data) - static_cast<double>(otherTree->m_data));
        		}
        		else
        		{
        			// Other metric for not arithmetic types - example:
        			return (m_data == otherTree->m_data) ? 0.0 : 1.0;
        		}
        	}
        	throw std::invalid_argument("Cannot compute distance between different Genome types.");
        }
		/** This implementation uses the traverse function to find the correct node */
        /*std::any getValue(size_t position) const override
        {
        	auto result = traverse(position);
        	if (result != nullptr)
        		return result->m_data;
        	throw std::out_of_range("GenomeSimpleTree<T>::getValue - index out of range");
        }
		/** This implementation traverses the tree in a depth-first order #1#
		GenomeSimpleTree* traverse(size_t &position)
        {
        	if (position == 0) return this;

        	--position;
        	GenomeSimpleTree* temp = nullptr;
        	for (size_t i = 0; i < m_children.size() && temp == nullptr; ++i)
        	{
        		if (m_children[i]) temp = dynamic_cast<GenomeSimpleTree*>(m_children[i].get())->traverse(position);
        	}
        	return temp;
        }
		const GenomeSimpleTree* traverse(size_t &position) const
        {
        	if (position == 0) return this;

        	--position;
        	const GenomeSimpleTree* temp = nullptr;
        	for (size_t i = 0; i < m_children.size() && temp == nullptr; ++i)
        	{
        		if (m_children[i]) temp = dynamic_cast<const GenomeSimpleTree*>(getChild(i))->traverse(position);
        	}
        	return temp;
        }
        void setValue(size_t position, std::any value) override
        {
        	auto result = traverse(position);
        		if (result != nullptr) {
        			try {
        				result->m_data = std::any_cast<T>(value);
        			}
        			catch (const std::bad_any_cast &ex) {
        				std::cout << "GenomeSimpleTree::setValue " << ex.what() << std::endl;
        				throw;
        			}
        		}
        	// throw std::out_of_range("GenomeSimpleTree<T>::getValue");
        }*/
		GenomeSimpleTree<T>* getChild(size_t index)
        {
	        return dynamic_cast<GenomeSimpleTree*>(m_children[index].get());
        }
		const GenomeSimpleTree<T>* getChild(size_t index) const
        {
        	return dynamic_cast<GenomeSimpleTree*>(m_children[index].get());
        }
		void setChild(size_t index, std::unique_ptr<GenomeSimpleTree<T>> child)
        {
        	m_children[index] = std::move(child);
        }
		void setChildrenNumber(size_t size)
        {
        	return m_children.resize(size);
        }
        size_t getSize() const override {
        	size_t size = 1; // current node
        	for (const auto& child : m_children)
        	{
        		if (child)
        			size += child->getSize();
        	}
        	return size;
		}
        bool operator==(Genome *other) const override {
        	auto otherTree = dynamic_cast<GenomeSimpleTree<T>*>(other);
        	if (!otherTree) return false;
        	if (m_data != otherTree->m_data) return false;
        	if (m_children.size() != otherTree->m_children.size()) return false;
        	for (size_t i = 0; i < m_children.size(); i++)
        	{
        		const Genome* child1 = m_children[i].get();
        		const Genome* child2 = otherTree->m_children[i].get();
        		// Zakładamy, że oba mogą być nullptr lub mają operator==
        		if (child1 == nullptr && child2 == nullptr)
        			continue;
        		if ((child1 == nullptr) != (child2 == nullptr))
        			return false;
        		if (!(*child1 == const_cast<Genome*>(child2)))
        			return false;
        	}
        	return true;
        }

	};
}
