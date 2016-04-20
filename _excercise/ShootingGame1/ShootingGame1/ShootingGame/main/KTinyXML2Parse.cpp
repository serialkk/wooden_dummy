#include "KTinyXML2Parse.h"



vector<KImageRect> g_vectorImage;



void tinyxml2Parse(const XMLAttribute* firstAttr, unsigned int indent)
{
	XMLAttribute* attr;
	KImageRect temp;

	for (attr = (XMLAttribute*)firstAttr; attr != 0; attr = (XMLAttribute*)attr->Next()) {

		if (strcmp(attr->Name(), "name") == 0) {
			strcpy_s(temp.m_szName, attr->Value());
		}
		else if (strcmp(attr->Name(), "x") == 0) {
			temp.m_iX = atoi(attr->Value());
		}
		else if (strcmp(attr->Name(), "y") == 0) {
			temp.m_iY = atoi(attr->Value());
		}
		else if (strcmp(attr->Name(), "width") == 0) {
			temp.m_iWidth = atoi(attr->Value());
		}
		else if (strcmp(attr->Name(), "height") == 0) {
			temp.m_iHeight = atoi(attr->Value());

			g_vectorImage.push_back(temp);

			memset(&temp, 0, sizeof(temp));
		}
		else { continue; }


	}
}



void tinyxml2Parse(const XMLNode* parent, unsigned int indent)
{
	if (!parent) return;

	XMLNode* child;

	XMLDeclaration* decl;
	XMLElement* elem;
	XMLComment* comm;
	XMLAttribute* attr;
	XMLText* text;

	for (child = (XMLNode*)parent->FirstChild(); child != 0; child = (XMLNode*)child->NextSibling()) {

		decl = child->ToDeclaration();
		elem = child->ToElement();
		comm = child->ToComment();

		if (elem) {
			attr = (XMLAttribute*)elem->FirstAttribute();
			if (attr) tinyxml2Parse(attr, indent + 1);
		}
		tinyxml2Parse(child, indent + 1);
	}
}

void tinyxml2Parse(const char* filename)
{
	TINYXMLDocument doc;
	if (XML_NO_ERROR == doc.LoadFile(filename)) {
		//printf("\n<Document> %s:\n", filename);
		tinyxml2Parse(&doc);
	}
	else {
		//printf("Failed to open: %s\n", filename);
	}
}

KTinyXML2Parse::KTinyXML2Parse()
{
}


KTinyXML2Parse::~KTinyXML2Parse()
{
}
