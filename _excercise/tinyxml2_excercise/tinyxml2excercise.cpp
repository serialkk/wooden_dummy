#include <stdio.h>
#include <iostream>
#include "tinyxml2.h"

int main() {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("sheet.xml");

	//루트 노드 접근
	tinyxml2::XMLDocument* pRoot = doc.FirstChildElement("TextureAtlas");
	if (!pRoot) return;
	else printf("값 읽었음\n");

	return 0;
}