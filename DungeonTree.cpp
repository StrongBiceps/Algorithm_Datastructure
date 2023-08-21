#include "pch.h"
#include "DungeonTree.h"

DungeonTree::DungeonTree()
{
	root = new Room{ "/",true,nullptr,{} };
	cwd = root;
}

DungeonTree::~DungeonTree()
{
	for(int i = 0; i < root->children.size(); ++i)
	{
		delete root->children[i];
	}

	root->children.resize(0);

	delete root;
	root = nullptr;
}


Room* DungeonTree::find(const std::string& path)
{
	if (path[0] == '/')
	{
		return find_impl(root, path.substr(1));
	}
	else
	{
		return find_impl(cwd, path);
	}
}

void DungeonTree::show_path(const std::string& path)
{
	Room_ptr found = nullptr;
	if (path != "all")
	{
		found = find(path);

		if (!found)
		{
			std::cout << path << "��ΰ� �������� �ʽ��ϴ�." << std::endl;
			return;
		}

		if (found->is_Dungeon)
		{
			for (auto child : found->children)
			{
				std::cout << (child->is_Dungeon ? "d " : "-") << child->name << std::endl;
			}
			system("pause");
		}
		else
		{
			std::cout << "-" << found->name << std::endl;
		}
	}
	else
	{
		for (auto child : cwd->children)
		{
			std::cout << (child->is_Dungeon ? "d " : "-") << child->name << std::endl;
		}
		system("pause");
	}
}

bool DungeonTree::add(const std::string& path, bool is_dir)
{
	if (path[0] == '/')
	{
		return add_impl(root, path.substr(1), is_dir);
	}
	else
	{
		return add_impl(cwd, path, is_dir);
	}
}

bool DungeonTree::change_dir(const std::string& path)
{
	if (path == "..")
	{
		std::cout << cwd->name << std::endl;
		if(cwd->parent->name =="/")
		{
			std::cout << "������ �Ա��� �̵��մϴ�." << std::endl;
		}
		else
		{
			std::cout << "���� ���� " << cwd->parent->name << "�� �̵��մϴ�." << std::endl;
		}

		cwd = cwd->parent;
		Sleep(500);
		return true;
	}

	auto found = find(path);


	if (found && found->is_Dungeon)
	{
		cwd = found;
		std::cout << "���� ������ " << cwd->name << "�� �̵��մϴ�." << std::endl;
		Sleep(500);
		return true;
	}
	std::cout << path << "��θ� ã�� �� �����ϴ�." << cwd->name << "�� �̵��մϴ�." << std::endl;
	Sleep(500);
	return false;
}

Room_ptr DungeonTree::find_impl(Room_ptr directory, const std::string& path)
{
	if (path.empty())
	{
		return directory;
	}

	auto sep = path.find('/');

	std::string current_path = sep == std::string::npos ? path : path.substr(0, sep);

	std::string rest_path = sep == std::string::npos ? "" : path.substr(sep + 1);

	auto found = find_if(directory->children.begin(), directory->children.end(), [&](const Room_ptr& child) {
		return child->name == current_path;
		});

	if (found != directory->children.end())
	{
		return find_impl(*found, rest_path);
	}

	return NULL;
}

bool DungeonTree::add_impl(Room_ptr directory, const std::string& path, bool is_dir)
{
	if (!directory->is_Dungeon)
	{
		std::cout << directory->name << "�� ������Ʈ�Դϴ�." << std::endl;
		return false;
	}

	auto sep = path.find('/');

	if (sep == std::string::npos)
	{
		auto found = find_if(directory->children.begin(), directory->children.end(), [&](const Room_ptr& child) {
			return child->name == path;
			});

		if (found != directory->children.end())
		{
			std::cout << directory->name << "�� �̹� " << path << " �̸��� ����/������Ʈ�� �ֽ��ϴ�." << std::endl;
			return false;
		}
		directory->children.push_back(new Room{ path,is_dir,directory ,{} });
		return true;
	}

	std::string next_dir = path.substr(0, sep);
	auto found = std::find_if(directory->children.begin(), directory->children.end(), [&](const Room_ptr& child) {
		return child->name == next_dir && child->is_Dungeon;
		});

	if (found != directory->children.end())
	{
		return add_impl(*found, path.substr(sep + 1), is_dir);
	}

	std::cout << directory->name << "�� " << next_dir << "�̸��� ���� �����ϴ�." << std::endl;
	return false;
}

Room::~Room()
{
	for (int i = 0; i < children.size(); ++i)
	{
		delete children[i];
	}
}
