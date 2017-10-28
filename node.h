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
		Node * getParent();
		void setParent(Node * parent);
		unsigned int getCount();
		void doPrint(int level);
		void doPrint();

};
