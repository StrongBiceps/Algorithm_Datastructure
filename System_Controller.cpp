#include "System_Controller.h"

GameController::GameController()
{
	FSystem = new file_system();
}

GameController::~GameController()
{
	delete FSystem;
	FSystem = nullptr;
}

node_ptr GameController::find_interface(const std::string& path)
{
	return FSystem->find(path);
}

void GameController::show_path_interface(const std::string& path)
{
	if (path == "all")
	{
		if (FSystem->GetRoot() == FSystem->Getcwd())
		{
			FSystem->show_path("/");
		}
		else
		{
			FSystem->show_path(path);
		}
	}
	else
	{
		FSystem->show_path(path);
	}
}

bool GameController::add_interface(const std::string& path, bool is_dir)
{
	return FSystem->add(path, is_dir);
}

bool GameController::change_dir_interface(const std::string& path)
{
	return FSystem->change_dir(path);
}

void GameController::GameStart()
{
	std::cout << "Linux-FileSystem Initiate." << std::endl;

	load_bin();
	FSystem->Reset_cwd();
	while (true)
	{
		System_Helper();

		std::string sInput = "";

		std::cout << "Select Menu" << std::endl;

		std::cout << "1. add file or directory \t2. find directory or file \t3.change directory \t4.show path \t 5.Exit" << std::endl;

		std::getline(std::cin, sInput,'\n');

		if (sInput.size() > 1)
		{
			std::cout << "Invalid Input Abort called" << std::endl;
			continue;
		}

		int iInput = stoi(sInput);

		switch (stoi(sInput))
		{
		case 1:
			add_called();
			break;
		case 2:
			find_called();
			break;
		case 3:
			change_called();
			break;
		case 4:
			show_called();
			break;
		default:
			break;
		}

		if (iInput == 5 || (iInput >5 && iInput<1))
		{
			std::cout << "Exit called" << std::endl;
			Sleep(500);
			break;
		}
	}
	save_bin();
}

void GameController::add_called()
{
	std::string path = "";
	int iInput = 0;

	std::cout << "please input the directory or file \t abort->Input ." << std::endl;

	std::getline(std::cin, path);

	if (path == ".")
	{
		std::cout << "aborted" << std::endl;
		Sleep(500);
		return;
	}

	std::cout << std::endl << "is dir? 1-true 0-false 2:abort" << std::endl;
	std::cin >> iInput;
	//cin을 사용할 때 개행문자가 버퍼에 남아있으므로 다음 getline함수에서 문제가 생길 수 있다.
	//따라서 버퍼를 비우는 함수를 호출한다.
	std::cin.ignore();

	if (iInput == 2)
	{
		std::cout << "aborted" << std::endl;
		Sleep(500);
		return;
	}
	add_interface(path, iInput);
}

void GameController::find_called()
{
	std::string path = "";

	std::cout << "please input the directory or file \t abort->input ." << std::endl;

	std::getline(std::cin, path,'\n');

	if (path == ".")
	{
		std::cout << "aborted" << std::endl;
		Sleep(500);
		return;
	}

	if (find_interface(path) == NULL)
	{
		std::cout << path << "파일을 찾지 못했습니다. " << std::endl;
	}
	else
	{
		std::cout << path << "파일을 찾았습니다. " << std::endl;
	}
}

void GameController::change_called()
{
	std::string path = "";

	std::cout << "please input the directory \t abort->Input ." << std::endl;
	std::getline(std::cin, path, '\n');

	if (path == ".")
	{
		std::cout << "aborted" << std::endl;
		Sleep(500);
	}
	change_dir_interface(path);
}

void GameController::show_called()
{
	std::string path = "";

	std::cout << "please input the directory \t abort->Input ." << std::endl;
	std::getline(std::cin, path, '\n');

	if (path == ".")
	{
		std::cout << "aborted" << std::endl;
		Sleep(500);
		return;
	}

	show_path_interface(path);
}

void GameController::System_Helper()
{
	Sleep(1000);
	system("cls");
}

void GameController::save_data(const node* n, std::ofstream& outfile)
{
	// 문자열 크기 저장
	size_t name_size = n->name.size();
	outfile.write(reinterpret_cast<const char*>(&name_size), sizeof(name_size));

	// 문자열 저장
	outfile.write(n->name.c_str(), name_size);

	// is_dir 저장
	outfile.write(reinterpret_cast<const char*>(&n->is_dir), sizeof(n->is_dir));

	// children 크기 저장
	size_t children_size = n->children.size();
	outfile.write(reinterpret_cast<const char*>(&children_size), sizeof(children_size));

	// children 저장 (재귀 호출)
	for (const node* child : n->children) {
		save_data(child, outfile);
	}
}

node* GameController::load_data(std::ifstream& infile)
{
	//n이 저장하고 있는 주소는 힙 공간의 주소이다.
	//n이 파괴될 때 힙 공간의 데이터는 해제하지 않기 때문에
	//지역 변수인 n이 가지고 있는 힙 주소를 그대로 push해도 상관 없다.
	//힙 주소는 사용자가 해제하기 전까지는 유효하다.
	node* n = new node();

	// 문자열 크기 불러오기
	size_t name_size;
	infile.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));

	// 문자열 불러오기
	char* name_buffer = new char[name_size + 1];
	infile.read(name_buffer, name_size);
	name_buffer[name_size] = '\0';
	n->name = name_buffer;
	delete[] name_buffer;

	// is_dir 불러오기
	infile.read(reinterpret_cast<char*>(&n->is_dir), sizeof(n->is_dir));

	// children 크기 불러오기
	size_t children_size;
	infile.read(reinterpret_cast<char*>(&children_size), sizeof(children_size));

	// children 불러오기 (재귀 호출)
	for (size_t i = 0; i < children_size; ++i) {
		node* child = load_data(infile);
		n->children.push_back(child);
		child->parent = n;
	}

	return n;
}

void GameController::save_bin()
{
	// 이진 파일로 저장
	std::ofstream outfile("nodes.bin", std::ios::binary);
	if (outfile.is_open()) {
		save_data(FSystem->GetRoot(), outfile);
		outfile.close();
		std::cout << "Nodes saved to binary file." << std::endl;
	}
	else {
		std::cerr << "Failed to open file for writing." << std::endl;
	}
}

void GameController::load_bin()
{
	// 이진 파일로부터 노드 불러오기
	std::ifstream infile("nodes.bin", std::ios::binary);
	if (infile.is_open()) {
		FSystem->SetRoot(load_data(infile));
		infile.close();
	}
	else {
		std::cerr << "Failed to open file for reading." << std::endl;
	}
}
