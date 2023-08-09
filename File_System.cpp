#include "FIle_System.h"

file_system::file_system()
{
	root = new node{ "/",true,nullptr,{}};
	cwd = root;
}

file_system::~file_system()
{
	delete root;
	root = nullptr;
}


node* file_system::find(const std::string& path)
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

void file_system::show_path(const std::string& path)
{
	node_ptr found=nullptr;
	if (path != "all")
	{
		found = find(path);

		if (!found)
		{
			std::cout << path << "경로가 존재하지 않습니다." << std::endl;
			return;
		}

		if (found->is_dir)
		{
			for (auto child : found->children)
			{
				std::cout << (child->is_dir ? "d " : "-") << child->name << std::endl;
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
			std::cout << (child->is_dir ? "d " : "-") << child->name << std::endl;
		}
		system("pause");
	}
}

bool file_system::add(const std::string& path, bool is_dir)
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

bool file_system::change_dir(const std::string& path)
{
	if (path == "..")
	{
		std::cout << cwd->name << std::endl;
		std::cout << "이전 디렉토리 " << cwd->parent->name << "로 이동합니다." << std::endl;
		cwd = cwd->parent;
		return true;
	}

	auto found = find(path);


	if (found && found->is_dir)
	{
		cwd = found;
		std::cout<<path << "현재 디렉토리를 " << cwd->name << "로 이동합니다." << std::endl;
		return true;
	}
	std::cout << path << "경로를 찾을 수 없습니다." << cwd->name << "로 이동합니다." << std::endl;
	return false;
}

node_ptr file_system::find_impl(node_ptr directory,const std::string& path)
{
	if (path.empty())
	{
		return directory;
	}

	auto sep = path.find('/');

	std::string current_path = sep == std::string::npos ? path : path.substr(0, sep);

	std::string rest_path = sep == std::string::npos ? "" : path.substr(sep + 1);

	auto found = find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr& child) {
		return child->name == current_path;
		});

	if (found != directory->children.end())
	{
		return find_impl(*found, rest_path);
	}

	return NULL;
}

bool file_system::add_impl(node_ptr directory, const std::string& path, bool is_dir)
{
	if (!directory->is_dir)
	{
		std::cout << directory->name << "은 파일입니다." << std::endl;
		return false;
	}
	
	auto sep = path.find('/');

	if (sep == std::string::npos)
	{
		auto found = find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr& child) {
			return child->name == path;
			});

		if (found != directory->children.end())
		{
			std::cout << directory->name << "에 이미 " << path << " 이름의 파일/디렉토리가 있습니다." << std::endl;
			return false;
		}
		//벡터 내부에 동적으로 할당된 원소들은 자동으로 메모리가 관리된다.
		directory->children.push_back(new node{ path,is_dir,directory ,{}});
		return true;
	}

	std::string next_dir = path.substr(0, sep);
	auto found = std::find_if(directory->children.begin(), directory->children.end(), [&](const node_ptr& child) {
		return child->name == next_dir && child->is_dir;
		});

	if (found != directory->children.end())
	{
		return add_impl(*found, path.substr(sep + 1), is_dir);
	}

	std::cout << directory->name << "에 " << next_dir << "이름의 디렉토리가 없습니다." << std::endl;
	return false;
}
