#include <iostream>
#include <cstdlib>
using namespace std;


enum enQuestionLevel {EasyLevel = 1, MedLevel = 2, HardLevel = 3, MixLevel = 4};

enum enOperationType {Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5};

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions = 1;
	do
	{
		cout << "How many question do you want to answer? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 1;
	do
	{
		cout << "Enter Questions Level [1]Easy, [2]Med, [3]Hard, [4]Mix? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel) QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType= 1;
	do
	{
		cout << "Enter Operation Type [1]Add, [2]Sub, [3]Mult, [4]Div, [5]Mix? ";
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Sub:
		return Number1 - Number2;
		break;
	case enOperationType::Mult:
		return Number1 * Number2;
		break;
	case enOperationType::Div:
		return Number1 / Number2;
		break;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::MixLevel)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.QuestionLevel = QuestionLevel;
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		return Question;

	case enQuestionLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.QuestionLevel = QuestionLevel;
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		return Question;

	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.QuestionLevel = QuestionLevel;
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		return Question;
	}

	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (int Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
}

string OperationTypeTText(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Sub:
		return "-";
		break;
	case enOperationType::Mult:
		return "*";
		break;
	case enOperationType::Div:
		return "/";
		break;
	default:
		return "+";
	}
}

void PrintTheQuestion(stQuizz& Quizz, int QuestionNumber)
{
	cout << "\n Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << OperationTypeTText(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
	cout << "--------\n";
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void SetScreenColor(bool AnswerResult)
{
	if (AnswerResult)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, int QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-(\n";
		cout << "The Right Answer is ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-)\n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

		
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool isPass)
{
	if (isPass)
		return "PASS :-)";
	else
		return "FAIL :-(";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string arrQuestionLevel[4] = {"Easy", "Med", "Hard", "Mix"};
	return arrQuestionLevel[QuestionLevel - 1];
}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
		break;
	case enOperationType::Sub:
		return "-";
		break;
	case enOperationType::Div:
		return "/";
		break;
	case enOperationType::Mult:
		return "*";
		break;
	default:
		return "Mix";
	}
}

void PrintQuizzResults(stQuizz& Quizz)
{
	cout << "\n-------------------------------------------\n\n";
	cout << "Final Result: " << GetFinalResultsText(Quizz.isPass);
	cout << "\n-------------------------------------------\n\n";
	cout << "Number Of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level     : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "--------------------------------------------\n";

}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "\nDo you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();


    return 0;
}
