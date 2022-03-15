#include "mystack.hpp"

template <class Item>
stack<Item>::dnode::dnode(const Item& init_data, dnode* init_fore, dnode* init_back) {
	data_field = init_data;
	link_fore = init_fore;
	link_back = init_back;
}
template <class Item>
stack<Item>::dnode::dnode(const Item& init_data) {
	data_field = init_data;
	link_fore = NULL;
	link_back = NULL;
}
template <class Item>
void stack<Item>::dnode::set_data(const Item& new_data) { data_field = new_data; }
template <class Item>
void stack<Item>::dnode::set_forelink(dnode* new_link) { link_fore = new_link; }
template <class Item>
void stack<Item>::dnode::set_backlink(dnode* new_link) { link_back = new_link; }
template <class Item>
Item stack<Item>::dnode::data() const { return data_field; }
template <class Item>
typename stack<Item>::dnode* stack<Item>::dnode::forelink() { return link_fore; }
template <class Item>
const typename stack<Item>::dnode* stack<Item>::dnode::forelink()const { return link_fore; }
template <class Item>
typename stack<Item>::dnode* stack<Item>::dnode::backlink() { return link_back; }
template <class Item>
typename const stack<Item>::dnode* stack<Item>::dnode::backlink()const { return link_back; }

template <class Item>
size_t stack<Item>::dnode::list_length(const dnode* head_ptr) {
	size_t answer = 0;
	const dnode* cursor;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->forelink())
		++answer;
	return answer;
}

template <class Item>
void  stack<Item>::dnode::list_head_insert(dnode*& head_ptr, const Item& entry) {
	head_ptr = new dnode(entry, head_ptr, NULL);
	if (head_ptr->forelink() != NULL)	//새로운 노드를 생성한 뒤 리스트의 노드 개수가 2개 이상이라면 2번째 노드의 backlink를 첫번째 노드의 포인터로 설정한다.
		(head_ptr->forelink())->set_backlink(head_ptr);
}

template <class Item>
void  stack<Item>::dnode::list_insert(dnode* previous_ptr, const Item& entry) {
	previous_ptr->set_forelink(new dnode(entry, previous_ptr->forelink(), previous_ptr));	//list_head_insert와 마찬가지로 생성한 노드의 뒤 노드의 backlink를 생성한 노드의 포인터로 설정한다.
	dnode* insert_ptr = previous_ptr->forelink();
	if (insert_ptr->forelink() == NULL) return;
	(insert_ptr->forelink())->set_backlink(insert_ptr);
}

template <class Item>
void  stack<Item>::dnode::list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr) {
	head_ptr = NULL;
	tail_ptr = NULL;
	if (source_ptr == NULL) return;
	list_head_insert(head_ptr, source_ptr->data());
	tail_ptr = head_ptr;
	source_ptr = source_ptr->forelink();
	while (source_ptr != NULL) {
		list_insert(tail_ptr, source_ptr->data());
		tail_ptr = tail_ptr->forelink();
		source_ptr = source_ptr->forelink();
	}
}

template <class Item>
void  stack<Item>::dnode::list_head_remove(dnode*& head_ptr) {
	dnode* remove_ptr = head_ptr;
	head_ptr = head_ptr->forelink();
	if (head_ptr != NULL) head_ptr->set_backlink(NULL);	//리스트에 노드가 2개 이상이라면 2번째 노드의 backlink를 NULL로 설정한다.
	delete remove_ptr;
}

template <class Item>
void stack<Item>::dnode::list_clear(dnode*& head_ptr) {
	while (head_ptr != NULL)
		list_head_remove(head_ptr);
}
//===============================================================
template <class Item>
stack<Item>::stack() {
	top_ptr = NULL;
}

template <class Item>
stack<Item>::~stack() {
	dnode* temp = NULL;
	temp->list_clear(top_ptr);
}
template <class Item>
stack<Item>::stack(const stack<Item>& source) {
	dnode* tail_ptr;
	dnode::list_copy(source.top_ptr, top_ptr, tail_ptr);
}
template <class Item>
void stack<Item>::push(const Item& entry) {
	dnode::list_head_insert(top_ptr, entry);
}
template <class Item>
void stack<Item>::pop() {
	assert(!empty());
	dnode::list_head_remove(top_ptr);
}
template <class Item>
bool stack<Item>::empty() const {
	return top_ptr == NULL;
}
template <class Item>
Item stack<Item>::top() const {
	assert(!empty());
	return top_ptr->data();
}

template <class Item>
size_t stack<Item>::size() const {
	return top_ptr->list_length(top_ptr);
}