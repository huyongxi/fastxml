#include "fastxml.h"
#include "rapidxml_print.hpp"
#include <iostream>
#include <cassert>

using namespace rapidxml;
using namespace std;

char xml[] = "<config> <tag type=\"value\" attr=\"qbc\" >hyx</tag> <t a=\"123\"/> </config>";

int main() {

	xml_document<> doc;
	doc.parse<0>(xml);
	cout << doc;
	
	/*for (xml_node<>* i = doc.first_node(0); i; i = i->first_node(0)) {
		cout << i->name() << endl;
	}*/

	xml_node<>* node1 = doc.first_node("config");
	xml_node<>* node2 = node1->first_node("tag");
	assert(node2);
	cout << node2->name() << endl;
	cout << node2->value() << node2->value_size() << endl;
	xml_attribute<>* attr = node2->first_attribute("type");
	cout << attr->name() << attr->value() << endl;
	system("pause");
	return 0;
}