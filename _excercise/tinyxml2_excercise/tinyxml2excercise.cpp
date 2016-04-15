#include <stdio.h>
#include <iostream>
#include "tinyxml2.h"


int main() {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("sheet.xml");

	return 0;
}