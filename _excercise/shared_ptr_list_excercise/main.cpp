#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <list>
#include "Box.h"
#include <memory>

using namespace std;
//shared_ptr +
list<shared_ptr<CBox>> g_vectorBox;

void frame();
void render();
int main() {
	
	auto pBox = make_shared<CBox>(10);
	g_vectorBox.push_back(pBox);

	pBox = make_shared<CBox>(2);
	g_vectorBox.push_back(pBox);

	pBox = make_shared<CBox>(3);
	g_vectorBox.push_back(pBox);

	pBox = make_shared<CBox>(11);
	g_vectorBox.push_back(pBox);


	list<shared_ptr<CBox>>::iterator _F = g_vectorBox.begin();
	list<shared_ptr<CBox>>::iterator _L = g_vectorBox.end();

	for (; _F != _L; ++_F)
	{
		printf("name : %s, num : %d \n", (*_F)->m_szStr, (*_F)->m_iNum);
	}

	frame();

	_F= g_vectorBox.begin();
	_L=g_vectorBox.end();

	for (; _F != _L; ++_F)
	{
		printf("name : %s, num : %d \n", (*_F)->m_szStr, (*_F)->m_iNum);
	}

	_F = g_vectorBox.begin();
	_L = g_vectorBox.end();

	for (; _F != _L; ++_F)
	{
		_F->reset();//delete (*_F);
	}
	g_vectorBox.clear();


	return 0;
}

void frame() {
	list<shared_ptr<CBox>>::iterator _F = g_vectorBox.begin();
	list<shared_ptr<CBox>>::iterator _L = g_vectorBox.end();

	for (; _F != _L; ++_F)
	{
		if ((*_F)->m_iNum == 2) {
			(*_F)->m_iNum = 13;
		}
	}

	_F = g_vectorBox.begin();
	_L = g_vectorBox.end();
	for (; _F != _L; ++_F)
	{
		if ((*_F)->m_iNum == 10) {
			_F->reset();//delete (*_F);
			*_F = 0;
		}
	}

	_F = g_vectorBox.begin();
	while (_F != g_vectorBox.end())
	{
		if (*_F == 0) {

				_F = g_vectorBox.erase(_F);
		}
		else {
			_F++;
		}
	}
};
void render() {

};