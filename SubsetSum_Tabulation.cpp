#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>
#include <iostream>

#define DEBUG 0

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;

const int UNKNOWN = -1;

void GetAllSubsets(vector<int> set, vector<int> subset,
	int index, vector<vector<vector<int>>>& allSubsets)
{
	// ÁıÇÕ setÀÇ ³¡¿¡ µµ´ŞÇÑ °æ¿ì
	if (index == set.size())
	{
		// ºÎºĞÁıÇÕ Å©±â¸¦ ÀÎµ¦½º·Î »ç¿ëÇÏ¿© ºÎºĞÁıÇÕÀ» allSubsets¿¡ Ãß°¡
		allSubsets[subset.size()].push_back(subset);
		return;
	}

	// ¿ø¼Ò¸¦ Ãß°¡ÇÏÁö ¾Ê°í Àç±Í È£Ãâ
	GetAllSubsets(set, subset, index + 1, allSubsets);

	// ¿ø¼Ò¸¦ ºÎºĞÁıÇÕ¿¡ Ãß°¡ÇÑ ÈÄ Àç±Í È£Ãâ
	subset.push_back(set[index]);
	GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target)
{
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	GetAllSubsets(set, {}, 0, allSubsets);

	for (int size = 0; size <= set.size(); size++)
	{
		PRINT("ºÎºĞÁıÇÕÀÇ ¿ø¼Ò °³¼ö: " << size << endl);

		for (auto subset : allSubsets[size])
		{
			PRINT("\t{ ");

			int sum = 0;
			for (auto number : subset)
			{
				sum += number;
				PRINT(number << " ");
			}

			PRINT("} = " << sum << endl);

			if (sum == target)
				return true;
		}
	}

	return false;
}

bool SubsetSum_Backtracking(vector<int> set, int sum, int i)
{
	// ¸¸¾à ÇöÀç ºÎºĞÁıÇÕÀÇ ÇÕÀÌ target°ú °°´Ù¸é
	if (sum == 0)
	{
		return true;
	}

	// ¸¸¾à ÇöÀç ºÎºĞÁıÇÕÀÇ ÇÕÀÌ targetº¸´Ù Å©°Å³ª, ÁıÇÕÀÇ ³¡¿¡ µµ´ŞÇß´Ù¸é
	if (i == set.size() || set[i] > sum)
	{
		return false;
	}

	// Case 1: sum¿¡¼­ set[i]À» »©¼­ Àç±Í È£Ãâ (i¹øÂ° ¿ø¼Ò¸¦ ºÎºĞÁıÇÕ¿¡ Ãß°¡)
	// Case 2: sumÀ» ±×´ë·Î Àü´ŞÇÏ¿© Àç±Í È£Ãâ (i¹øÂ° ¿ø¼Ò¸¦ ºÎºĞÁıÇÕ¿¡ Ãß°¡ÇÏÁö ¾ÊÀ½)

	return SubsetSum_Backtracking(set, sum - set[i], i + 1)
		|| SubsetSum_Backtracking(set, sum, i + 1);
}

bool SubsetSum_Memoization(vector<int>& set, int sum, int i,
	vector<vector<int>>& memo)
{
	// ¸¸¾à ÇöÀç ºÎºĞÁıÇÕÀÇ ÇÕÀÌ target°ú °°´Ù¸é
	if (sum == 0)
	{
		return true;
	}

	// ¸¸¾à ÇöÀç ºÎºĞÁıÇÕÀÇ ÇÕÀÌ targetº¸´Ù Å©°Å³ª, ÁıÇÕÀÇ ³¡¿¡ µµ´ŞÇß´Ù¸é
	if (i == set.size() || set[i] > sum)
	{
		return false;
	}

	// ÇöÀç »óÅÂ°¡ Ä³½Ã¿¡ ÀÖ´ÂÁö È®ÀÎ
	if (memo[i][sum] == UNKNOWN)
	{
		// ÇöÀç »óÅÂ¿¡ ´ëÇÑ ¼Ö·ç¼ÇÀ» ±¸ÇÏ¿© Ä³½Ã¿¡ ÀúÀå
		bool append = SubsetSum_Memoization(set, sum - set[i], i + 1, memo);
		bool ignore = SubsetSum_Memoization(set, sum, i + 1, memo);

		memo[i][sum] = append || ignore;
	}

	// Ä³½Ã¿¡ ÀúÀåµÈ °ªÀ» ¹İÈ¯
	return memo[i][sum];
}

