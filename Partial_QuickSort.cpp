/*
* �ʱ� ���� 5 1 3 9 7 6
k=3

partial_quick_sort ��� ����

1. partition ȣ�� ->5 1 3 9 7 6  -> partial_quick_sort (5 1 3) ȣ��  
                          p

2. partition ȣ�� -> 3 1 5 -> partial_quick_sort(3 1) ȣ��
	                     p

3. partition ȣ�� -> 1 3 -> partial_quick_sort(1)ȣ��
                       p

4. distance�� 0�̹Ƿ� partial_quick_sort(1)�� ���� �۾� ����

5. 3���� distance<k if�� ���� -> distance�� 0�̹Ƿ� �۾� ���� ->3�� ��� ����

6. 2���� distance<k if�� ���� -> distance�� 0�̹Ƿ� �۾� ���� -> 2�� ��� ����

7. 1���� distance<k if�� ���� -> distance�� k�� ���� 3�̹Ƿ� if�� ���� �ȵ� -> 1�� ��� ����

���������  1 3 5 9 7 6
3���� ���Ҹ� ���ĵǾ���

���� k�� 4��� 1 3 5 6 7 9�� �Ǵµ� �� ���� ���� ���ĵ� �����̴�. �� �Ǻ��� k�� ���迡 ���� ������ ������
k������ ���ĵǴ� ���� �ƴѵ� �ϴ�. ���� ����� ������ ���ĵǴ� ���� Ȯ���ϴ�. k�� 2�� 1 3 5 9 7 6���� k��
3�϶��� ����.

k�� 4���, 9 7 6 �κ� �������� �����ؾ� �Ѵ�. �׷��� �� ���������� 9�� ������ ���� ���� partition ��������
6 7 9�� �Ǿ� ���� ������ �������� ��� ���ĵ� ���°� �ȴ�. ���� ������ ���¿� ���� ��Ȯ�� k��° ���� ���ĵ� ����
�ְ� �ƴϸ� �� ���� ���Ұ� ���� ���ĵ� ������ ���� ���� ���ĵ� �� �ִ�.
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
		// ������ ù ��° ���Һ��� �����Ͽ� �ǹ����� ū ���Ҹ� ã���ϴ�.
		while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
			left_iter++;

		// ������ ������ ���Һ��� �����Ͽ� �������� �ǹ����� ���� ���Ҹ� ã���ϴ�.
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			right_iter--;

		// ���� left_iter�� right_iter�� ���ٸ� ��ȯ�� ���Ұ� ������ �ǹ��մϴ�.
		// �׷��� ������ left_iter�� right_iter�� ����Ű�� ���Ҹ� ���� ��ȯ�մϴ�.
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
	// ���Ϳ� �ϳ� �̻��� ���Ұ� ���� �ִ� ���
	if (std::distance(begin, last) >= 1)
	{
		// ���� ������ ����
		auto partition_iter = partition<T>(begin, last);

		// ���� ���꿡 ���� ������ �� ���͸� ��������� ����
		partial_quick_sort<T>(begin, partition_iter - 1, k);

		// ���� ������ �ǹ� ��ġ�� k���� ������ ������ �κ� ���͵� ����
		//������ �κ� ���͸� ������ �� k�� �״�� �����ϸ� �� �ٽ� k���� �����ϴ� ���� �ȴ�. ����
		//k���� ������ ���Ҹ�ŭ ����� ������ ������ ������ ���̴�. �ش� �ڵ�� partial_quick_sort2�Լ����� �����ߴ�.
		if (std::distance(begin, partition_iter) < k)
			partial_quick_sort<T>(partition_iter, last, k);
	}
}

template <typename T>
void partial_quick_sort2(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last,
	size_t k)
{
	// ���Ϳ� �ϳ� �̻��� ���Ұ� ���� �ִ� ���
	if (std::distance(begin, last) >= 1)
	{
		// ���� ������ ����
		auto partition_iter = partition<T>(begin, last);

		// ���� ���꿡 ���� ������ �� ���͸� ��������� ����
		partial_quick_sort2<T>(begin, partition_iter - 1, k);

		// ���� ������ �ǹ� ��ġ�� k���� ������ ������ �κ� ���͵� ����
		//���� k���� ���Ҹ� ��Ȯ�� �����Ѵٴ� �������� partition_iter + (k-distance) ��ŭ�� �����Ѵٴ� ������ �ϸ� �ȵȴ�.
		//���� ��� ������ ���� �������� ����̴�.
		//5 1 3 9 7 6���� k = 4��� �� ��, ���� �κ� ���Ͱ� ���ĵ� �����̰� ������ �κ� ���͸� �����Ϸ� �� ��
		//1 3 5 9 ,  7 6   �̷��� 3��° ���� ���ĵǾ����Ƿ� �������� �ϳ��� �����ϸ� �Ǵ� �� �ƴѰ� ��� ������ �� �ִµ�
		//�� ������ �߸��� �����̴�. ������ �κ� ������ ��ü�� ���� partition�� �ؾ� 6�� ���ڸ��� �� �� �ֱ� �����̴�.
		//���� �� ����ó�� �ڵ带 ¥�� k = 4 ���� ���ĵ� �������� 1 3 5 9 �� �� ���̴�. �̰��� �߸��� ����̴�.
		if (std::distance(begin, partition_iter) < k)
			partial_quick_sort2<T>(partition_iter, last, k - std::distance(begin, partition_iter));
	}
}

template <typename T>
void quick_sort(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last)
{
	// ���� ���Ϳ� �ϳ� �̻��� ���Ұ� �ִٸ�
	if (std::distance(begin, last) >= 1)
	{
		// ���� �۾��� ����
		auto partition_iter = partition<T>(begin, last);

		// ���� �۾��� ���� ������ ���͸� ��������� ����
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

// [1, size] ������ ���ϴ� ������ ������ �����մϴ�. 
template <typename T>
auto generate_random_vector(T size)
{
	std::vector<T> V;
	V.reserve(size); //vector�� ������ size��ŭ �̸� Ȯ���ϴ� ��.

	std::random_device rd;
	std::mt19937 rand(rd());

	//���� ������ �� ������ ���ԵǴ� ��� ���� ������ �յ���(��� ���� �����ϰ� ���� �� ����) ���� ������ �����մϴ�.
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	for (T i = 0; i < size; i++)
		V.push_back(uniform_dist(rand));

	return std::move(V); //�Լ��� ��ȯ���� R-Value�̴�. �� move�� ���ؼ� R-Value Reference�� ��ȯ�ϴ� ���̴�.
	//������ C++11���ʹ� �����Ϸ��� �˾Ƽ� RVO,NRVO�� ���ؼ� �Լ��� ��ȯ���� R-Value��
	//����ȭ��Ű�� ������ move�� ���ؼ� �̵� �������� ����� �ʿ�� ���� �� ����.
	//�����Ϸ������� �̷��� ��� �޽����� ����Ѵ�.
	//���� ������ ��ȯ�Ϸ��� move�� ������� ������.
}

template <typename T>
void test_partial_quicksort(size_t size, size_t k)
{
	// ������ ���͸� �����ϰ�, ���纻�� ����� �� �˰��� ���� �׽�Ʈ ����.
	auto random_vec = generate_random_vector<T>(size);
	//std::vector<T> vec = { 5,1,3,9,7,6 };
	//auto random_vec = vec;
	auto random_vec_copy(random_vec);

	std::cout << "�Է� ����: " << std::endl;
	print_vector<T>(random_vec);

	// �κ� �� ���� �˰��� ���� �ð� ����
	auto begin1 = std::chrono::steady_clock::now();
	partial_quick_sort<T>(random_vec.begin(), random_vec.end() - 1, k);
	auto end1 = std::chrono::steady_clock::now();
	auto diff1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);

	std::cout << std::endl;
	std::cout << "�κ� �� ���� ���� �ð�: " << diff1.count() << "us" << std::endl;

	std::cout << "(ó�� " << k << "�� ���Ҹ�) �κ� ���ĵ� ����: ";
	print_vector<T>(random_vec);

	// ��ü �� ���� �˰��� ���� �ð� ����
	/*auto begin2 = std::chrono::steady_clock::now();
	quick_sort<T>(random_vec_copy.begin(), random_vec_copy.end() - 1);
	auto end2 = std::chrono::steady_clock::now();
	auto diff2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);

	std::cout << std::endl;
	std::cout << "��ü �� ���� ���� �ð�: " << diff2.count() << "us" << std::endl;

	std::cout << "��ü ���ĵ� ����: ";
	print_vector<T>(random_vec_copy);*/

	//�κ� �� ���� 2 ���� ���
	auto begin2 = std::chrono::steady_clock::now();
	partial_quick_sort2<T>(random_vec_copy.begin(), random_vec_copy.end() - 1,k);
	auto end2 = std::chrono::steady_clock::now();
	auto diff2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);

	std::cout << std::endl;
	std::cout << "�κ� �� ����2 ���� �ð�: " << diff2.count() << "us" << std::endl;

	std::cout << "�κ� ���ĵ� ����: ";
	print_vector<T>(random_vec_copy);
}

