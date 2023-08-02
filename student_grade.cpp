#include <iostream>
using namespace std;

class Score_System
{
	typedef unsigned int uint;
private:
	class Student_Info
	{
	private:
		string sName;
		uint iScore;
	public:
		Student_Info(const string& _sName = " ", const uint& _iScore = 0) :sName(_sName), iScore(_iScore) {}
		string GetName() const
		{
			return sName;
		}
		uint GetScore() const
		{
			return iScore;
		}
		void SetName(const string& _sName)
		{
			sName = _sName;
		}
		void SetScore(const uint& _iScore)
		{
			iScore = _iScore;
		}
	};
	Student_Info* sArr;
	uint iSize;
	uint iTotal;
	uint iAve;
	uint iCount=0;
public:
	Score_System(const uint& _iSize = 0) :sArr(nullptr), iSize(_iSize)
	{
		sArr = new Student_Info[iSize];
		iAve = 0;
		iTotal = 0;
	}
	Score_System(const Score_System& S) :Score_System(0)
	{
		if (this != &S)
		{
			sArr = new Student_Info[S.GetSize()];
			iSize = S.GetSize();
			for (register int i = 0; i < S.GetSize(); ++i)
			{
				sArr[i] = (S.GetArrptr())[i];
			}
			cout << "copy constructor called"<<endl;
		}
	}
	Score_System(Score_System&& S) noexcept :Score_System(0) 
	{
		if (this != &S)
		{
			sArr = S.GetArrptr();
			S.NULLArrptr();
			iSize = S.GetSize();

			cout << "move constructor called"<<endl;
		}
	}
	~Score_System()
	{
		delete []sArr;
	}
	uint GetSize() const
	{
		return iSize;
	}
	Student_Info* GetArrptr() const
	{
		return sArr;
	}
	void SetSize(const uint& _iSize)
	{
		iSize = _iSize;
	}
	void NULLArrptr()
	{
		sArr = nullptr;
	}
	void print_all()
	{
		for (register int i = 0; i < iSize; ++i)
		{
			cout << sArr[i].GetName() << " " << sArr[i].GetScore()<<endl;
		}
		score_proccessing();
		cout << "총점: " << iTotal << " " << "평균: " << iAve << " "<<endl;
	}
	void score_proccessing()
	{
		for (register int i = 0; i < iSize; ++i)
		{
			iTotal += sArr[i].GetScore();
		}
		iAve = iTotal / iSize;
	}
	void insert_student(const string& sName,const uint& _iScore)
	{
		if (iCount == iSize)
		{
			cout << "더 이상 삽입할 수 없습니다." << endl;
		}
		else
		{
			sArr[iCount].SetName(sName);
			sArr[iCount++].SetScore(_iScore);
		}
	}
	void find_student(const string& _sName) const
	{
		uint i = 0;
		for (; i < iSize; ++i)
		{
			if (_sName == sArr[i].GetName())
			{
				cout << "학생을 찾았습니다. 정보를 출력합니다." << endl;
				break;
			}
		}
		if (i == iSize)
		{
			cout << "해당하는 학생이 없습니다." << endl;
		}
		else
		{
			cout << "점수 :" << sArr[i].GetName();
		}
	}
};

int main()
{
	Score_System S(5);
	S.insert_student("Lee", 98);
	S.insert_student("Park", 93);
	S.insert_student("Seo", 78);
	S.insert_student("Moon", 54);
	S.insert_student("Min", 87);
	Score_System S1(S);
	Score_System S2(move(S));
	S1.print_all();
	S2.print_all();

	S1.find_student("Lee");
	S1.find_student("Jeong");

	//S.print_all();
}