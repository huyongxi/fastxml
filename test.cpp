#include "fastxml.h"
#include "rapidxml_print.hpp"
#include <iostream>
#include <cassert>

using namespace rapidxml;
using namespace std;

int main() {

	{
		FastXml::fastxml xml;
		xml.load_xml("SkillCfg.xml");
		if (!xml) {
			return -1;
		}
		auto cfg = xml["SkillCfg"];
		if (cfg) {
			cfg.for_child([](const FastXml::node& n) {
				auto s = n.attribute("un32ID");
				cout << "un32ID " << (s ? s : "") << endl;
				n.for_child([](const FastXml::node& n) {
					cout << n.name() << " " << n.value() << endl;
				});
			});
		}
	}

	system("pause");
	return 0;
}