//ÀÌ ÇÔ¼ö´Â Á¤¼ö º¤ÅÍ setÀ» ÀÎÀÚ·Î ¹Ş°í, 2Â÷¿ø ºÎ¿ïÇü º¤ÅÍ¸¦ ¹İÈ¯ÇÑ´Ù,
vector<vector<bool>> SubsetSum_Tabulation(vector<int>& set)
{
	int maxSum = 0;

	for (int i = 0; i < set.size(); i++)
	{
		maxSum += set[i];
	}

	//DP¶ó´Â ÀÌ¸§ÀÇ 2Â÷¿ø ºÎ¿ïÇü º¤ÅÍ¸¦ ¼±¾ğÇÏ¿© »ç¿ëÇÑ´Ù. dpÀÇ Ã¹ ¹øÂ° Â÷¿ø Å©±â´Â ÀÔ·Â ÁıÇÕÀÇ Å©±â¿Í °°°í, µÎ ¹øÂ° Â÷¿øÀÇ Å©±â´Â
	//ÀÔ·Â ÁıÇÕÀÇ ¸ğµç ¿ø¼Ò ÇÕº¸´Ù 1¸¸Å­ Å©°Ô ¼³Á¤ÇÑ´Ù. dpÀÇ ¸ğµç ¿ø¼Ò´Â false·Î ÃÊ±âÈ­ÇÏµÇ, ºÎºĞÁıÇÕÀÇ ÇÕÀÌ 0ÀÎ ±âÀú Á¶°Ç¿¡ ´ëÇØ¼­
	//´Â true·Î ¼³Á¤ÇÑ´Ù.

	//Ã¹ ¹øÂ° Â÷¿øÀº ÀÎµ¦½º¸¦ ÀÇ¹ÌÇÏ°í µÎ ¹øÂ° Â÷¿øÀº ºÎºĞÁıÇÕÀÇ ÇÕÀ» ÀÇ¹ÌÇÑ´Ù.
	vector<vector<bool>> DP(set.size() + 1, vector<bool>(maxSum + 1, 0));

	//°¢ Â÷¿øÀÇ ±âÀú Á¶°ÇÀÎ ÀÎµ¦½º 0À» true·Î ¼³Á¤ÇÑ´Ù.
	for (int i = 0; i < set.size(); i++)
	{
		DP[i][0] = true;
	}

	//DP Å×ÀÌºí ¿ø¼Ò °ªÀ» ¼³Á¤ÇÏ±â À§ÇØ ÀÌÁß for¹İº¹¹®À» »ç¿ëÇÑ´Ù.

	//3 7 9 13 16 22 46 47 55 85 92 98 106 333 367 577 807 1058 3059


	//i¿¡¼­´Â i-1 ÀÎµ¦½º±îÁöÀÇ Á¶ÇÕÀÌ sumÀ» ¸¸µé ¼ö ÀÖ´Ù¸é i¿¡¼­µµ sumÀ» ¸¸µé ¼ö ÀÖ´Ù.
	//if-else·Î °æ¿ì°¡ ³ª´µ´Â ÀÌÀ¯´Â sum°ªÀÌ set[i-1]º¸´Ù °°°Å³ª Å©´Ù¸é i-1 ÀÌÀü ´Ü°è¿¡¼­ ÀÌ¹Ì sum°ªÀÌ
	//¸¸µé¾îÁú ¼ö ÀÖ´Â °æ¿ìµµ ÀÖÁö¸¸, i-1±îÁö ¿ø¼Ò¸¦ ¸ğµÎ ÇÕÇØµµ sum°ªº¸´Ù ÀÛÀº °æ¿ì°¡ ÀÖ´Ù. 
	//¿ø¼Ò 9 ÀÌÇÏÀÇ °æ¿ì¸¦ »ı°¢ÇØº¸¸é µÈ´Ù. 7±îÁö 3,7À» ¸¸µé ¼ö´Â ÀÖÁö¸¸ 10Àº 7À» ÇÕÇØ¾ß ¸¸µé ¼ö ÀÖ´Ù.
	//µû¶ó¼­ 7À» »°À» ¶§ ¸¸µé¾îÁú ¼ö ÀÖ´Â°¡¸¦ º¸´Â °ÍÀÌ´Ù. ¸¸¾à ¸¸µé¾îÁú ¼ö ÀÖ´Ù¸é 7À» ´õÇÏ¸é  7¿¡¼­ 10±îÁö ¸¸µé ¼ö ÀÖ´Ù. ¶ÇÇÑ 9¿¡¼­µµ ÇØ´ç °ªÀ» 
	//¸¸µé ¼ö ÀÖ°Ô µÈ´Ù. DP[i-1][sum]À» °ËÅäÇÏ´Â °ÍÀº set[i-1]ÀÌ ´õÇØÁöÁö ¾Ê¾ÒÀ» °æ¿ì¸¸ °ËÅäÇÏ±â ¶§¹®¿¡ if-else·Î ³ª´¶´Ù.
	
<<<<<<< HEAD
	//¸¸¾à ÀÎµ¦½º i=set.sizeÀÏ ¶§´Â ¸¶Áö¸· ¿ø¼Ò±îÁöÀÇ ÇÕÀÌ DP[set.size]¿¡ ÀúÀåµÈ´Ù.
=======
	//ë§Œì•½ ì¸ë±ìŠ¤ i=set.sizeì¼ ë•ŒëŠ” ë§ˆì§€ë§‰ ì›ì†Œê¹Œì§€ì˜ í•©ì´ DP[set.size]ì— ì €ì¥ëœë‹¤.
>>>>>>> 36958ff8f3035530e08b316d8a953353b498398f
	for (int i = 1; i <= set.size(); i++)
	{
		for (int sum = 1; sum <= maxSum; sum++)
		{
			//ÀÎµ¦½º i=1ÀÏ ¶§´Â Set[0] = 3 ÀÌ¹Ç·Î 2±îÁö Ã¹ ¹øÂ° if¹®ÀÌ ½ÇÇàµÈ´Ù.
			if (sum < set[i - 1])
			{
				cout << "<" << i << ">" << endl;

				cout << "sum("<<sum<<") < set["<<i-1<<"]("<<set[i-1]<< ") called" << endl;

				//°¡Àå ÃÊ±â¿¡´Â sum=1ÀÌ°í, iµµ 1ÀÌ´Ù.
				//DP[1][1]=DP[0][1]ÀÌ µÈ´Ù.
				//DP[1][1]=false°¡ µÈ´Ù. DP[0][1]Àº falseÀÌ´Ù.

				//ÀÎµ¦½º i=1¿¡¼­´Â
				//DP[1][1~MAX] = DP[0][MAX]°¡ µÈ´Ù.
				auto temp = DP[i][sum];

				DP[i][sum] = DP[i - 1][sum];

				cout << "DP[" << i << "][" << sum << "](" << temp << ") = DP[" << i - 1 << "][" << sum << "](" << DP[i - 1][sum] << ") : " << DP[i][sum]<<endl;
				cout << endl;
			}
			else // sum >= set[i-1]
			{
				cout << "<" << i << ">" << endl;

				cout << "else called" << endl;
				//i=1ÀÏ ¶§ sumÀÌ 3ÀÌ µÇ¸é ÇØ´ç ÄÚµå°¡ ½ÇÇàµÈ´Ù.
				//DP[1][3]=DP[0][3] || DP[0][0] ÀÌ µÈ´Ù.

				//ÀÌ ÄÚµå¸¦ ºĞ¼®ÇØº¸¸é, ÀÎµ¦½º i¿¡¼­ ºÎºĞÁıÇÕÀÇ ÇÕ sum >= set[i]ÀÏ ¶§
				//DP[i-1][sum] = true Áï ÇÏ³ª ÀÌÀü ÀÎµ¦½º¿¡¼­ ÇØ´ç sum°ªÀ» ¸¸µé ¼ö ÀÖ´Ù¸é
				//i¿¡¼­µµ sumÀ» ¸¸µé ¼ö ÀÖ´Ù.

				//i°¡ °¡¸®Å°´Â °ªÀÌ 9±îÁö¸¸ ÀÌ ÇÔ¼öÀÇ ÁøÇà »óÈ²À» ±â·ÏÇØº¸ÀÚ.
				//¸ÕÀú DP[1]¿¡´Â 3ÀÌ true·Î ¼³Á¤µÉ °ÍÀÌ´Ù.
				//i°¡ 2°¡ µÇ¸é DP[2]¿¡´Â 3 7 10ÀÌ true·Î ¼³Á¤µÉ °ÍÀÌ´Ù.
				//10ÀÌ true·Î ¼³Á¤µÇ´Â °úÁ¤Àº DP[1][10]Àº ºÒ°¡´ÉÇÏ¹Ç·Î 
				//DP[1][3]À¸·Î ³Ñ¾î°£´Ù. ±×·±µ¥ À§¿¡¼­ DP[1][3]Àº trueÀÌ¹Ç·Î DP[2][10]Àº true·Î ¼³Á¤µÈ´Ù.
				//µû¶ó¼­ sum < set[i-1]ÀÏ ¶§´Â set[i-1]ÀÌ ´õÇØÁø °á°ú¸¦ »ı°¢ÇÒ ÇÊ¿ä ¾øÀÌ set[i-1]¿¡¼­ sumÀÌ ¸¸µé¾îÁú ¼ö ÀÖ´ÂÁö¸¦
				//È®ÀÎÇØ¾ß ÇÑ´Ù. ÇÏÁö¸¸ set[i-1] <= sumÀÏ ¶§´Â set[i-1]ÀÌ ´õÇØÁø °á°úµµ »ı°¢À» ÇØºÁ¾ß ÇÑ´Ù. µû¶ó¼­ set[i-1]¿¡¼­
				//sum¿¡¼­ set[i-1]ÀÌ ºüÁ³À» ¶§ °ªÀÌ ¸¸µé¾îÁú ¼ö ÀÖ´Ù¸é i¿¡¼­´Â set[i-1]À» ´õÇØ¼­ sumÀ» ¸¸µé ¼ö ÀÖ°Ô µÈ´Ù.
				//±×·±µ¥ ¸¸¾à set[i-1]À» »°À» ¶§µµ sumÀÌ ¸¸µé¾îÁú ¼ö ¾ø´Ù¸é ÀÌ¹Ì ÀÌÀü¿¡¼­ sum-set[i-1]ÀÌ ¸¸µé¾îÁú ¼ö ¾øÀ¸¹Ç·Î
				//sumÀº i¿¡¼­ ¸¸µé¾îÁú ¼ö ¾ø´Ù. ¹İº¹ÀÌ Áõ°¡ÇÏ¸é¼­ DP[1]¿¡ 3ÀÌ true·Î ¼³Á¤µÇ°í DP[2]¿¡ 3,7,10ÀÌ true·Î ¼³Á¤µÇ¹Ç·Î
				//index i¿¡¼­´Â sum-set[i-1]±îÁöÀÇ ¸ğµç °æ¿ìÀÇ ¼ö°¡ true·Î ¹Ù²î¹Ç·Î i´Ü°è¿¡¼­´Â sum-set[i-1]ÀÌ ¸¸µé¾îÁú ¼ö ÀÖ´ÂÁö¸¸
				//È®ÀÎÇÏ¸é µÈ´Ù. iÀÌÀüÀÇ °æ¿ì¸¦ ÀüºÎ ´Ù½Ã °è»êÇØ¼­ sum-set[i-1]ÀÌ °¡´ÉÇÑÁö Ã¼Å©ÇÏÁö ¾Ê¾Æµµ µÈ´Ù.

				//sum >= set[i-1]ÀÏ ¶§´Â ÀÌÀü ¿ø¼Ò±îÁö¸¸ Á¶ÇÕÇßÀ» °æ¿ì¿Í, ÇöÀç ¿ø¼Ò¸¦ Æ÷ÇÔÇÏ¿© Á¶ÇÕÇßÀ» °æ¿ì¸¦ ºñ±³ÇÑ´Ù.
				//¸¸¾à ÀÌÀü ¿ø¼Ò±îÁö Á¶ÇÕÇßÀ» ¶§ °¡´ÉÇÏ´Ù¸é ÇöÀç ¿ø¼Ò´Â °è»êÇÏÁö ¾Ê¾Æµµ µÈ´Ù. ÇÏÁö¸¸ ÀÌÀü ¿ø¼Ò±îÁö Á¶ÇÕÀÌ
				//¾ÈµÈ´Ù¸é sumÀÌ ÇöÀç ¿ø¼Ò±îÁö ´õÇØÁø °ªÀÎÁö¸¦ È®ÀÎÇØ¾ß ÇÑ´Ù. ÀÌ ÄÚµåº¸´Ù ³ªÁß¿¡ ÀÛ¼ºÇÑ 0 - 1 ¹è³¶ ¹®Á¦¸¦
				//µ¿Àû °èÈ¹¹ıÀ¸·Î ÇØ°áÇÑ ÄÚµå¿ÍÀÇ ·ÎÁ÷ÀÌ °ÅÀÇ ¶È°°´Ù. ´Ü, ¹è³¶ ¹®Á¦´Â °¡°İÀ» µûÁ®¾ß ÇÑ´Ù´Â Â÷ÀÌ¸¸ ÀÖ´Ù.
				DP[i][sum] = DP[i - 1][sum]
					|| DP[i - 1][sum - set[i - 1]];
				cout << "DP[" << i << "][" << sum << "](" << DP[i - 1][sum] << ") OR "
					<< "DP[" << i - 1 << "][" << sum << " - " << set[i - 1] << "](" << DP[i - 1][sum - set[i - 1]] << ")"<<endl;

				cout << "DP[" << i << "][" << sum << "] : " << DP[i][sum] << endl;
				cout << endl;
			}
		}
	}

	return DP;
}

