#pragma once
#include "stddef.h"
#include <cassert>
#include <cstdlib>

using namespace std;
template<class Item>
class stack {
public:
	stack();
	~stack();
	stack(const stack&);
	void push(const Item&);
	void pop();
	bool empty() const;			//스택이 비어있으면 1을 반환
	Item top() const;			//가장 위의 원소를 반환
	size_t size() const;		//스택 내 원소의 수 반환

	class dnode {	// double linked list 노드
	public:
		dnode(const Item&, dnode*, dnode*);	//생성자
		dnode(const Item&);
		void set_data(const Item&);			//데이터 입력
		void set_forelink(dnode*);					//앞의 노드를 가리키는 포인터(link_fore) 입력
		void set_backlink(dnode*);					//뒤의 노드를 가리키는 포인터(link_back) 입력
		Item data() const;							//데이터 반환
		dnode* forelink();							//forelink 반환
		const dnode* forelink()const;
		dnode* backlink();							//backlink 반환
		const dnode* backlink()const;

		size_t list_length(const dnode*);			//리스트의 길이 반환
		static void list_head_insert(dnode*&, const Item&);			//리스트 앞부분에 노드 삽입
		static void list_insert(dnode*, const Item&);				//리스트의 특정 부분에 노드 삽입
		static void list_copy(const dnode*, dnode*&, dnode*&);				//리스트 복사
		static void list_head_remove(dnode*&);								//리스트의 앞 노드 삭제
		void list_clear(dnode*&);									//리스트 내 모든 노드 삭제
	private:
		Item data_field;		//노드의 데이터
		dnode* link_fore;			//앞 노드를 가리키는 포인터. 없으면 NULL
		dnode* link_back;			//뒤 노드를 가리키는 포인터. 없으면 NULL
	};

private:
	dnode* top_ptr;
};
