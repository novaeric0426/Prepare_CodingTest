#include<iostream>
#include<queue>
using namespace std;

struct node {
	string position;
	node* first;
	node* second;
};

struct org_tree {
	node* root;

	static org_tree create_org_structure(const string& pos) {
		org_tree tree;
		tree.root = new node{ pos,NULL,NULL };
		return tree;
	}
	static node* find(node* root, const string& value) {
		if (root == NULL)
			return NULL;
		if (root->position == value)
			return root;
		auto firstFound = org_tree::find(root->first, value);
		if (firstFound != NULL)
			return firstFound;
		return org_tree::find(root->second, value);
	}

	bool addSubordinate(const string& manager, const string& subordinate) {
		auto managerNode = org_tree::find(root, manager);
		if (!managerNode)
		{
			std::cout << manager << "��(��) ã�� �� �����ϴ�: " << std::endl;
			return false;
		}
		if (managerNode->first && managerNode->second) {
			cout << manager << " �Ʒ��� " << subordinate << " �� �߰��� �� �����ϴ�." << endl;
			return false;
		}

		if (!managerNode->first)
			managerNode->first = new node{ subordinate,NULL,NULL };
		else
			managerNode->second = new node{ subordinate,NULL,NULL };

		cout << manager << " �Ʒ��� " << subordinate << " �� �߰��߽��ϴ�." << endl;

		return true;
	}

	//��ȸ ����
	static void preOrder(node* start) { //���� ��ȸ(current,left,right ��)
		if (!start)
			return;
		cout << start->position << ", ";
		preOrder(start->first);
		preOrder(start->second);
	}

	static void levelOrder(node* start) {
		if (!start)
			return;
		queue<node*> q;
		q.push(start);
		
		while (!q.empty()) {
			int size = q.size();
			for (int i = 0; i < size; i++) {
				auto current = q.front();
				q.pop();

				cout << current->position << ", ";
				if (current->first)
					q.push(current->first);
				if (current->second)
					q.push(current->second);
			}
			cout << endl;
		}
	}
};

int main() {
	auto tree = org_tree::create_org_structure("CEO");

	tree.addSubordinate("CEO", "�λ���");
	tree.addSubordinate("�λ���", "IT����");
	tree.addSubordinate("�λ���", "�����ú���");
	tree.addSubordinate("IT����", "��������");
	tree.addSubordinate("IT����", "�۰�������");
	tree.addSubordinate("�����ú���", "��������");
	tree.addSubordinate("�����ú���", "ȫ������");
	tree.addSubordinate("�λ���", "�繫����");

	org_tree::levelOrder(tree.root);
	return 0;
}