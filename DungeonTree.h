#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>

class Room
{
public:
	std::string name;
	bool is_Dungeon;
	Room* parent;
	std::vector<Room*> children;
	bool bIsCleared=false;
	/*
	*Inline function section
	*/
	size_t Getsize()
	{
		return sizeof(*this);
	}
	Room* Getparent()
	{
		return parent;
	}
	~Room();
	void SetCleared(bool _bCleared)
	{
		bIsCleared = _bCleared;
	}
	bool GetCleared() const
	{
		return bIsCleared;
	}
};

using Room_ptr = Room*;

class DungeonTree
{
private:
	Room_ptr root;
	Room_ptr cwd;
public:
	DungeonTree();
	~DungeonTree();
	Room_ptr find(const std::string& path);
	void show_path(const std::string& path);
	bool add(const std::string& path, bool is_dir);
	bool change_dir(const std::string& path);

	/*
	*Inline function section
	*/
	Room_ptr GetRoot()
	{
		return root;
	}
	void SetRoot(const Room_ptr& node)
	{
		if (nullptr != root)
			delete root;
		root = node;
	}
	Room_ptr Getcwd()
	{
		return cwd;
	}
	void Reset_cwd()
	{
		cwd = root;
	}
private:
	Room_ptr find_impl(Room_ptr directory, const std::string& path);
	bool add_impl(Room_ptr directory, const std::string& path, bool is_dir);
};
