#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>

class node
{
public:
	std::string name;
	bool is_dir;
	node* parent;
	std::vector<node*> children;
	/*
	*Inline function section
	*/
	size_t Getsize()
	{
		return sizeof(*this);
	}
	node* Getparent()
	{
		return parent;
	}
};

using node_ptr = node*;

class file_system
{
private:
	node_ptr root;
	node_ptr cwd;
public:
	file_system();
	~file_system();
	node_ptr find(const std::string& path);
	void show_path(const std::string& path);
	bool add(const std::string& path, bool is_dir);
	bool change_dir(const std::string& path);

	/*
	*Inline function section
	*/
	node_ptr GetRoot()
	{
		return root;
	}
	void SetRoot(const node_ptr& node)
	{
		root = node;
	}
	node_ptr Getcwd()
	{
		return cwd;
	}
	void Reset_cwd()
	{
		cwd = root;
	}
private:
	node_ptr find_impl(node_ptr directory,const std::string& path);
	bool add_impl(node_ptr directory, const std::string& path, bool is_dir);
};