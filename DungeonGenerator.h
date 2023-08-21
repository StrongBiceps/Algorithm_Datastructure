#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "DungeonTree.h"

class DungeonGenerator
{
private:
	DungeonTree* DTree;
public:
	DungeonGenerator();
	~DungeonGenerator();

	/*
	* interface_functions
	*/
	Room_ptr find_interface(const std::string& path);
	void show_path_interface(const std::string& path);
	bool add_interface(const std::string& path, bool is_dir);
	bool change_dir_interface(const std::string& path);

	/*
	*Game Control function
	*/
	bool Initiate();
	void add_called();
	void find_called();
	void change_called();
	void show_called();
	void System_Helper();
	void save_data(const Room* n, std::ofstream& outfile);
	Room* load_data(std::ifstream& infile);
	void save_bin();
	void load_bin();
	DungeonTree* GetDTree()
	{
		return DTree;
	}
};
