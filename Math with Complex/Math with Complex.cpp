#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

enum enQuestionLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4, Complex = 5 };

enum enOperationType { Sum = 1, Sub = 2, Mul = 3, Div = 4, mix = 5 };

struct stQuestion
{
	int NumberOfQuestion = 0;
	int Num1 = 0, Num2 = 0;
	int RightAnswer = 0;
	int PlayerAnswer = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	bool IsCorrect = 0;

	int NumOneRealComplex = 0, NumTwoRealComplex = 0;
	int NumOneIMComplex = 0, NumTwoIMComplex = 0;
	int PlayerRealSolComplex = 0, Magnitude = 0;
	int PlayerPhaseSolComplex = 0, Phase = 0;
};

struct stQuiz
{
	stQuestion QuestionList[100];
	int NumberOfQuestion = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int NumberOfRightAnswer = 0, NumberOfWrongAnswer = 0;
	bool IsPass = 0;

};

int Random(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

int ReadNumber()
{
	int Number = 0;

	cin >> Number;
	return Number;
}

int NumberOfQuestion()
{
	int Number = 0;
	do
	{
		cout << "Enter Number Of Question 1 to 100 : ";
		cin >> Number;


	} while (Number < 1 || Number>100);
	return Number;


}

enQuestionLevel QuestionLevel()
{
	int Number = 0;
	do
	{
		cout << "Select The Level Of Question 1[Easy], 2[Mid], 3[Hard], 4[Mix], 5[Complex] : ";
		cin >> Number;

	} while (Number < 1 || Number >5);

	return (enQuestionLevel)Number;

}

enOperationType OperationType()
{
	int Number = 0;
	do
	{


		cout << "Select The Operation Type 1[Sum], 2[Sub], 3[Mul], 4[Div], 5[Mix]  : ";
		cin >> Number;

	} while (Number < 1 || Number >5);

	return (enOperationType)Number;


}

int GetAnswer(int Num1, int Num2, enOperationType OperationType)
{
	switch (OperationType)
	{

	case enOperationType::Sum:
		return Num1 + Num2;
		break;
	case enOperationType::Sub:
		return  Num1 - Num2;
		break;
	case enOperationType::Mul:
		return  Num1 * Num2;
		break;
	default:
		return  Num1 / Num2;
		break;

	}



}

void RealPartSolve(stQuestion& Question, enOperationType OperationType)
{
	const float PI = 3.14;
	int Real = 0;
	int Im = 0;

	switch (OperationType)
	{
	case enOperationType::Sum:
	{
		Real = Question.NumOneRealComplex + Question.NumTwoRealComplex;
		Im = Question.NumOneIMComplex + Question.NumTwoIMComplex;

		Question.Magnitude = sqrt(pow(Real, 2.0) + pow(Im, 2.0));
		float PhaseINRad = atan2((float)Im, (float)Real);
		Question.Phase = PhaseINRad * 180.0 / PI;
		break;
	}

	case enOperationType::Sub:
	{
		Real = Question.NumOneRealComplex - Question.NumTwoRealComplex;
		Im = Question.NumOneIMComplex - Question.NumTwoIMComplex;

		Question.Magnitude = sqrt(pow(Real, 2.0) + pow(Im, 2.0));
		float PhaseINRad = atan2((float)Im, (float)Real);
		Question.Phase = PhaseINRad * 180.0 / PI;
		break;
	}

	case enOperationType::Mul:
	{
		float a = Question.NumOneRealComplex;
		float b = Question.NumOneIMComplex;
		float c = Question.NumTwoRealComplex;
		float d = Question.NumTwoIMComplex;

		
		Real = a * c - b * d;
		Im = a * d + b * c;

		Question.Magnitude = sqrt(pow(Real, 2.0) + pow(Im, 2.0));
		float PhaseINRad = atan2((float)Im, (float)Real);
		Question.Phase = PhaseINRad * 180.0 / PI;
		break;
	}

	default:
	{
		float a = (float)Question.NumOneRealComplex;
		float b = (float)Question.NumOneIMComplex;
		float c = (float)Question.NumTwoRealComplex;
		float d = (float)Question.NumTwoIMComplex;

		float denominator = c * c + d * d;

		// ? ???? ?????? float
		float Real = (a * c + b * d) / denominator;
		float Im = (b * c - a * d) / denominator;

		// ? ???? ??????? ??????
		Question.Magnitude = sqrt(pow(Real, 2.0) + pow(Im, 2.0));
		Question.Phase = atan2(Im, Real) * 180.0 / PI;

		break;
	}
	}
}

stQuestion GeneratOneQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;
	if (QuestionLevel == 4)
	{
		QuestionLevel = (enQuestionLevel)Random(1, 3);
	}


	if (OperationType == 5)
	{
		OperationType = (enOperationType)Random(1, 4);
	}


	Question.OperationType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Question.Num1 = Random(1, 10);
		Question.Num2 = Random(1, 10);
		Question.QuestionLevel = QuestionLevel;
		Question.RightAnswer = GetAnswer(Question.Num1, Question.Num2, OperationType);
		return Question;

	case enQuestionLevel::Mid:
		Question.Num1 = Random(10, 50);
		Question.Num2 = Random(10, 50);
		Question.QuestionLevel = QuestionLevel;
		Question.RightAnswer = GetAnswer(Question.Num1, Question.Num2, OperationType);
		return Question;

	case enQuestionLevel::Complex:
		Question.NumOneRealComplex = Random(-50, 50);
		Question.NumTwoRealComplex = Random(-50, 50);
		Question.NumOneIMComplex = Random(-50, 50);
		Question.NumTwoIMComplex = Random(-50, 50);
		Question.QuestionLevel = QuestionLevel;
		RealPartSolve(Question, OperationType);
		return Question;

	default:
		Question.Num1 = Random(50, 100);
		Question.Num2 = Random(50, 100);
		Question.QuestionLevel = QuestionLevel;
		Question.RightAnswer = GetAnswer(Question.Num1, Question.Num2, OperationType);
		return Question;
	}
}

