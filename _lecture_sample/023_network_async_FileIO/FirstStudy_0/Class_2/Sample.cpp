#include "TSon.h"

void add(TParent* a )
{

}
void main()
{
	//TParent d;
	//TParent* e = new TParent;
	
	TManager mgr;
	Ta* ta = new Ta;
	add(ta);

	a->SetMoney(100);
	TParent* b = new Tb;
	b->SetMoney(200);
	TParent* c = new Tc;
	c->SetMoney(300);
	mgr.Add(a, 0);// new Ta);
	mgr.Add(b, 1);// new Ta);
	mgr.Add(c, 2);// new Ta);
	mgr.Show();
	delete a;
	delete b;
	delete c;
	//TParent* GameEngine[3];
	//TObject * obj = new TObject;
	//GameEngine[0] = obj;
	//GameEngine[1] = new TEffect;
	//GameEngine[2] = new TMap;
	//// frame
	//for (int i = 0; i < 3; i++)
	//{
	//	GameEngine[i]->SetMoney(10000);
	//}
	

	//TSon* son = new TSon;
	////son->m_iMoney = 1000;
	//son->SetMoney(1000);
	//std::cout << son->GetMoney() << std::endl;


	//TParent* parent = new TParent;
	//parent->SetMoney(1000);

	TParent*  parent = new TChild;
	//parent->m_iMoney = 1000;
	//std::cout << parent->m_iMoney << std::endl;		
	parent->SetMoney(1000);
	std::cout << parent->GetMoney() << std::endl;
	//child->m_iMoney = 1000;
	//delete parent;
	delete parent;

	std::cout <<"ÀüÃ¼¼Ò¸ê!";
}