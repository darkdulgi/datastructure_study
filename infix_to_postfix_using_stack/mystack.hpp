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
	bool empty() const;			//������ ��������� 1�� ��ȯ
	Item top() const;			//���� ���� ���Ҹ� ��ȯ
	size_t size() const;		//���� �� ������ �� ��ȯ

	class dnode {	// double linked list ���
	public:
		dnode(const Item&, dnode*, dnode*);	//������
		dnode(const Item&);
		void set_data(const Item&);			//������ �Է�
		void set_forelink(dnode*);					//���� ��带 ����Ű�� ������(link_fore) �Է�
		void set_backlink(dnode*);					//���� ��带 ����Ű�� ������(link_back) �Է�
		Item data() const;							//������ ��ȯ
		dnode* forelink();							//forelink ��ȯ
		const dnode* forelink()const;
		dnode* backlink();							//backlink ��ȯ
		const dnode* backlink()const;

		size_t list_length(const dnode*);			//����Ʈ�� ���� ��ȯ
		static void list_head_insert(dnode*&, const Item&);			//����Ʈ �պκп� ��� ����
		static void list_insert(dnode*, const Item&);				//����Ʈ�� Ư�� �κп� ��� ����
		static void list_copy(const dnode*, dnode*&, dnode*&);				//����Ʈ ����
		static void list_head_remove(dnode*&);								//����Ʈ�� �� ��� ����
		void list_clear(dnode*&);									//����Ʈ �� ��� ��� ����
	private:
		Item data_field;		//����� ������
		dnode* link_fore;			//�� ��带 ����Ű�� ������. ������ NULL
		dnode* link_back;			//�� ��带 ����Ű�� ������. ������ NULL
	};

private:
	dnode* top_ptr;
};