void GenerateExam(stQuiz& Quiz)
{
	for (int Question = 0; Question < Quiz.NumberOfQuestion; Question++)
		Quiz.QuestionList[Question] = GeneratOneQuestion(Quiz.QuestionLevel, Quiz.OperationType);

}

string GetOperationTypeWord(enOperationType OperationType)
{
	string arrOPType[5] = { "+", "-" , "*" , "/", "Mix" };
	return arrOPType[OperationType - 1];
}

void PrintQuestion(stQuiz& Quiz, int QuestionNumber)
{
	cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestion << "]\n";
	if (Quiz.QuestionLevel == enQuestionLevel::Complex)
	{
		cout << "" << Quiz.QuestionList[QuestionNumber].NumOneRealComplex << " + " << Quiz.QuestionList[QuestionNumber].NumOneIMComplex << "i " << endl;
		cout << "" << Quiz.QuestionList[QuestionNumber].NumTwoRealComplex << " + " << Quiz.QuestionList[QuestionNumber].NumTwoIMComplex << "i " << GetOperationTypeWord(Quiz.QuestionList[QuestionNumber].OperationType);
		cout << "\n___________\n";


	}
	else
	{
		cout << Quiz.QuestionList[QuestionNumber].Num1 << endl;
		cout << Quiz.QuestionList[QuestionNumber].Num2 << " " << GetOperationTypeWord(Quiz.QuestionList[QuestionNumber].OperationType);
		cout << "\n___________\n";
	}




}

void SetColorforRound(stQuiz Quiz, int QuestionNumber)
{
	if (Quiz.QuestionList[QuestionNumber].IsCorrect == true)
		system("color 2F");

	else
	{
		cout << "\a";
		system("color 4F");
	}

}

void IsThePlayerAnswerCorrect(stQuiz& Quiz, int QuestionNumber)
{
	if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].RightAnswer)
	{
		Quiz.QuestionList[QuestionNumber].IsCorrect = false;
		Quiz.NumberOfWrongAnswer++;
		cout << "Wrong Answer\n";
		cout << "The Right Answer Is : " << Quiz.QuestionList[QuestionNumber].RightAnswer << endl << endl;
	}
	else
	{
		Quiz.QuestionList[QuestionNumber].IsCorrect = true;
		Quiz.NumberOfRightAnswer++;
		cout << "RightAnswer\n\n";
	}
	SetColorforRound(Quiz, QuestionNumber);
}

void SetColorforComplexRound(stQuiz Quiz, int QuestionNumber)
{
	if (Quiz.QuestionList[QuestionNumber].IsCorrect == true)
		system("color 2F");

	else if ((Quiz.QuestionList[QuestionNumber].Magnitude != Quiz.QuestionList[QuestionNumber].PlayerRealSolComplex) && (Quiz.QuestionList[QuestionNumber].Phase != Quiz.QuestionList[QuestionNumber].PlayerPhaseSolComplex))
	{
		cout << "\a";
		system("color 4F");
	}

	else
		system("color 6F");
}

