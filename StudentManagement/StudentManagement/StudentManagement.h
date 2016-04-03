#ifndef HOMEWORK9
#define HOMEWORK9

#include "list.h"
#include "HashTable.h"

//////////////////////////////////////////////
// 객체 및 배열 할당과 삭제 및 소멸 매크로
//////////////////////////////////////////////
#ifndef SAFE_ZERO
#define SAFE_ZERO(A)				{ A = 0; }
#endif

#ifndef SAFE_NEW
#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
#endif 

#ifndef SAFE_DEL
#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }
#endif 

#ifndef SAFE_NEW_ARRAY
#define SAFE_NEW_ARRAY(A, B, C)		{ if (!A && C) A = new B[C]; }
#endif 

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete [] A; (A)=NULL; }
#endif 

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#endif 

#ifndef SAFE_NEW_CLEAR
#define SAFE_NEW_CLEAR( A, B )			{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#endif 

#ifndef SAFE_NEW_ARRAY_CLEAR
#define NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif








class CStudentManagement {
	
	enum menu_item {
		FIRSTSCREEN, //처음 화면.
		PRINTALL = 1, //1.모두 출력
		FILESAVE,	 //2.파일로 저장(to 파일)
		FILELOAD,	 //3.로드하기 (from 파일)
		INPUTDATA,	 //4.성적 입력
		INPUTMAN,	 //5.인원 추가
		DELDATA,	 //6.인원 삭제
		SORTDATA,	 //7.인원 정렬
		FINDMAN,	 //8.인원 검색
		QUITPROG,	 //9.프로그램 종료
		ERASEALL	 //10.데이터 삭제
	};

	static menu_item g_iMenuNum;
private:
	//////멤버변수
	
	//리스트 구현부
	CStudent* m_List;
	CStudent* m_Current ;

	CList<CStudent> m_list_manage;

	CHashTable* m_HT;

	//////멤버함수
private:
	void printMenu() const ;            //  메뉴 출력
	void printResult(CStudent* List) const ;//1.전체 출력
	void saveToFile(CStudent* List) const; //2.파일로 저장       
	void loadToFile(CStudent** List);//3.파일로 부터 읽어옴
	int inputData(CStudent* List);	 //4.성적 입력         
	void inputMan(CStudent** List);	 //5.인원 추가
	void inputRandomMan(CStudent** List);	 //5.인원 추가 	
	int delData(CStudent* List);	 //6.인원 삭제  ★       
	int sortData(CStudent** List, bool isUp = true);	 //7.인원 정렬  ★
	CStudent* findMan(CStudent* List) const;	 //8.인원 검색  
	CStudent* eraseAll(CStudent* List);	 //10.데이터 삭제

	//////함수오버로딩 연습
	void printResult(CStudent& List) const;//1.전체 출력
	void saveToFile(CStudent& List) const; //2.파일로 저장
	int inputData(CStudent& List);	 //4.성적 입력         
public:
	void run();
	void run2();


	////// 생성자 & 소멸자.
	CStudentManagement();
	~CStudentManagement();

};

#endif

