#ifndef __FASTXML_H__
#define __FASTXML_H__
#include "rapidxml.hpp"
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>

namespace FastXml {

	using namespace rapidxml;

	std::string strip(char* str) {
		char* b = str;
		char* e = str + strlen(str) - 1;
		int len = e - b;
		while (true) {
			if (*b == ' ' || *b == '\n' || *b == '\t') {
				++b;
			}
			if (*e == ' ' || *e == '\n' || *e == '\t') {
				--e;
			}
			if (e - b == len) {
				break;
			}
			else {
				len = e - b;
			}
		}
		return std::move(std::string(b, e + 1));
	}

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

		char* name() const { return _name; }
		std::string value() const { return std::move(strip(_value)); }

		auto attribute() const { 
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

		node operator[](const char* s) const {
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

		void for_child(const std::function<void(const node& n)>& f) const {
			for (auto iter = _node->first_node(); iter; iter = iter->next_sibling()) {
				f(node(iter));
			}
		}

		operator bool() const {
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
			memcpy(data, "<config> <tag type=\"value\" attr=\"qbc\" >   \n\t\t hyx   </tag> <t a=\"123\"/> </config>", 82);

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
