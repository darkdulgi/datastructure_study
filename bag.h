#pragma once
#include "stddef.h"

using namespace std;

	class bag {		//dnode 클래스는 bag의 구현을 위한 클래스이기 때문에 bag의 내부클래스로 정의.
	public:
		typedef int value_type;
		typedef size_t size_type;

		class dnode {	//double linked list 노드
		public:
			dnode(const value_type&, dnode*, dnode*);	//생성자
			void set_data(const value_type&);			//데이터 입력
			void set_forelink(dnode*);					//앞의 노드를 가리키는 포인터(link_fore) 입력
			void set_backlink(dnode*);					//뒤의 노드를 가리키는 포인터(link_back) 입력
			value_type data() const;					//데이터 반환
			dnode* forelink();							//forelink 반환
			const dnode* forelink()const;				
			dnode* backlink();							//backlink 반환
			const dnode* backlink()const;

			size_t list_length(const dnode*);			//리스트의 길이 반환
			void list_head_insert(dnode*&, const value_type&);			//리스트 앞부분에 노드 삽입
			void list_insert(dnode*, const value_type&);				//리스트의 특정 부분에 노드 삽입
			dnode* list_search(dnode*, const value_type&);				//리스트에서 특정 데이터가 들어간 첫번째 노드의 포인터 반환
			const dnode* list_search(const dnode*, const value_type&);	
			dnode* list_locate(dnode*, size_t);							//리스트에서 특정 번째 노드의 포인터 반환
			const dnode* list_locate(const dnode*, size_t);
			void list_copy(const dnode*, dnode*&, dnode*&);				//리스트 복사
			void list_head_remove(dnode*&);								//리스트의 앞 노드 삭제
			void list_remove(dnode*);									//리스트의 특정 노드 삭제
			void list_clear(dnode*&);									//리스트 내 모든 노드 삭제
		private:
			value_type data_field;		//노드의 데이터
			dnode* link_fore;			//앞 노드를 가리키는 포인터. 없으면 NULL
			dnode* link_back;			//뒤 노드를 가리키는 포인터. 없으면 NULL
		};

		bag();				//생성자
		bag(const bag&);	//복사 생성자
		~bag();				//소멸자
		void operator=(const bag&);					//대입 연산자 오버로딩
		void operator+=(const bag&);				//두 개의 bag을 붙여서 호출한 bag에 대입
		bag operator+(const bag&);					//두 개의 bag을 붙여서 반환함
		bool operator==(const bag&);				//비교 연산자 오버로딩
		bool operator!=(const bag&);				
		bool erase_one(const value_type&);			//특정 데이터를 bag에서 삭제
		size_type count(const value_type&)const;	//bag의 특정 데이터의 개수 반환
		value_type grab();							//bag 내 랜덤한 데이터 반환
		void insert(const value_type&);				//특정 데이터 삽입
		size_type size();							//bag 내 데이터 수 반환
		void bagsort();								//bag 내 데이터를 오름차순으로 정렬

		void show_contents();						//bag내 모든 데이터 출력
	private:
		dnode* head_ptr;
		size_type many_nodes;
	};
