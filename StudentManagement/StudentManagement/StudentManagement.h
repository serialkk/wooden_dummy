#ifndef HOMEWORK9
#define HOMEWORK9

#include "list.h"
#include "HashTable.h"

//////////////////////////////////////////////
// ��ü �� �迭 �Ҵ�� ���� �� �Ҹ� ��ũ��
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
		FIRSTSCREEN, //ó�� ȭ��.
		PRINTALL = 1, //1.��� ���
		FILESAVE,	 //2.���Ϸ� ����(to ����)
		FILELOAD,	 //3.�ε��ϱ� (from ����)
		INPUTDATA,	 //4.���� �Է�
		INPUTMAN,	 //5.�ο� �߰�
		DELDATA,	 //6.�ο� ����
		SORTDATA,	 //7.�ο� ����
		FINDMAN,	 //8.�ο� �˻�
		QUITPROG,	 //9.���α׷� ����
		ERASEALL	 //10.������ ����
	};

	static menu_item g_iMenuNum;
private:
	//////�������
	
	//����Ʈ ������
	CStudent* m_List;
	CStudent* m_Current ;

	CList<CStudent> m_list_manage;

	CHashTable* m_HT;

	//////����Լ�
private:
	void printMenu() const ;            //  �޴� ���
	void printResult(CStudent* List) const ;//1.��ü ���
	void saveToFile(CStudent* List) const; //2.���Ϸ� ����       
	void loadToFile(CStudent** List);//3.���Ϸ� ���� �о��
	int inputData(CStudent* List);	 //4.���� �Է�         
	void inputMan(CStudent** List);	 //5.�ο� �߰�
	void inputRandomMan(CStudent** List);	 //5.�ο� �߰� 	
	int delData(CStudent* List);	 //6.�ο� ����  ��       
	int sortData(CStudent** List, bool isUp = true);	 //7.�ο� ����  ��
	CStudent* findMan(CStudent* List) const;	 //8.�ο� �˻�  
	CStudent* eraseAll(CStudent* List);	 //10.������ ����

	//////�Լ������ε� ����
	void printResult(CStudent& List) const;//1.��ü ���
	void saveToFile(CStudent& List) const; //2.���Ϸ� ����
	int inputData(CStudent& List);	 //4.���� �Է�         
public:
	void run();
	void run2();


	////// ������ & �Ҹ���.
	CStudentManagement();
	~CStudentManagement();

};

#endif

