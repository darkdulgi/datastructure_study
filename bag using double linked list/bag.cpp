#include "bag.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

//각 함수의 기능에 대한 간략한 설명은 bag.h 에서.

//----------------------dnode---------------------
bag::dnode::dnode(const value_type& init_data = value_type(), dnode* init_fore = NULL, dnode* init_back = NULL) {
	data_field = init_data;
	link_fore = init_fore;
	link_back = init_back;
}

void bag::dnode::set_data(const value_type& new_data) { data_field = new_data; }
void bag::dnode::set_forelink(dnode* new_link) { link_fore = new_link; }
void bag::dnode::set_backlink(dnode* new_link) { link_back = new_link; }
bag::value_type bag::dnode::data() const { return data_field; }
bag::dnode* bag::dnode::forelink() { return link_fore; }
const bag::dnode* bag::dnode::forelink()const { return link_fore; }
bag::dnode* bag::dnode::backlink() { return link_back; }
const bag::dnode* bag::dnode::backlink()const { return link_back; }

size_t bag::dnode::list_length(const dnode* head_ptr) {
	size_t answer = 0;
	const dnode* cursor;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->forelink())
		++answer;
	return answer;
}

void bag::dnode::list_head_insert(dnode*& head_ptr, const value_type& entry) {	
	head_ptr = new dnode(entry, head_ptr, NULL);
	if(head_ptr->forelink()!=NULL)	//새로운 노드를 생성한 뒤 리스트의 노드 개수가 2개 이상이라면 2번째 노드의 backlink를 첫번째 노드의 포인터로 설정한다.
		(head_ptr->forelink())->set_backlink(head_ptr);
}

void bag::dnode::list_insert(dnode* previous_ptr, const value_type& entry) {
	previous_ptr->set_forelink(new dnode(entry, previous_ptr->forelink(), previous_ptr));	//list_head_insert와 마찬가지로 생성한 노드의 뒤 노드의 backlink를 생성한 노드의 포인터로 설정한다.
	dnode* insert_ptr = previous_ptr->forelink();
	if (insert_ptr->forelink() == NULL) return;
	(insert_ptr->forelink())->set_backlink(insert_ptr);
}

bag::dnode* bag::dnode::list_search(dnode* head_ptr, const value_type& target) {
	dnode* cursor;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->forelink()) {
		if (target == cursor->data())
			return cursor;
	}
	return NULL;
}

const bag::dnode* bag::dnode::list_search(const dnode* head_ptr, const value_type& target) {
	const dnode* cursor;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->forelink()) {
		if (target == cursor->data())
			return cursor;
	}
	return NULL;
}

bag::dnode* bag::dnode::list_locate(dnode* head_ptr, size_t position) {
	dnode* cursor = head_ptr;
	size_t i;
	assert(0 < position);
	for (i = 1; (cursor != NULL && i < position); ++i)
		cursor = cursor->forelink();
	return cursor;
}

const bag::dnode* bag::dnode::list_locate(const dnode* head_ptr, size_t position) {
	const dnode* cursor = head_ptr;
	size_t i;
	assert(0 < position);
	for (i = 1; (cursor != NULL && i < position); ++i)
		cursor = cursor->forelink();
	return cursor;
}

