#ifndef __FASTXML_H__
#define __FASTXML_H__
#include "rapidxml.hpp"
#include <string>
#include <iostream>
#include <unordered_map>

namespace FastXml {

	using namespace rapidxml;

	class node {
	private:
		xml_node<>* _node;
		char* _name = nullptr;
		char* _value = nullptr;
		bool valid = false;
	public:
		node(xml_node<>* p) :_node(p){
			if (_node != nullptr) {
				valid = true;
				_name = _node->name();
				_value = _node->value();
			}
		}

		node& operator=(const node&) = delete;

		char* name() { return _name; }
		char* value() { return _value; }

		auto attribute() { 
			std::unordered_map<char*, char*> attr_map;
			if (!*this) {
				std::cerr << "node not exist don¡¯t have attribute" << std::endl;
				return attr_map;
			}
			for (auto* iter = _node->first_attribute(); iter; iter = iter->next_attribute()) {
				attr_map.insert(std::make_pair(iter->name(), iter->value()));
			}
			return std::move(attr_map); 
		}

		node operator[](const char* s) {
			if (!*this) {
				std::cerr << "operator[]: node not exist!" << std::endl;
				return node(nullptr);
			}
			xml_node<>* child = _node->first_node(s);
			if (child) {
				return node(child);
			}
			else {
				std::cerr << _name << " don¡¯t have child node " << s << std::endl;
				return node(nullptr);
			}
		}

		operator bool() {
			return valid;
		}
	};

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
			memcpy(data, "<config> <tag type=\"value\" attr=\"qbc\" >hyx  </tag> <t a=\"123\"/> </config>", 74);

			doc.parse<0>(data);
			root = doc.first_node();
			return true;
		}
		~fastxml() {
			delete[] data;
		}

		node operator[](const char* name) {
			return node(doc.first_node(name));
		}


	};
}



#endif 
