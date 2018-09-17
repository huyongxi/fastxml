#ifndef __FASTXML_H__
#define __FASTXML_H__
#include "rapidxml.hpp"
#include <string>
#include <unordered_map>

namespace FastXml {

	using namespace rapidxml;

	class node;

	class fastxml {
	private:
		char* data = nullptr;
		uint32_t size = 0;
		xml_document<> doc;
		xml_node<>* root;
	public:
		fastxml() = default;
		bool load_xml(const std::string& filename) {
			//test
			data = new char[100];
			memcpy(data, "<config> <tag type=\"value\" attr=\"qbc\" >hyx  </tag> <t a=\"123\"/> </config>", 72);

			doc.parse<0>(data);
			root = doc.first_node();
		}
		~fastxml() {
			delete[] data;
		}

		fastxml& operator[](const char* name) {
			static xml_node<>* node;
			node = doc.first_node("name");

			return *this;
		}


	};

	class node {
	private:
		xml_node<>* _node;
		xml_node<>* visit_node;
		char* _name;
		char* _value;
		std::unordered_map<char*, char*> attr_map;
	public:
		node(xml_node<>* p) :_node(p), visit_node(nullptr){
			_name = _node->name();
			_value = _node->value();
		}
		node(const node&) = delete;
		node& operator=(const node&) = delete;
		~node() = default;

		char* name() { return _name; }
		char* value() { return _value; }

		const auto& attribute() { 
			for (auto* iter = _node->first_attribute(); iter; iter = iter->next_attribute()) {
				attr_map.insert(std::make_pair(iter->name(), iter->value()));
			}
			return attr_map; 
		}

		node& operator[](const char* s) {
			static bool first = true;
			//visit_node = _noe
			return *this;
		}
	};
}



#endif 
