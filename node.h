#include <vector>

class Node {

	private:
		int value;
		std::vector<Node> childrens;
		Node * parent;

	public:
		void addChildren(Node children);
		void setValue(int value);
		Node * getParent();
		void setParent(Node * parent);

};