void IsTheComplexPlayerAnswerCorrect(stQuiz& Quiz, int QuestionNumber)
{
	int AnswerForRealPart = Quiz.QuestionList[QuestionNumber].Magnitude;
	int PlayerRealPart = Quiz.QuestionList[QuestionNumber].PlayerRealSolComplex;
	int AnswerForImaginaryPart = Quiz.QuestionList[QuestionNumber].Phase;
	int PlayerImaginaryPart = Quiz.QuestionList[QuestionNumber].PlayerPhaseSolComplex;

	if ((AnswerForRealPart != PlayerRealPart) && (AnswerForImaginaryPart != PlayerImaginaryPart))
	{
		Quiz.QuestionList[QuestionNumber].IsCorrect = false;
		Quiz.NumberOfWrongAnswer++;
		cout << "Wrong Answer\n";
		cout << "The Right Answer of Real Part is : " << AnswerForRealPart << endl << endl;
		cout << "The Right Answer Of Im Part is : " << AnswerForImaginaryPart << endl << endl;
	}

	else if ((AnswerForRealPart != PlayerRealPart) && (AnswerForImaginaryPart == PlayerImaginaryPart))
	{
		Quiz.QuestionList[QuestionNumber].IsCorrect = false;
		Quiz.NumberOfWrongAnswer++;
		cout << "Wrong Answer (The Imaginary Part is Right)\n";
		cout << "The Right Answer of Real Part is : " << AnswerForRealPart << endl << endl;
	}

	else if ((AnswerForRealPart == PlayerRealPart) && (AnswerForImaginaryPart != PlayerImaginaryPart))
	{
		Quiz.QuestionList[QuestionNumber].IsCorrect = false;
		Quiz.NumberOfWrongAnswer++;
		cout << "Wrong Answer (The Real Part is Right)\n";
		cout << "The Right Answer of Im Part is : " << AnswerForImaginaryPart << endl << endl;
	}
	else
	{
		Quiz.QuestionList[QuestionNumber].IsCorrect = true;
		Quiz.NumberOfRightAnswer++;
		cout << "Right Answer\n";

	}
	SetColorforComplexRound(Quiz, QuestionNumber);
}

void AskIsCorrect(stQuiz& Quiz)
{
	for (int Question = 0; Question < Quiz.NumberOfQuestion; Question++)
	{
		PrintQuestion(Quiz, Question);
		if (Quiz.QuestionLevel == enQuestionLevel::Complex)
		{
			cout << "Real Part : ";
			Quiz.QuestionList[Question].PlayerRealSolComplex = ReadNumber();
			cout << "Phase Part : ";
			Quiz.QuestionList[Question].PlayerPhaseSolComplex = ReadNumber();
			IsTheComplexPlayerAnswerCorrect(Quiz, Question);
		}
		else
		{

			Quiz.QuestionList[Question].PlayerAnswer = ReadNumber();
			IsThePlayerAnswerCorrect(Quiz, Question);
		}


	}
	Quiz.IsPass = (Quiz.NumberOfRightAnswer >= Quiz.NumberOfWrongAnswer);
}

string Tape(int NumberOfTap)
{
	for (int i = 0; i < NumberOfTap; i++)
	{
		cout << "\t";
	}
	return "";
}

void ShowGameOver(stQuiz Quiz)
{

	cout << "\n";
	cout << Tape(2) << "_____________________________________________________________\n\n";

	if (Quiz.IsPass == true)
	{
		cout << Tape(2) << "                       YouPass :)                           \n";
	}

	else
	{
		cout << Tape(2) << "                       YouFail :(                           \n";
	}
	cout << Tape(2) << "_____________________________________________________________\n";


}

string GetQuestionLevelName(enQuestionLevel QuestionLevel)
{
	string arrLevel[5] = { "[Easy]", "[Mid]", "[Hard]", "[Mix]", "[Complex]" };
	return arrLevel[QuestionLevel - 1];

}

void PrintFindalResult(stQuiz Quiz)
{
	ShowGameOver(Quiz);
	cout << Tape(2) << "Number Of Question     : " << Quiz.NumberOfQuestion << endl;
	cout << Tape(2) << "Question Level         : " << GetQuestionLevelName(Quiz.QuestionLevel) << endl;
	cout << Tape(2) << "Operation Type         : " << GetOperationTypeWord(Quiz.OperationType) << endl;
	cout << Tape(2) << "Number Of Right Answer : " << Quiz.NumberOfRightAnswer << endl;
	cout << Tape(2) << "Number Of Wrong Answer : " << Quiz.NumberOfWrongAnswer << endl;



}

void PlayGame()
{
	stQuiz Quiz;
	Quiz.NumberOfQuestion = NumberOfQuestion();
	Quiz.QuestionLevel = QuestionLevel();
	Quiz.OperationType = OperationType();
	GenerateExam(Quiz);
	AskIsCorrect(Quiz);
	PrintFindalResult(Quiz);

}

void Reset()
{
	system("color 0F");
	system("cls");

}

void Play()
{
	char PlayAgain = 'Y';
	do {

		Reset();
		PlayGame();
		cout << "\n\t\tDo you Wont Play Again Y(yes) N(No) : ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');




}

int main()
{
	srand((unsigned)time(NULL));
	Play();

	return 0;
}