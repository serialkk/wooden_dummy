#include <stdio.h>
#include <iostream>
#include "tinyxml2.h"

int main() {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("sheet.xml");

	//��Ʈ ��� ����
	tinyxml2::XMLDocument* pRoot = doc.FirstChildElement("TextureAtlas");
	if (!pRoot) return;
	else printf("�� �о���\n");

	return 0;
}