int main()
{
	test_partial_quicksort<unsigned>(100, 10);

	//test_partial_quicksort<unsigned>(6, 4);
	return 0;
}

/*
* �Ʒ� ����� ���캸��, �κ� �� ����2 ������ �� ��Ȯ�� ������ ���ĵ� ���� Ȯ���� �� �ִ�. ������ �κ� ���͸� ������ ��
* k�� �״�� �����ϸ� �� k����ŭ �����ϰ� �ǹǷ� �߸��� �ڵ��̴�.
* 
* �Է� ����:
86 80 51 94 66 84 43 40 59 87 26 3 94 80 44 2 85 37 52 63 48 4 69 56 16 86 46 23 91 48 2 79 42 89 98 15 2 23 18 17 37 66 99 82 88 26 21 99 49 55 94 31 62 14 26 33 52 30 56 39 85 36 71 55 21 19 22 91 10 74 48 56 11 57 28 43 92 33 65 89 23 57 66 23 96 93 14 18 15 82 53 97 77 96 81 38 68 49 100 69

�κ� �� ���� ���� �ð�: 368us
(ó�� 10�� ���Ҹ�) �κ� ���ĵ� ����: 2 2 2 3 4 10 11 14 14 15 15 16 17 18 18 19 21 21 22 23 23 23 23 26 26 28 26 30 38 48 46 56 42 48 48 52 37 56 44 57 37 55 53 36 39 49 40 43 49 55 43 31 56 33 51 33 52 57 62 82 85 82 71 66 77 81 79 86 69 74 63 85 80 68 59 84 66 69 65 66 80 86 89 92 96 93 91 94 99 88 99 97 98 96 89 91 94 87 100 94

�κ� �� ����2 ���� �ð�: 252us
�κ� ���ĵ� ����: 2 2 2 3 4 10 11 14 14 15 15 18 17 22 18 23 23 16 21 21 19 23 23 26 26 28 26 30 38 48 46 56 42 48 48 52 37 56 44 57 37 55 53 36 39 49 40 43 49 55 43 31 56 33 51 33 52 57 62 82 85 82 71 66 77 81 79 86 69 74 63 85 80 68 59 84 66 69 65 66 80 86 89 92 96 93 91 94 99 88 99 97 98 96 89 91 94 87 100 94
*/