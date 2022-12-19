#include<iostream>
#include<algorithm>
#include<list>
#include<forward_list>
#include<stack>
#include <vector>
#include<queue>
using namespace std;




template <typename T>
struct BinaryTreeNode {
	T data;
	unique_ptr<BinaryTreeNode<T>> left, right;
};

class Stack {
private:
	stack<int> element_;

	struct MaxWithCount {
		int max, count;
	};
	stack<MaxWithCount> cached_max_with_count_;

public:
	bool Empty() const { return element_.empty(); }

	int Max() const {
		if (Empty()) {
			throw length_error("Max(): empty stack");
		}
		return cached_max_with_count_.top().max;
	}

	int Pop() {
		if (Empty()) {
			throw length_error("Pop(): empty stack");
		}
		int pop_element = element_.top();
		element_.pop();
		const int current_max = cached_max_with_count_.top().max;
		if (pop_element == current_max) {
			int& max_frequency = cached_max_with_count_.top().count;
			--max_frequency;
			if (max_frequency == 0) {
				cached_max_with_count_.pop();
			}
		}
		return pop_element;
	}

	void Push(int x) {
		element_.emplace(x);
		if (cached_max_with_count_.empty()) {
			cached_max_with_count_.emplace(MaxWithCount{ x,1 });
		}
		else {
			const int current_max = cached_max_with_count_.top().max;
			if (x == current_max) {
				int& max_frequency = cached_max_with_count_.top().count;
				++max_frequency;
			}
			else if(x>current_max){
				cached_max_with_count_.emplace(MaxWithCount{ x,1 });
			}
		}
	}
};

template <typename T>
struct ListNode {
	T data;
	shared_ptr<ListNode<T>> next;
};

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
	shared_ptr <ListNode<int>> L2) {
	shared_ptr <ListNode<int>> dummy_head(new ListNode<int>);

	auto tail = dummy_head;

	while (L1 && L2) {
		AppendNode(L1->data <= L2->data ? &L1 : &L2, &tail);
	}
	tail->next = L1 ? L1 : L2;
	return dummy_head->next;
}

void AppendNode(shared_ptr<ListNode<int>>* node, shared_ptr<ListNode<int>>* tail) {
	(*tail)->next = *node;
	*tail = *node;
	*node = (*node)->next;
}
