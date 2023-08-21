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
	std::cout << "������ ������ �����Դϴ�." << std::endl;

	//load_bin();
	//DTree->Reset_cwd();
	while (true)
	{
		System_Helper();

		std::string sInput = "";

		if(GetDTree()->Getcwd() == GetDTree()->GetRoot())
		{
			printf("Select Menu \t���� ��ġ[%s]\n", "������ �Ա�");
		}
		else
		{
			printf("Select Menu \t���� ��ġ[%s]\n", GetDTree()->Getcwd()->name.c_str());
		}
		//std::cout << "Select Menu" << std::endl;
	

		//std::cout << "1.���� ã�� \t2.���� �̵�(2�� ���� �� .. -> �ڷ� ����) \t3.�� ����(all �Է�) \t4.����" << std::endl;
		printf("1.���� ã�� \t2.���� �̵�(2�� ���� �� .. -> �ڷ� ����) \t3.�� ����(all �Է�) \t4.����\n");

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
			printf("�غ����Դϴ�.\n");
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
			std::cout << "�������� �����մϴ�." << std::endl;
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
	//cin�� ����� �� ���๮�ڰ� ���ۿ� ���������Ƿ� ���� getline�Լ����� ������ ���� �� �ִ�.
	//���� ���۸� ���� �Լ��� ȣ���Ѵ�.
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
		std::cout << path << "������ ã�� ���߽��ϴ�. " << std::endl;
	}
	else
	{
		std::cout << path << "������ ã�ҽ��ϴ�. " << std::endl;
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
	// ���ڿ� ũ�� ����
	size_t name_size = n->name.size();
	outfile.write(reinterpret_cast<const char*>(&name_size), sizeof(name_size));

	// ���ڿ� ����
	outfile.write(n->name.c_str(), name_size);

	// is_dir ����
	outfile.write(reinterpret_cast<const char*>(&n->is_Dungeon), sizeof(n->is_Dungeon));

	// children ũ�� ����
	size_t children_size = n->children.size();
	outfile.write(reinterpret_cast<const char*>(&children_size), sizeof(children_size));

	// children ���� (��� ȣ��)
	for (const Room* child : n->children) {
		save_data(child, outfile);
	}
}

Room* DungeonGenerator::load_data(std::ifstream& infile)
{
	//n�� �����ϰ� �ִ� �ּҴ� �� ������ �ּ��̴�.
	//n�� �ı��� �� �� ������ �����ʹ� �������� �ʱ� ������
	//���� ������ n�� ������ �ִ� �� �ּҸ� �״�� push�ص� ��� ����.
	//�� �ּҴ� ����ڰ� �����ϱ� �������� ��ȿ�ϴ�.
	Room* n = new Room;

	// ���ڿ� ũ�� �ҷ�����
	size_t name_size;
	infile.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));

	// ���ڿ� �ҷ�����
	char* name_buffer = new char[name_size + 1];
	infile.read(name_buffer, name_size);
	name_buffer[name_size] = '\0';
	n->name = name_buffer;
	delete[] name_buffer;

	// is_dir �ҷ�����
	infile.read(reinterpret_cast<char*>(&n->is_Dungeon), sizeof(n->is_Dungeon));

	// children ũ�� �ҷ�����
	size_t children_size;
	infile.read(reinterpret_cast<char*>(&children_size), sizeof(children_size));

	// children �ҷ����� (��� ȣ��)
	for (size_t i = 0; i < children_size; ++i) {
		Room* child = load_data(infile);
		n->children.push_back(child);
		child->parent = n;
	}

	return n;
}

void DungeonGenerator::save_bin()
{
	// ���� ���Ϸ� ����
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
	// ���� ���Ϸκ��� ��� �ҷ�����
	std::ifstream infile("nodes.bin", std::ios::binary);
	if (infile.is_open()) {
		DTree->SetRoot(load_data(infile));
		infile.close();
	}
	else {
		std::cerr << "Failed to open file for reading." << std::endl;
	}
}
