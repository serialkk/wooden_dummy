#include <stdio.h>
#include <vector>
#include "Box.h"

using namespace std;

vector<CBox*> g_vectorBox;

void frame();
void render();
int main() {
	
	g_vectorBox.push_back(new CBox("penguin",10));
	g_vectorBox.push_back(new CBox("penguin1", 9));
	g_vectorBox.push_back(new CBox("penguin2", 8));
	g_vectorBox.push_back(new CBox("penguin3", 7));
	g_vectorBox.push_back(new CBox("penguin4", 10));
	g_vectorBox.push_back(new CBox("penguin5", 1));
	g_vectorBox.push_back(new CBox("penguin6", 2));
	g_vectorBox.push_back(new CBox("penguin7", 3));
	g_vectorBox.push_back(new CBox("penguin8", 4));

	vector<CBox*>::iterator _F = g_vectorBox.begin();
	vector<CBox*>::iterator _L = g_vectorBox.end();

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
		delete (*_F);
	}
	g_vectorBox.clear();


	return 0;
}

void frame() {
	vector<CBox*>::iterator _F = g_vectorBox.begin();
	vector<CBox*>::iterator _L = g_vectorBox.end();

	for (; _F != _L; ++_F)
	{
		if (strcmp((*_F)->m_szStr, "penguin") == 0) {
			(*_F)->m_iNum = 2;
		}
	}

	_F = g_vectorBox.begin();
	_L = g_vectorBox.end();
	for (; _F != _L; ++_F)
	{
		if (strcmp((*_F)->m_szStr, "penguin1") == 0) {
			delete (*_F);
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