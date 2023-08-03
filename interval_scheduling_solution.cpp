#include <list>
#include <algorithm>
#include <iostream>
#include <random>

// 모든 작업은 ID와 <시작 시간, 종료 시간> 쌍으로 표현됨
struct Task
{
public:
	unsigned ID;
	unsigned start_time;
	unsigned end_time;
};

auto initialize_tasks(int num_tasks, int max_end_time)
{
	//작업의 시작 시간과 종료 시간의 난수를 생성한다.
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, max_end_time);

	std::list<Task> tasks;

	for (unsigned i = 0; i < num_tasks; i++)
	{
		auto start_time = uniform_dist(rand);
		auto end_time = uniform_dist(rand);

		//만약 시작 시간과 종료 시간이 같다면 종료 시간의 값을 하나 올린다.
		if (start_time == end_time) end_time++;
		//시작 시간이 종료 시간보다 크다면 둘의 값을 바꾼다.
		if (start_time > end_time) std::swap(start_time, end_time);

		//ID를 순차적으로 부여하며 push 작업을 진행한다.
		//ID는 0부터 시작한다.
		tasks.push_back({ i + 1, start_time, end_time });
	}

	return tasks;
}

auto job_scheduling(std::list<Task> tasks)
{
	// 작업 종료 시간을 기준으로 정렬
	// 람다함수를 정의하여 오름차순 정렬
	//종료 시간이 가장 짧은 것이 begin으로 간다.
	tasks.sort([](const auto& lhs, const auto& rhs) {
		return lhs.end_time < rhs.end_time;
		});

	//순차적으로 task를 순회하며 겹치는 작업들을 제거
	for (auto curr_task = tasks.begin(); curr_task != tasks.end(); curr_task++)
	{
		auto next_task = std::next(curr_task, 1);

		// 현재 작업과 시간이 겹치는 작업은 제거
		//현재 작업의 종료 시간보다 앞에서 시작하는 작업을 모두 제거
		while (next_task != tasks.end() &&
			next_task->start_time < curr_task->end_time)
		{
			next_task = tasks.erase(next_task);
		}
	}

	return tasks;
}

void print(std::list<Task>& tasks, int max_end_time)
{
	for (auto t : tasks) {
		std::cout << "[" << t.ID << "] " << t.start_time << " -> " << t.end_time << "\t|";

		int i = 0;
		//시작 시간까지는 공백을 출력하고
		for (; i < t.start_time; i++) std::cout << " ";
		//시작 시간부터 종료 시간까지는 * 출력
		for (; i < t.end_time; i++) std::cout << "*";
		//나머지 시간들은 공백으로 출력
		for (; i < max_end_time; i++) std::cout << " ";
		std::cout << "|" << std::endl;
	}
}

int main()
{
	int num_tasks = 10;
	int max_end_time = 20;

	auto tasks = initialize_tasks(num_tasks, max_end_time);
	std::cout << "[전체 작업]" << std::endl;
	print(tasks, max_end_time);

	auto scheduled_tasks = job_scheduling(tasks);
	std::cout << "\n[스케쥴 조정한 작업]" << std::endl;
	print(scheduled_tasks, max_end_time);
}