void bag::dnode::list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr) {
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

void bag::dnode::list_head_remove(dnode*& head_ptr) {
	dnode* remove_ptr = head_ptr;
	head_ptr = head_ptr->forelink();
	if (head_ptr != NULL) head_ptr->set_backlink(NULL);	//리스트에 노드가 2개 이상이라면 2번째 노드의 backlink를 NULL로 설정한다.
	delete remove_ptr;
}

void bag::dnode::list_remove(dnode* previous_ptr) {
	dnode* remove_ptr = previous_ptr->forelink();
	previous_ptr->set_forelink(remove_ptr->forelink());
	if (previous_ptr->forelink() == NULL)return;
	(previous_ptr->forelink())->set_backlink(previous_ptr);	//list_head_remove 와 마찬가지로 삭제한 노드의 뒤의 노드의 backlink를 NULL 또는 삭제한 노드의 앞의 노드의 포인터로 설정한다.
	delete remove_ptr;
}

void bag::dnode::list_clear(dnode*& head_ptr) {
	while (head_ptr != NULL)
		list_head_remove(head_ptr);
}
//--------------------bag-------------------------
bag::bag() {
	head_ptr = NULL;
	many_nodes = 0;
}

bag::bag(const bag& source) {
	dnode* tail_ptr;
	dnode* temp = NULL;
	temp->list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
}

bag::~bag() {
	dnode* temp = NULL;
	temp->list_clear(head_ptr);
}

void bag::operator=(const bag& source) {
	dnode* tail_ptr;
	dnode* temp = NULL;
	if (this == &source) return;
	temp->list_clear(head_ptr);
	temp->list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
}

void bag::operator+=(const bag& addend) {	//두 bag을 앞뒤로 이어붙인 뒤 호출한 bag에 덮어쓰기 한다.
	dnode* copy_tail_ptr;
	dnode* copy_head_ptr;
	dnode* temp = NULL;
	if (addend.many_nodes > 0) {
		temp->list_copy(addend.head_ptr, copy_head_ptr, copy_tail_ptr);
		copy_tail_ptr->set_forelink(head_ptr);
		(copy_tail_ptr->forelink())->set_backlink(copy_tail_ptr);
		head_ptr = copy_head_ptr;
		many_nodes += addend.many_nodes;
	}
}

bag bag::operator+(const bag& add) {	//두 bag을 이어붙이고 반환만 할 뿐 두 bag의 내용이 변하진 않는다.
	bag ans = (*this);

	ans += add;
	return ans;
}

bool bag::operator==(const bag& source) {
	if (many_nodes != source.many_nodes) return 0;
	dnode* cursor1 = head_ptr;
	dnode* cursor2 = source.head_ptr;
	while (cursor1 != NULL) {
		if (cursor1->data() != cursor2->data()) return 0;
		cursor1 = cursor1->forelink();
		cursor2 = cursor2->forelink();
	}
	return 1;
}

bool bag::operator!=(const bag& source) {
	bag ans = (*this);
	return !(ans == source);
}

bool bag::erase_one(const value_type& target) {
	dnode* target_ptr;
	dnode* temp = NULL;
	target_ptr = temp->list_search(head_ptr, target);
	if (target_ptr == NULL) return 0;
	target_ptr->set_data(head_ptr->data());
	temp->list_head_remove(head_ptr);
	many_nodes--;
	return 1;
}

bag::size_type bag::count(const value_type& target)const {
	size_type answer = 0;
	dnode* temp = NULL;
	const dnode* cursor;
	cursor = temp->list_search(head_ptr, target);
	while (cursor != NULL) {
		answer++;
		cursor = cursor->forelink();
		cursor = temp->list_search(cursor, target);
	}
	return answer;
}

bag::size_type bag::size() {
	return head_ptr->list_length(head_ptr);
}

bag::value_type bag::grab() {
	dnode* temp = NULL;
	size_type i;
	const dnode* cursor;
	assert(size() > 0);
	i = (rand() % size()) + 1;
	cursor = temp->list_locate(head_ptr, i);
	return cursor->data();
}

void bag::insert(const value_type& entry) {
	dnode* temp = NULL;
	temp->list_head_insert(head_ptr, entry);
	many_nodes++;
}

void bag::show_contents() {
	const dnode* cursor = head_ptr;
	cout << "Showing contents of bag: ";
	if (many_nodes == 0) {
		cout << "EMPTY\n";
		return;
	}
	while (cursor != NULL) {
		cout << cursor->data() << ' ';
		cursor = cursor->forelink();
	}
	cout << '\n';
}

void bag::bagsort() {		//bag 내 데이터의 정렬을 위해 버블 정렬을 이용했다.
	if (many_nodes == 1 || many_nodes == 0) return;
	dnode* cursor = head_ptr->forelink();
	for (int i = 0; i < many_nodes-1; i++) {
		while (cursor != NULL) {
			if ((cursor->backlink())->data() > cursor->data()) {
				value_type temp = cursor->data();
				cursor->set_data((cursor->backlink())->data());
				(cursor->backlink())->set_data(temp);
			}
			cursor = cursor->forelink();
		}
		cursor = head_ptr->forelink();
	}
	
}