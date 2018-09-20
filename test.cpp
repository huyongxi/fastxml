#include "fastxml.h"
#include "rapidxml_print.hpp"
#include <iostream>
#include <cassert>

using namespace rapidxml;
using namespace std;

char xml[] = "<config> <tag type=\"value\" attr=\"qbc\" >hyx</tag> <t a=\"123\"/> </config>";

int main() {

	//xml_document<> doc;
	//doc.parse<0>(xml);
	//cout << doc;
	//
	///*for (xml_node<>* i = doc.first_node(0); i; i = i->first_node(0)) {
	//	cout << i->name() << endl;
	//}*/

	//xml_node<>* node1 = doc.first_node("config");
	//cout << node1->name() << ":" << node1->value() << endl;
	//xml_node<>* node2 = node1->first_node("tag");
	//assert(node2);
	//cout << node2->name() << endl;
	//cout << node2->value() << node2->value_size() << endl;
	//xml_attribute<>* attr = node2->first_attribute("type");
	//cout << attr->name() << attr->value() << endl;


	FastXml::fastxml f;
	f.load_xml("null");
	auto n1 = f["config"];
	auto m1 = n1.attribute();

	auto n2 = f["tag"];
	auto m2 = n2.attribute();

	auto n3 = n1["tag"];
	auto m3 = n3.attribute();
	n1.for_child([](const FastXml::node& n) {
		cout << "name:" << n.name() << " value:" << n.value() << endl;
		for (const auto& i : n.attribute()) {
			cout << i.first << "=" << i.second << endl;
		}
	});

	cout << n3.attribute("type") << endl;

	system("pause");
	return 0;
}