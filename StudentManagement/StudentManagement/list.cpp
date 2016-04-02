#include "list.h"
#include <string.h>
#include <string>

#define _CRT_SECURE_NO_WARNINGS




void CNode::print_to_buffer(char * buffer, int size)
{
}

CStudent CStudent::operator=(const CStudent& node) {

	this->num = node.num;
	this->classroom = node.classroom;
	this->eng = node.eng;
	this->math = node.math;
	strcpy(this->Name, node.Name);

	this->num = node.num;
	this->ranks = node.ranks;
	this->sci = node.sci;
	this->total = node.total;

	this->NextNode = NULL;
	this->PrevNode = NULL;

	return *this;
}

ostream& operator << (ostream &os, const CStudent& p)
{
	os << p.Name << "\t" << p.eng << "\t" << p.math << "\t" << p.sci << "\t" << p.total << "\t" << p.ranks << "\t" << p.classroom << "\t" << p.num ;

	return os;
}
istream& operator >> (istream &is, CStudent& p)
{

	printf("이름? > ");
	scanf("%s", p.Name);
	printf("\n영어? > ");
	scanf("%d", &p.eng);
	printf("\n수학? > ");
	scanf("%d", &p.math);
	printf("\n과학? > ");
	scanf("%d", &p.sci);
	printf("\n반번호? > ");
	scanf("%d", &p.classroom);

	p.num = 0; p.ranks = 0;
	p.total = p.sci + p.eng + p.math;

	return is;
}

void CStudent::print_to_buffer(char* buffer, int size)
{
	char buffer2[256] = { 0 };

	strcat(buffer, this->Name); strcat(buffer, "\t");
	_itoa(this->eng, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * size);
	_itoa(this->math, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * size);
	_itoa(this->sci, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * size);
	_itoa(this->total, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * size);
	_itoa(this->ranks, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * size);
	_itoa(this->classroom, buffer2, 10); strcat(buffer, buffer2); strcat(buffer, "\t"); memset(buffer2, 0, sizeof(char) * size);
	_itoa(this->num, buffer2, 10); strcat(buffer, buffer2);  memset(buffer2, 0, sizeof(char) * size);

}