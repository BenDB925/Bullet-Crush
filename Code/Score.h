#include <vector>

class Score
{
public:
	static Score& Instance();
	void Init();
	void UpdateScores();
	void SortHighScoreTable();

	int currentScore;
	std::string currentScoreText;
	std::vector<std::string> highScoresText;


private:
	Score();
	std::vector<int> highScores;
};