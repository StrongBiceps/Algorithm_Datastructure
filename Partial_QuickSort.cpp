/*
* 초기 조건 5 1 3 9 7 6
k=3

partial_quick_sort 재귀 순서

1. partition 호출 ->5 1 3 9 7 6  -> partial_quick_sort (5 1 3) 호출  
                          p

2. partition 호출 -> 3 1 5 -> partial_quick_sort(3 1) 호출
	                     p

3. partition 호출 -> 1 3 -> partial_quick_sort(1)호출
                       p

4. distance가 0이므로 partial_quick_sort(1)에 대한 작업 종료

5. 3번의 distance<k if문 실행 -> distance가 0이므로 작업 종료 ->3번 재귀 종료

6. 2번의 distance<k if문 실행 -> distance가 0이므로 작업 종료 -> 2번 재귀 종료

7. 1번의 distance<k if문 실행 -> distance가 k랑 같은 3이므로 if문 실행 안됨 -> 1번 재귀 종료

결과적으로  1 3 5 9 7 6
3개의 원소만 정렬되었음

만약 k가 4라면 1 3 5 6 7 9가 되는데 이 것은 전부 정렬된 상태이다. 즉 피봇과 k의 관계에 따라서 무조건 정해진
k개수만 정렬되는 것은 아닌듯 하다. 거의 비슷한 갯수가 정렬되는 것은 확실하다. k가 2라도 1 3 5 9 7 6으로 k가
3일때와 같다.

k가 4라면, 9 7 6 부분 시퀀스도 정렬해야 한다. 그런데 이 시퀀스에서 9만 정렬할 수는 없고 partition 과정에서
6 7 9가 되어 버려 나머지 시퀀스도 모두 정렬된 상태가 된다. 따라서 시퀀스 상태에 따라 정확히 k번째 까지 정렬될 수도
있고 아니면 몇 개의 원소가 같이 정렬된 지금의 경우와 같이 정렬될 수 있다.
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

template <typename T>
auto partition(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end)
{
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;

	while (true)
	{
		// 벡터의 첫 번째 원소부터 시작하여 피벗보다 큰 원소를 찾습니다.
		while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
			left_iter++;

		// 벡터의 마지막 원소부터 시작하여 역순으로 피벗보다 작은 원소를 찾습니다.
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			right_iter--;

		// 만약 left_iter와 right_iter가 같다면 교환할 원소가 없음을 의미합니다.
		// 그렇지 않으면 left_iter와 right_iter가 가리키는 원소를 서로 교환합니다.
		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}

	if (pivot_val > *right_iter)
		std::iter_swap(begin, right_iter);

	return right_iter;
}

template <typename T>
void partial_quick_sort(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last,
	size_t k)
{
	// 벡터에 하나 이상의 원소가 남아 있는 경우
	if (std::distance(begin, last) >= 1)
	{
		// 분할 연산을 수행
		auto partition_iter = partition<T>(begin, last);

		// 분할 연산에 의해 생성된 두 벡터를 재귀적으로 정렬
		partial_quick_sort<T>(begin, partition_iter - 1, k);

		// 만약 마지막 피벗 위치가 k보다 작으면 오른쪽 부분 벡터도 정렬
		//오른쪽 부분 벡터를 정렬할 때 k를 그대로 전달하면 또 다시 k개를 정렬하는 셈이 된다. 따라서
		//k에서 정렬한 원소만큼 빼줘야 나머지 개수를 정렬할 것이다. 해당 코드는 partial_quick_sort2함수에서 정의했다.
		if (std::distance(begin, partition_iter) < k)
			partial_quick_sort<T>(partition_iter, last, k);
	}
}

template <typename T>
void partial_quick_sort2(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last,
	size_t k)
{
	// 벡터에 하나 이상의 원소가 남아 있는 경우
	if (std::distance(begin, last) >= 1)
	{
		// 분할 연산을 수행
		auto partition_iter = partition<T>(begin, last);

		// 분할 연산에 의해 생성된 두 벡터를 재귀적으로 정렬
		partial_quick_sort2<T>(begin, partition_iter - 1, k);

		// 만약 마지막 피벗 위치가 k보다 작으면 오른쪽 부분 벡터도 정렬
		//만약 k개의 원소를 정확히 정렬한다는 생각으로 partition_iter + (k-distance) 만큼만 정렬한다는 생각을 하면 안된다.
		//예를 들어 다음과 같이 생각했을 경우이다.
		//5 1 3 9 7 6에서 k = 4라고 할 때, 왼쪽 부분 벡터가 정렬된 상태이고 오른쪽 부분 벡터를 정렬하려 할 때
		//1 3 5 9 ,  7 6   이렇게 3번째 까지 정렬되었으므로 오른쪽은 하나만 정렬하면 되는 거 아닌가 라고 생각할 수 있는데
		//이 생각은 잘못된 생각이다. 오른쪽 부분 시퀀스 전체를 보고 partition을 해야 6이 제자리에 올 수 있기 때문이다.
		//만약 위 생각처럼 코드를 짜면 k = 4 까지 정렬된 시퀀스는 1 3 5 9 가 될 것이다. 이것은 잘못된 결과이다.
		if (std::distance(begin, partition_iter) < k)
			partial_quick_sort2<T>(partition_iter, last, k - std::distance(begin, partition_iter));
	}
}

template <typename T>
void quick_sort(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last)
{
	// 만약 벡터에 하나 이상의 원소가 있다면
	if (std::distance(begin, last) >= 1)
	{
		// 분할 작업을 수행
		auto partition_iter = partition<T>(begin, last);

		// 분할 작업에 의해 생성된 벡터를 재귀적으로 정렬
		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
}

template <typename T>
void print_vector(std::vector<T> arr)
{
	for (auto i : arr)
		std::cout << i << " ";

	std::cout << std::endl;
}

// [1, size] 범위에 속하는 임의의 정수를 생성합니다. 
template <typename T>
auto generate_random_vector(T size)
{
	std::vector<T> V;
	V.reserve(size); //vector의 공간을 size만큼 미리 확보하는 것.

	std::random_device rd;
	std::mt19937 rand(rd());

	//시작 범위와 끝 범위가 포함되는 출력 범위 내에서 균등한(모든 값이 균일하게 있을 것 같음) 정수 분포를 생성합니다.
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	for (T i = 0; i < size; i++)
		V.push_back(uniform_dist(rand));

	return std::move(V); //함수는 반환값이 R-Value이다. 즉 move를 통해서 R-Value Reference로 반환하는 것이다.
	//하지만 C++11부터는 컴파일러가 알아서 RVO,NRVO를 통해서 함수의 반환값을 R-Value로
	//최적화시키기 때문에 move를 통해서 이동 가능함을 명시할 필요는 없는 것 같다.
	//컴파일러에서도 이러한 경고 메시지를 출력한다.
	//지역 변수를 반환하려면 move를 사용하지 마세요.
}

template <typename T>
void test_partial_quicksort(size_t size, size_t k)
{
	// 임의의 벡터를 생성하고, 복사본을 만들어 두 알고리즘에 각각 테스트 진행.
	auto random_vec = generate_random_vector<T>(size);
	//std::vector<T> vec = { 5,1,3,9,7,6 };
	//auto random_vec = vec;
	auto random_vec_copy(random_vec);

	std::cout << "입력 벡터: " << std::endl;
	print_vector<T>(random_vec);

	// 부분 퀵 정렬 알고리즘 수행 시간 측정
	auto begin1 = std::chrono::steady_clock::now();
	partial_quick_sort<T>(random_vec.begin(), random_vec.end() - 1, k);
	auto end1 = std::chrono::steady_clock::now();
	auto diff1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);

	std::cout << std::endl;
	std::cout << "부분 퀵 정렬 수행 시간: " << diff1.count() << "us" << std::endl;

	std::cout << "(처음 " << k << "개 원소만) 부분 정렬된 벡터: ";
	print_vector<T>(random_vec);

	// 전체 퀵 정렬 알고리즘 수행 시간 측정
	/*auto begin2 = std::chrono::steady_clock::now();
	quick_sort<T>(random_vec_copy.begin(), random_vec_copy.end() - 1);
	auto end2 = std::chrono::steady_clock::now();
	auto diff2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);

	std::cout << std::endl;
	std::cout << "전체 퀵 정렬 수행 시간: " << diff2.count() << "us" << std::endl;

	std::cout << "전체 정렬된 벡터: ";
	print_vector<T>(random_vec_copy);*/

	//부분 퀵 정렬 2 실행 결과
	auto begin2 = std::chrono::steady_clock::now();
	partial_quick_sort2<T>(random_vec_copy.begin(), random_vec_copy.end() - 1,k);
	auto end2 = std::chrono::steady_clock::now();
	auto diff2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);

	std::cout << std::endl;
	std::cout << "부분 퀵 정렬2 수행 시간: " << diff2.count() << "us" << std::endl;

	std::cout << "부분 정렬된 벡터: ";
	print_vector<T>(random_vec_copy);
}

