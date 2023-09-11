#include <iostream>
#include <vector>

#include <openssl/md5.h>

class BloomFilter
{
	//해시 크기를 나타내는 정수형
	int nHashes;
	//최대 255비트의 블룸 필터
	std::vector<bool> bits;

	static constexpr int hashSize = 128 / 8; // 128비트(16바이트)

	//16바이트 크기의 해시 값을 저장하는 문자 배열
	unsigned char hashValue[hashSize];

public:
	BloomFilter(int size, int hashes) : bits(size), nHashes(hashes)
	{
		if (nHashes > hashSize)
		{
			throw("해시 함수 개수가 너무 많습니다.");
		}

		if (size > 255)
		{
			throw("블룸 필터 크기가 255보다 클 수 없습니다.");
		}
	}

	void hash(const std::string& key)
	{
		//key 길이에 상관없이 16바이트의 해시 값을 생성한다. 하지만 key 길이도 해시 값에 영향을 준다.
		MD5(reinterpret_cast<const unsigned char*>(key.data()), key.length(), hashValue);
	}

	void add(const std::string& key)
	{
		hash(key);
		//해시 값 배열의 각 인덱스를 블룸 필터 사이즈로 나머지 연산을 하여 블룸 필터에 저장한다.
		for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
		{
			bits[*it % bits.size()] = true;
		}

		std::cout << "블룸 필터에 추가: " << key << std::endl;
	}

	bool mayContain(const std::string& key)
	{
		hash(key);
		//만약 key에 해당하는 해시 값이 하나라도 중복되지 않으면 블룸 필터에 저장할 수 있다.
		//이 상황은 key가 블룸 필터에 반드시 없다.
		for (auto it = &hashValue[0]; it < &hashValue[nHashes]; it++)
		{
			if (!bits[*it % bits.size()])
			{
				std::cout << key << " : 사용할 수 있는 이메일입니다." << std::endl;
				return false;
			}
		}

		//위 for문을 통과했다는 것은 모든 해시 값이 이미 true로 설정되어 있기 때문에 mayContain의 상황이다.
		//즉 있을 수도 없을 수도 있다.
		std::cout << key << " : 이미 사용 중입니다." << std::endl;
		return true;
	}
};

int main()
{
	BloomFilter bloom(128, 5);

	bloom.add("abc@gilbut.com");
	bloom.add("xyz@gilbut.com");

	bloom.mayContain("abc");
	bloom.mayContain("xyz@gilbut.com");
	bloom.mayContain("xyz");

	bloom.add("abcd@gilbut.com");
	bloom.add("ab@gilbut.com");

	bloom.mayContain("abcd");
	bloom.mayContain("ab@gilbut.com");
}