vector<string> types =
{
	"BRUTE FORCE",
	"BACKTRACKING",
	"MEMOIZATION",
	"TABULATION"
};

void GetTime(clock_t& timer, string type)
{
	// ÇöÀç ½Ã°£¿¡¼­ timer¸¦ »©¼­ °æ°ú ½Ã°£À» °è»ê
	timer = clock() - timer;

	// È­¸é¿¡ °æ°ú ½Ã°£ Ãâ·Â
	cout << type << " ¹æ¹ı °æ°ú ½Ã°£: ";
	cout << fixed << setprecision(5) << (float)timer / CLOCKS_PER_SEC << endl;

	timer = clock(); // timer¸¦ ÇöÀç ½Ã°£À¸·Î ÃÊ±âÈ­
}

int main()
{
	/*vector<int> set = { 16, 1058, 22, 13, 46, 55, 3, 92, 47, 7,
					   98, 367, 807, 106, 333, 85, 577, 9, 3059 };
	int target = 6800;*/

	vector<int> set = { 3, 7 ,9 };
	int target = 19;
	int tests = 4;

	sort(set.begin(), set.end());

	for (int i = 0; i < tests; i++)
	{
		bool found = false;

		clock_t timer = clock();

		switch (i)
		{
		case 0:
			found = SubsetSum_BruteForce(set, target);
			break;
		case 1:
			found = SubsetSum_Backtracking(set, target, 0);
			break;
		case 2:
		{
			// ¸Ş¸ğÀÌÁ¦ÀÌ¼Ç Å×ÀÌºí ÃÊ±âÈ­
			vector<vector<int>> memo(set.size(), vector<int>(7000, UNKNOWN));

			found = SubsetSum_Memoization(set, target, 0, memo);
			break;
		}
		case 3:
		{
			int total = 0;
			for (auto number : set)
				total += number;

			vector<vector<bool>> DP = SubsetSum_Tabulation(set);
			found = DP[set.size()][target];

			vector<int> subsetSums;
			for (int sum = 1; sum <= total; sum++)
			{
				if (DP[set.size()][sum])
				{
					subsetSums.push_back(sum);
				}
			}

			cout << "´ÙÀ½°ú °°ÀÌ " << subsetSums.size() << "°¡ÁöÀÇ ºÎºĞÁıÇÕÀÇ ÇÕÀÌ °¡´ÉÇÕ´Ï´Ù:" << endl;

			for (auto sum : subsetSums)
				cout << sum << " ";
			cout << endl;

			break;
		}
		}

		if (found)
		{
			cout << "¿ø¼Ò ÇÕÀÌ " << target << "ÀÎ ºÎºĞÁıÇÕÀÌ ÀÖ½À´Ï´Ù." << endl;
		}
		else
		{
			cout << "¿ø¼Ò ÇÕÀÌ " << target << "ÀÎ ºÎºĞÁıÇÕÀÌ ¾ø½À´Ï´Ù." << endl;
		}

		GetTime(timer, types[i]);
		cout << endl;
	}
}