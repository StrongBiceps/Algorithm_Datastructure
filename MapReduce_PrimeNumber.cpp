#include <iostream>
#include <functional>
#include "mapreduce.hpp"
using namespace std;

namespace prime_calculator
{
	//const long과 long const는 같은 의미
	//또한 bool const와 const bool은 같은 의미
	bool const is_prime(const long number)
	{
		if (number > 2)
		{
			if (number % 2 == 0)
			{
				return false;
			}

			//절댓값을 구하는 함수
			const long n = abs(number);
			//제곱근을 구하는 sqrt함수는 반환값이 double이다. 제곱근은 일반적으로
			//정수로 표현되지 않는 경우가 많기 때문에, 정수형으로 제곱근을 구하면 소수점
			//이하가 버려지고 정확한 결과가 얻어지지 않을 수 있다. 따라서 보통
			//부동 소수점 형태인 float이나 double같은 실수형을 사용하는 것이 좋다.
			//여기서 소수점 아래를 버리기 위해서 long으로 다시 캐스팅한다.
			const long sqrt_number = static_cast<long>(sqrt(static_cast<double>(n)));

			//제곱근까지만 나눗셈을 해도 소수를 판별할 수 있다.
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
		//위 모든 과정을 통과했다면 그 수는 소수이다.
		return true;
	}
	
	//지정한 범위 안에서 일정 간격의 정수를 생성하는 클래스를 정의한다.
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

	//맵 연산을 수행하는 함수를 정의한다.
	struct map_task :public mapreduce::map_task<long, pair<long, long>>
	{
		template<typename Runtime>
		void operator()(Runtime& runtime, key_type const& /*key*/, value_type const& value) const
		{
			for (key_type loop = value.first; loop <= value.second; ++loop)
				runtime.emit_intermediate(is_prime(loop), loop);
		}
	};

	//리듀스 연산을 수행하는 함수를 정의한다.
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
}//prime_calculator 네임스페이스

int main()
{
	mapreduce::specification spec;

	int prime_limit = 1000;

	//std::thread::hardware_concurrency()는 C++ 표준 라이브러리에서 제공하는 함수로, 현재 시스템에서 지원하는 동시 실행 가능한 스레드 수를 반환합니다.
	//이 함수는 <thread> 헤더 파일에 정의되어 있으며, 다중 스레드 프로그래밍에서 스레드 수를 조절하고 최적화하는 데 도움이 됩니다.
	int cpu_cores = max(1U, thread::hardware_concurrency());
	spec.map_tasks = cpu_cores;
	spec.reduce_tasks = cpu_cores;

	//지정한 범위의 정수 생성을 위한 객체
	prime_calculator::job::datasource_type datasource(0, prime_limit, prime_limit / spec.reduce_tasks);

	cout << "0부터 " << prime_limit << "사이의 정수에서 소수 판별: " << endl;
	cout << "CPU코어 개수: " << cpu_cores << endl;

	//맵리듀스 실행
	prime_calculator::job job(datasource, spec);
	mapreduce::results result;

	job.run<mapreduce::schedule_policy::cpu_parallel<prime_calculator::job>>(result);

	cout << "맵 리듀스 실행 시간: " << result.job_runtime.count() << " sec." << endl;
	cout << "검출된 소수 개수: " << distance(job.begin_results(), job.end_results()) << endl;

	//결과 출력
	for (auto it = job.begin_results(); it != job.end_results(); ++it)
	{
		cout << it->second << " ";
	}
	cout << endl;
	return 0;
}

//라이브러리 출처
https://github.com/cdmh/mapreduce