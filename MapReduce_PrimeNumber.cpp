#include <iostream>
#include <functional>
#include "mapreduce.hpp"
using namespace std;

namespace prime_calculator
{
	//const long�� long const�� ���� �ǹ�
	//���� bool const�� const bool�� ���� �ǹ�
	bool const is_prime(const long number)
	{
		if (number > 2)
		{
			if (number % 2 == 0)
			{
				return false;
			}

			//������ ���ϴ� �Լ�
			const long n = abs(number);
			//�������� ���ϴ� sqrt�Լ��� ��ȯ���� double�̴�. �������� �Ϲ�������
			//������ ǥ������ �ʴ� ��찡 ���� ������, ���������� �������� ���ϸ� �Ҽ���
			//���ϰ� �������� ��Ȯ�� ����� ������� ���� �� �ִ�. ���� ����
			//�ε� �Ҽ��� ������ float�̳� double���� �Ǽ����� ����ϴ� ���� ����.
			//���⼭ �Ҽ��� �Ʒ��� ������ ���ؼ� long���� �ٽ� ĳ�����Ѵ�.
			const long sqrt_number = static_cast<long>(sqrt(static_cast<double>(n)));

			//�����ٱ����� �������� �ص� �Ҽ��� �Ǻ��� �� �ִ�.
			for (register long i = 3; i <= sqrt_number; i += 2)
			{
				if (n % i == 0)
				{
					return false;
				}
			}
		}
		else if(number ==0 || number ==1)
		{
			return false;
		}
		//�� ��� ������ ����ߴٸ� �� ���� �Ҽ��̴�.
		return true;
	}
	
	//������ ���� �ȿ��� ���� ������ ������ �����ϴ� Ŭ������ �����Ѵ�.
	template<typename MapTask>
	class number_source :mapreduce::detail::noncopyable
	{
	public:
		number_source(long first, long last, long step)
			:sequence_(0), first_(first), last_(last), step_(step) {}

		bool const setup_key(typename MapTask::key_type& key)
		{
			key = sequence_++;
			return (key * step_ <= last_);
		}

		bool const get_data(typename MapTask::key_type const& key,
			typename MapTask::value_type& value)
		{
			typename MapTask::value_type val;

			val.first = first_ + (key * step_);
			val.second = min(val.first + step_ - 1, last_);
			
			swap(val, value);
			return true;
		}
	private:
		long sequence_;
		const long step_;
		const long last_;
		const long first_;
	};

	//�� ������ �����ϴ� �Լ��� �����Ѵ�.
	struct map_task :public mapreduce::map_task<long, pair<long, long>>
	{
		template<typename Runtime>
		void operator()(Runtime& runtime, key_type const& /*key*/, value_type const& value) const
		{
			for (key_type loop = value.first; loop <= value.second; ++loop)
				runtime.emit_intermediate(is_prime(loop), loop);
		}
	};

	//���ེ ������ �����ϴ� �Լ��� �����Ѵ�.
	struct reduce_task :public mapreduce::reduce_task<bool, long>
	{
		template<typename Runtime,typename It>
		void operator()(Runtime& runtime, key_type const& key, It it, It ite) const
		{
			if (key)
			{
				for_each(it, ite, bind(&Runtime::emit, &runtime, true, placeholders::_1));
			}
		}
	};

	typedef mapreduce::job<prime_calculator::map_task,
		prime_calculator::reduce_task,
		mapreduce::null_combiner,
		prime_calculator::number_source<prime_calculator::map_task>> job;
}//prime_calculator ���ӽ����̽�

int main()
{
	mapreduce::specification spec;

	int prime_limit = 1000;

	//std::thread::hardware_concurrency()�� C++ ǥ�� ���̺귯������ �����ϴ� �Լ���, ���� �ý��ۿ��� �����ϴ� ���� ���� ������ ������ ���� ��ȯ�մϴ�.
	//�� �Լ��� <thread> ��� ���Ͽ� ���ǵǾ� ������, ���� ������ ���α׷��ֿ��� ������ ���� �����ϰ� ����ȭ�ϴ� �� ������ �˴ϴ�.
	int cpu_cores = max(1U, thread::hardware_concurrency());
	spec.map_tasks = cpu_cores;
	spec.reduce_tasks = cpu_cores;

	//������ ������ ���� ������ ���� ��ü
	prime_calculator::job::datasource_type datasource(0, prime_limit, prime_limit / spec.reduce_tasks);

	cout << "0���� " << prime_limit << "������ �������� �Ҽ� �Ǻ�: " << endl;
	cout << "CPU�ھ� ����: " << cpu_cores << endl;

	//�ʸ��ེ ����
	prime_calculator::job job(datasource, spec);
	mapreduce::results result;

	job.run<mapreduce::schedule_policy::cpu_parallel<prime_calculator::job>>(result);

	cout << "�� ���ེ ���� �ð�: " << result.job_runtime.count() << " sec." << endl;
	cout << "����� �Ҽ� ����: " << distance(job.begin_results(), job.end_results()) << endl;

	//��� ���
	for (auto it = job.begin_results(); it != job.end_results(); ++it)
	{
		cout << it->second << " ";
	}
	cout << endl;
	return 0;
}

//���̺귯�� ��ó
https://github.com/cdmh/mapreduce