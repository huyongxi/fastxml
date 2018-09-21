#include "fastxml.h"
#include "rapidxml_print.hpp"
#include <iostream>
#include <cassert>

using namespace rapidxml;
using namespace std;

int main() {

	FastXml::fastxml f;
	f.load_xml("fastxml.vcxproj");
	auto n1 = f.root();
	cout << n1.name() << " " << n1.value() << endl;
	n1.for_child([](const FastXml::node& n) {
		cout << "name:" << n.name() << " value:" << n.value() << endl;
		for (const auto& i : n.attribute()) {
			cout << i.first << "=" << i.second << endl;
		}
	});
	system("pause");
	return 0;
}