#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "FIle_System.h"
#include <Windows.h>

class GameController
{
private:
	file_system* FSystem;
public:
	GameController();
	~GameController();

	/*
	* interface_functions
	*/
	node_ptr find_interface(const std::string& path);
	void show_path_interface(const std::string& path);
	bool add_interface(const std::string& path, bool is_dir);
	bool change_dir_interface(const std::string& path);

	/*
	*Game Control function 
	*/
	void GameStart();
	void add_called();
	void find_called();
	void change_called();
	void show_called();
	void System_Helper();
	void save_data(const node* n, std::ofstream& outfile);
	node* load_data(std::ifstream& infile);
	void save_bin();
	void load_bin();
};
