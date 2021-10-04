#pragma once
#include "stddef.h"

using namespace std;

	class bag {		//dnode Ŭ������ bag�� ������ ���� Ŭ�����̱� ������ bag�� ����Ŭ������ ����.
	public:
		typedef int value_type;
		typedef size_t size_type;

		class dnode {	//double linked list ���
		public:
			dnode(const value_type&, dnode*, dnode*);	//������
			void set_data(const value_type&);			//������ �Է�
			void set_forelink(dnode*);					//���� ��带 ����Ű�� ������(link_fore) �Է�
			void set_backlink(dnode*);					//���� ��带 ����Ű�� ������(link_back) �Է�
			value_type data() const;					//������ ��ȯ
			dnode* forelink();							//forelink ��ȯ
			const dnode* forelink()const;				
			dnode* backlink();							//backlink ��ȯ
			const dnode* backlink()const;

			size_t list_length(const dnode*);			//����Ʈ�� ���� ��ȯ
			void list_head_insert(dnode*&, const value_type&);			//����Ʈ �պκп� ��� ����
			void list_insert(dnode*, const value_type&);				//����Ʈ�� Ư�� �κп� ��� ����
			dnode* list_search(dnode*, const value_type&);				//����Ʈ���� Ư�� �����Ͱ� �� ù��° ����� ������ ��ȯ
			const dnode* list_search(const dnode*, const value_type&);	
			dnode* list_locate(dnode*, size_t);							//����Ʈ���� Ư�� ��° ����� ������ ��ȯ
			const dnode* list_locate(const dnode*, size_t);
			void list_copy(const dnode*, dnode*&, dnode*&);				//����Ʈ ����
			void list_head_remove(dnode*&);								//����Ʈ�� �� ��� ����
			void list_remove(dnode*);									//����Ʈ�� Ư�� ��� ����
			void list_clear(dnode*&);									//����Ʈ �� ��� ��� ����
		private:
			value_type data_field;		//����� ������
			dnode* link_fore;			//�� ��带 ����Ű�� ������. ������ NULL
			dnode* link_back;			//�� ��带 ����Ű�� ������. ������ NULL
		};

		bag();				//������
		bag(const bag&);	//���� ������
		~bag();				//�Ҹ���
		void operator=(const bag&);					//���� ������ �����ε�
		void operator+=(const bag&);				//�� ���� bag�� �ٿ��� ȣ���� bag�� ����
		bag operator+(const bag&);					//�� ���� bag�� �ٿ��� ��ȯ��
		bool operator==(const bag&);				//�� ������ �����ε�
		bool operator!=(const bag&);				
		bool erase_one(const value_type&);			//Ư�� �����͸� bag���� ����
		size_type count(const value_type&)const;	//bag�� Ư�� �������� ���� ��ȯ
		value_type grab();							//bag �� ������ ������ ��ȯ
		void insert(const value_type&);				//Ư�� ������ ����
		size_type size();							//bag �� ������ �� ��ȯ
		void bagsort();								//bag �� �����͸� ������������ ����

		void show_contents();						//bag�� ��� ������ ���
	private:
		dnode* head_ptr;
		size_type many_nodes;
	};