int main()
{
	test_partial_quicksort<unsigned>(100, 10);

	//test_partial_quicksort<unsigned>(6, 4);
	return 0;
}

/*
* 아래 결과를 살펴보면, 부분 퀵 정렬2 버전이 더 정확한 개수가 정렬된 것을 확인할 수 있다. 오른쪽 부분 벡터를 정렬할 때
* k를 그대로 전달하면 또 k개만큼 정렬하게 되므로 잘못된 코드이다.
* 
* 입력 벡터:
86 80 51 94 66 84 43 40 59 87 26 3 94 80 44 2 85 37 52 63 48 4 69 56 16 86 46 23 91 48 2 79 42 89 98 15 2 23 18 17 37 66 99 82 88 26 21 99 49 55 94 31 62 14 26 33 52 30 56 39 85 36 71 55 21 19 22 91 10 74 48 56 11 57 28 43 92 33 65 89 23 57 66 23 96 93 14 18 15 82 53 97 77 96 81 38 68 49 100 69

부분 퀵 정렬 수행 시간: 368us
(처음 10개 원소만) 부분 정렬된 벡터: 2 2 2 3 4 10 11 14 14 15 15 16 17 18 18 19 21 21 22 23 23 23 23 26 26 28 26 30 38 48 46 56 42 48 48 52 37 56 44 57 37 55 53 36 39 49 40 43 49 55 43 31 56 33 51 33 52 57 62 82 85 82 71 66 77 81 79 86 69 74 63 85 80 68 59 84 66 69 65 66 80 86 89 92 96 93 91 94 99 88 99 97 98 96 89 91 94 87 100 94

부분 퀵 정렬2 수행 시간: 252us
부분 정렬된 벡터: 2 2 2 3 4 10 11 14 14 15 15 18 17 22 18 23 23 16 21 21 19 23 23 26 26 28 26 30 38 48 46 56 42 48 48 52 37 56 44 57 37 55 53 36 39 49 40 43 49 55 43 31 56 33 51 33 52 57 62 82 85 82 71 66 77 81 79 86 69 74 63 85 80 68 59 84 66 69 65 66 80 86 89 92 96 93 91 94 99 88 99 97 98 96 89 91 94 87 100 94
*/