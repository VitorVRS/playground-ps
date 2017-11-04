#include <vector>
#include <string>

class Node {

	private:
		std::string value;
		std::vector<Node *> childrens;
		Node * parent;
		unsigned int count;

	public:
		Node();
		void addChildren(Node * children);
		void setValue(std::string value);
		void setParent(Node * parent);
		void doPrint(unsigned int level);
		void doPrint();

};
