#include <limits>
#include "pch.h"
#include "DungeonGenerator.h"

DungeonGenerator::DungeonGenerator()
{
	DTree = new DungeonTree();
}

DungeonGenerator::~DungeonGenerator()
{
	delete DTree;
	DTree = nullptr;
}

Room_ptr DungeonGenerator::find_interface(const std::string& path)
{
	return DTree->find(path);
}

void DungeonGenerator::show_path_interface(const std::string& path)
{
	if (path == "all")
	{
		if (DTree->GetRoot() == DTree->Getcwd())
		{
			DTree->show_path("/");
		}
		else
		{
			DTree->show_path(path);
		}
	}
	else
	{
		DTree->show_path(path);
	}
}

bool DungeonGenerator::add_interface(const std::string& path, bool is_dir)
{
	return DTree->add(path, is_dir);
}

bool DungeonGenerator::change_dir_interface(const std::string& path)
{
	return DTree->change_dir(path);
}

bool DungeonGenerator::Initiate()
{
	std::cout << "던전에 입장한 상태입니다." << std::endl;

	//load_bin();
	//DTree->Reset_cwd();
	while (true)
	{
		System_Helper();

		std::string sInput = "";

		if(GetDTree()->Getcwd() == GetDTree()->GetRoot())
		{
			printf("Select Menu \t현재 위치[%s]\n", "던전의 입구");
		}
		else
		{
			printf("Select Menu \t현재 위치[%s]\n", GetDTree()->Getcwd()->name.c_str());
		}
		//std::cout << "Select Menu" << std::endl;
	

		//std::cout << "1.던전 찾기 \t2.던전 이동(2번 누른 뒤 .. -> 뒤로 가기) \t3.길 보기(all 입력) \t4.퇴장" << std::endl;
		printf("1.던전 찾기 \t2.던전 이동(2번 누른 뒤 .. -> 뒤로 가기) \t3.길 보기(all 입력) \t4.퇴장\n");

		rewind(stdin);
		rewind(stdout);
		fflush(stdout);
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

		std::getline(std::cin, sInput, '\n');

		if (sInput.size() > 1)
		{
			std::cout << "Invalid Input Abort called" << std::endl;
			return false;
			//continue;
		}

		int iInput = stoi(sInput);

		switch (stoi(sInput))
		{
		case 1:
			//add_called();
			//find_called();
			printf("준비중입니다.\n");
			break;
		case 2:
			change_called();
			return false;
			break;
		case 3:
			show_called();
			break;
		default:
			break;
		}

		if (iInput == 4 || (iInput > 4 && iInput < 1))
		{
			std::cout << "던전에서 퇴장합니다." << std::endl;
			Sleep(500);
			return true;
			//break;
		}
	}
	//save_bin();
}

void DungeonGenerator::add_called()
{
	std::string path = "";
	int iInput = 0;

	std::cout << "please input the Dungeon or Object \t abort->Input ." << std::endl;

	std::getline(std::cin, path);

	if (path == ".")
	{
		std::cout << "aborted" << std::endl;
		Sleep(500);
		return;
	}

	std::cout << std::endl << "is Dungeon? 1-true 0-false 2:abort" << std::endl;
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

void DungeonGenerator::find_called()
{
	std::string path = "";

	std::cout << "please input the Dungeon or Object \t abort->input ." << std::endl;

	std::getline(std::cin, path, '\n');

	if (path == ".")
	{
		std::cout << "aborted" << std::endl;
		Sleep(500);
		return;
	}

	if (find_interface(path) == NULL)
	{
		std::cout << path << "던전을 찾지 못했습니다. " << std::endl;
	}
	else
	{
		std::cout << path << "던전을 찾았습니다. " << std::endl;
	}
}

void DungeonGenerator::change_called()
{
	std::string path = "";

	std::cout << "please input the Dungeon \t abort->Input ." << std::endl;
	std::getline(std::cin, path, '\n');

	if (path == ".")
	{
		std::cout << "aborted" << std::endl;
		Sleep(500);
	}
	change_dir_interface(path);
}

void DungeonGenerator::show_called()
{
	std::string path = "";

	std::cout << "please input the Dungeon \t abort->Input ." << std::endl;
	std::getline(std::cin, path, '\n');

	if (path == ".")
	{
		std::cout << "aborted" << std::endl;
		Sleep(500);
		return;
	}

	show_path_interface(path);
}

void DungeonGenerator::System_Helper()
{
	Sleep(1000);
	system("cls");
}

void DungeonGenerator::save_data(const Room* n, std::ofstream& outfile)
{
	// 문자열 크기 저장
	size_t name_size = n->name.size();
	outfile.write(reinterpret_cast<const char*>(&name_size), sizeof(name_size));

	// 문자열 저장
	outfile.write(n->name.c_str(), name_size);

	// is_dir 저장
	outfile.write(reinterpret_cast<const char*>(&n->is_Dungeon), sizeof(n->is_Dungeon));

	// children 크기 저장
	size_t children_size = n->children.size();
	outfile.write(reinterpret_cast<const char*>(&children_size), sizeof(children_size));

	// children 저장 (재귀 호출)
	for (const Room* child : n->children) {
		save_data(child, outfile);
	}
}

Room* DungeonGenerator::load_data(std::ifstream& infile)
{
	//n이 저장하고 있는 주소는 힙 공간의 주소이다.
	//n이 파괴될 때 힙 공간의 데이터는 해제하지 않기 때문에
	//지역 변수인 n이 가지고 있는 힙 주소를 그대로 push해도 상관 없다.
	//힙 주소는 사용자가 해제하기 전까지는 유효하다.
	Room* n = new Room;

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
	infile.read(reinterpret_cast<char*>(&n->is_Dungeon), sizeof(n->is_Dungeon));

	// children 크기 불러오기
	size_t children_size;
	infile.read(reinterpret_cast<char*>(&children_size), sizeof(children_size));

	// children 불러오기 (재귀 호출)
	for (size_t i = 0; i < children_size; ++i) {
		Room* child = load_data(infile);
		n->children.push_back(child);
		child->parent = n;
	}

	return n;
}

void DungeonGenerator::save_bin()
{
	// 이진 파일로 저장
	std::ofstream outfile("nodes.bin", std::ios::binary);
	if (outfile.is_open()) {
		save_data(DTree->GetRoot(), outfile);
		outfile.close();
		std::cout << "Nodes saved to binary file." << std::endl;
	}
	else {
		std::cerr << "Failed to open file for writing." << std::endl;
	}
}

void DungeonGenerator::load_bin()
{
	// 이진 파일로부터 노드 불러오기
	std::ifstream infile("nodes.bin", std::ios::binary);
	if (infile.is_open()) {
		DTree->SetRoot(load_data(infile));
		infile.close();
	}
	else {
		std::cerr << "Failed to open file for reading." << std::endl;
	}
}
