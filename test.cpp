#include "fastxml.h"
#include "rapidxml_print.hpp"
#include <iostream>
#include <cassert>

using namespace rapidxml;
using namespace std;

int main() {

	cout << FastXml::to_number<double>("3435.56") << endl;

	{
		FastXml::fastxml xml;
		xml.load_xml("SkillC1fg.xml");
		if (!xml) {
			return -1;
		}
		auto cfg = xml["SkillCfg"];
		if (cfg) {
			cfg.for_child([](const FastXml::node& n) {
				cout << "un32ID " << n.attribute("un32ID") << endl;
				n.for_child([](const FastXml::node& n) {
					cout << n.name() << " " << n.value() << endl;
				});
			});
		}
	}
	system("pause");
	return 0;
}