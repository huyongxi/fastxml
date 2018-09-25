#ifndef __FASTXML_H__
#define __FASTXML_H__
#include "rapidxml.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <cstdlib>

namespace FastXml {

	using namespace rapidxml;

	std::string strip(char* str) {
		char* b = str;
		char* e = str + strlen(str) - 1;
		int len = e - b;
		while (true) {
			if (*b == ' ' || *b == '\n' || *b == '\t' || *b == '\r') {
				++b;
			}
			if (*e == ' ' || *e == '\n' || *e == '\t' || *e == '\r') {
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

	template<typename T>
	T to_number(const char* str)
	{
		if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
			return atof(str);
		}
		else if (sizeof(T) >= 8) {
			return atoll(str);
		}
		else {
			return atoi(str);
		}
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
				std::cerr << "[error:]" << "node not exist don¡¯t have attribute" << std::endl;
				return attr_map;
			}
			for (auto* iter = _node->first_attribute(); iter; iter = iter->next_attribute()) {
				attr_map.insert(std::make_pair(iter->name(), iter->value()));
			}
			return std::move(attr_map); 
		}

		const char* attribute(const char* name) const {
			if (!*this) {
				std::cerr << "[error:]" << "node not exist don¡¯t have attribute" << std::endl;
				return "";
			}
			auto attr = _node->first_attribute(name);
			if (!attr) {
				std::cerr << "[error:]" << _name << " don¡¯t have attribute " << name << std::endl;
				return "";
			}
			return attr->value();
		}

		node operator[](const char* s) const {
			if (!*this) {
				std::cerr << "[error:]" << "operator[]: node not exist!" << std::endl;
				return node(nullptr);
			}
			xml_node<>* child = _node->first_node(s);
			if (child) {
				return node(child);
			}
			else {
				std::cerr << "[error:]" << _name << " don¡¯t have child node " << s << std::endl;
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
		std::size_t size = 0;
		bool valid = false;
		xml_document<> doc;
		xml_node<>* _root;
		
	public:
		fastxml() = default;
		bool load_xml(const std::string& filename) {
			std::ifstream ifile;
			ifile.open(filename,std::ios::binary);
			if (!ifile) {
				std::cerr << "[error:]" << "open file failed!" << std::endl;
				return false;
			}

			std::filebuf* buf = ifile.rdbuf();
			size = buf->pubseekoff(0, ifile.end, ifile.in);
			buf->pubseekpos(0, ifile.in);
			data = new char[size+1];
			buf->sgetn(data, size);
			data[size] = 0;
			ifile.close();

			doc.parse<0>(data);
			_root = doc.first_node();
			valid = true;
			return true;
		}
		~fastxml() {
			delete[] data;
		}
		node operator[](const char* name) const {
			return node(doc.first_node(name));
		}

		node root() const {
			return node(_root);
		}

		operator bool() const {
			return valid;
		}
	};
}



#endif 
