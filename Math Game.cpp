#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

enum enLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, mix = 5 };

struct strQuestionInfo
{
	int questionNumber = 0;
	enOperationType operationType = enOperationType::Add;
	enLevel level = enLevel::Easy;
	int passCount = 0, failCount = 0;
	string operationName = "", levelName = "";
	char OperationType = ' ';
	int number1 = 0, number2 = 0, numberMix = 0;

};

int ReadQuestionNumber(strQuestionInfo& questionInfo)
{
	cout << "How many question you want to answer ? ";
	cin >> questionInfo.questionNumber;
	return questionInfo.questionNumber;
}

enOperationType ReadOperationType(strQuestionInfo& questionInfo)
{
	short operationType = 0;
	cout << "Enter Operation Type [1]Add,[2]Sub,[3]Mul,[4]Div,[5]Mix ? ";
	cin >> operationType;
	return (enOperationType)operationType;
}

enLevel ReadLevel(strQuestionInfo& questionInfo)
{
	short level = 0;
	cout << "Enter question level [1]Easy,[2]Med,[3]Hard,[4]Mix ? ";
	cin >> level;
	return (enLevel)level;
}

int RandomNumber(int from, int to)
{
	int number = rand() % (to - from + 1) + from;

	return number;
}

void FillQuestionInfo(strQuestionInfo& questionInfo)
{
	questionInfo.questionNumber = ReadQuestionNumber(questionInfo);
	questionInfo.level = ReadLevel(questionInfo);
	questionInfo.operationType = ReadOperationType(questionInfo);

}

void GenerateNumber(strQuestionInfo& questionInfo)
{
	switch (questionInfo.level)
	{
	case enLevel::Easy:
		questionInfo.number1 = RandomNumber(1, 10);
		questionInfo.number2 = RandomNumber(1, 10);
		questionInfo.levelName = "Easy";
		break;
	case enLevel::Med:
		questionInfo.number1 = RandomNumber(10, 50);
		questionInfo.number2 = RandomNumber(10, 50);
		questionInfo.levelName = "Med";
		break;
	case enLevel::Hard:
		questionInfo.number1 = RandomNumber(50, 100);
		questionInfo.number2 = RandomNumber(50, 100);
		questionInfo.levelName = "Hard";
		break;
	case enLevel::Mix:
		questionInfo.number1 = RandomNumber(1, 100);
		questionInfo.number2 = RandomNumber(1, 100);
		questionInfo.levelName = "Mix";
		break;
	}
}

char MixOperationType(strQuestionInfo& questionInfo)
{
	questionInfo.numberMix = RandomNumber(1, 4);
	if (questionInfo.numberMix == 1)
	{
		return  '+';
	}
	else if (questionInfo.numberMix == 2)
	{
		return  '-';
	}
	else if (questionInfo.numberMix == 3)
	{
		return '*';
	}
	else if (questionInfo.numberMix == 4)
	{
		return  '/';
	}
	return ' '; // Default return to avoid undefined behavior
}
void GenerateOperationType(strQuestionInfo& questionInfo)
{
	switch (questionInfo.operationType)
	{
	case enOperationType::Add:
		questionInfo.OperationType = '+';
		questionInfo.operationName = "+";
		break;
	case enOperationType::Sub:
		questionInfo.OperationType = '-';
		questionInfo.operationName = "-";
		break;
	case enOperationType::Mul:
		questionInfo.OperationType = '*';
		questionInfo.operationName = "*";
		break;
	case enOperationType::Div:
		questionInfo.OperationType = '/';
		questionInfo.operationName = "/";
		break;
	case enOperationType::mix:
		questionInfo.operationName = "Mix";
		questionInfo.OperationType = MixOperationType(questionInfo);
		break;
	}
}
int CalculateQuestion(strQuestionInfo& questionInfo)
{
	switch (questionInfo.OperationType) {
	case'+':
		return (questionInfo.number1 + questionInfo.number2);
		break;
	case '-':
		return (questionInfo.number1 - questionInfo.number2);
		break;
	case'/':
		if (questionInfo.number2 > 0)
		{
			return round(questionInfo.number1 / questionInfo.number2);
			break;
		}
	case'*':
		return (questionInfo.number1 * questionInfo.number2);
		break;
	}
}
void GenerateQuestion(strQuestionInfo& questionInfo)
{

	GenerateNumber(questionInfo);
	GenerateOperationType(questionInfo);
	cout << questionInfo.number1 << endl;
	cout << questionInfo.number2 << "  " << questionInfo.OperationType << endl;
	cout << "___________________________\n";

}
bool CheckAnswer(strQuestionInfo& questionInfo)
{
	int answer = 0;
	cin >> answer;
	if (answer == CalculateQuestion(questionInfo))
	{
		cout << "\nRight Answer:-)\n";
		questionInfo.passCount++;
		return true;
	}
	else
	{
		cout << "\nWrong Right Answer:-(\n";
		cout << "The right Answer is: " << CalculateQuestion(questionInfo) << endl;
		questionInfo.failCount++;
		return false;
	}

}

void ScreenColor(bool Result)
{
	if (Result == true)
	{
		system("color 2F");
	}
	else
	{
		cout << "\a";
		system("color 4F");
	}

}

void FinalResult(strQuestionInfo questionInfo)
{
	if (questionInfo.passCount >= questionInfo.failCount)
	{
		ScreenColor(true);
		cout << "\n_____________________________________\n\n";
		cout << "  Final Result is Pass:-)\n";
		cout << "\n_____________________________________\n";
	}
	else
	{
		ScreenColor(false);
		cout << "\n_____________________________________\n\n";
		cout << "  Final Result is Fail:-(\n";
		cout << "\n_____________________________________\n\n";
	}
}
void PrintResult(strQuestionInfo questionInfo)
{
	cout << "Number of Question     : " << questionInfo.questionNumber << endl;
	cout << "Question level         : " << questionInfo.levelName << endl;
	cout << "OpType                 : " << questionInfo.operationName << endl;
	cout << "Number of right answer : " << questionInfo.passCount << endl;
	cout << "Number of wrong answer : " << questionInfo.failCount << endl;
	cout << "\n_____________________________________\n\n";
}

void QuestionGame(strQuestionInfo& questionInfo)
{
	FillQuestionInfo(questionInfo);
	for (int questionNumber = 1; questionNumber <= questionInfo.questionNumber; questionNumber++)
	{
		cout << "Question [" << questionNumber << "/" << questionInfo.questionNumber << "]\n";
		GenerateQuestion(questionInfo);
		ScreenColor(CheckAnswer(questionInfo));
		cout << endl << endl;
	}
	FinalResult(questionInfo);
	PrintResult(questionInfo);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char playAgain = 'Y';
	do
	{
		strQuestionInfo questionInfo;
		ResetScreen();
		QuestionGame(questionInfo);
		cout << "\nDo you want to play again? Y/N?";
		cin >> playAgain;
	} while (playAgain == 'Y' || playAgain == 'y');

}

int main()
{

	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}