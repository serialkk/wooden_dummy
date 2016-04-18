#include <stdio.h>
#include <iostream>
#include "tinyxml2.h"


using namespace tinyxml2;
using namespace std;

void createSimpleDoc(const char* filename)
{
	XMLDocument doc;
	XMLDeclaration* decl = doc.NewDeclaration();    // <?xml version="1.0" encoding="UTF-8"?>
	XMLElement* element = doc.NewElement("Hello");
	XMLText* text = doc.NewText("World");
	element->LinkEndChild(text);
	doc.LinkEndChild(decl);
	doc.LinkEndChild(element);
	doc.SaveFile(filename); // writing document to a file
}

void createMoreComplicatedDoc(const char* filename)
{
	XMLDocument doc;
	XMLDeclaration* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);

	XMLElement* root = doc.NewElement("MyApp");
	doc.LinkEndChild(root);

	XMLComment* comment = doc.NewComment("Settings for MyApp");
	root->LinkEndChild(comment);

	XMLElement* messages = doc.NewElement("Messages");
	root->LinkEndChild(messages);

	XMLElement* welcome = doc.NewElement("Welcome");
	welcome->LinkEndChild(doc.NewText("Welcome to MyApp"));
	messages->LinkEndChild(welcome);

	XMLElement* farewell = doc.NewElement("Farewell");
	farewell->LinkEndChild(doc.NewText("Thank you for using MyApp"));
	messages->LinkEndChild(farewell);

	XMLElement* windows = doc.NewElement("Windows");
	root->LinkEndChild(windows);

	XMLElement* window = doc.NewElement("Window");
	windows->LinkEndChild(window);
	window->SetAttribute("name", "MainFrame");   // attributes
	window->SetAttribute("x", 5);                // attributes
	window->SetAttribute("y", 15);               // attributes
	window->SetAttribute("w", 400);              // attributes
	window->SetAttribute("h", 250);              // attributes

	XMLElement* connection = doc.NewElement("Connection");
	root->LinkEndChild(connection);
	connection->SetAttribute("ip", "192.168.0.1");
	connection->SetAttribute("timeout", 123.456);

	doc.SaveFile(filename); // writing document to a file
}

void dumpToStdout(const XMLAttribute* firstAttr, unsigned int indent)
{
	XMLAttribute* attr;

	for (attr = (XMLAttribute*)firstAttr; attr != 0; attr = (XMLAttribute*)attr->Next()) {
		for (int i = 0; i < indent + 1; i++) printf("    ");
		printf("%s: %s\n", attr->Name(), attr->Value());
	}
}



void dumpToStdout(const XMLNode* parent, unsigned int indent = 0)
{
	if (!parent) return;

	XMLNode* child;

	XMLDeclaration* decl;
	XMLElement* elem;
	XMLComment* comm;
	XMLAttribute* attr;
	XMLText* text;

	for (child = (XMLNode*)parent->FirstChild(); child != 0; child = (XMLNode*)child->NextSibling()) {
		for (int i = 0; i < indent + 1; i++) printf("    ");
		if (decl = child->ToDeclaration()) printf("<Declaration>");
		if (elem = child->ToElement()) printf("<Element>");
		if (comm = child->ToComment()) printf("<Comment>");
		printf(" %s\n", child->Value());
		if (elem) {
			attr = (XMLAttribute*)elem->FirstAttribute();
			if (attr) dumpToStdout(attr, indent + 1);
		}
		dumpToStdout(child, indent + 1);
	}
}

void dumpToStdout(const char* filename)
{
	XMLDocument doc;
	if (XML_NO_ERROR == doc.LoadFile(filename)) {
		printf("\n<Document> %s:\n", filename);
		dumpToStdout(&doc);
	}
	else {
		printf("Failed to open: %s\n", filename);
	}
}

int main() {
	dumpToStdout("sheet.xml");

	return 0;
}