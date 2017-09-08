#define N 4

int temp[4], bucket[5040][4], cnt;
bool use[10];

typedef struct {
	int strike;
	int ball;
} Result;

// API
extern Result query(int guess[]);

void dfs(int index)
{
	if (index == 4)
	{
		for (int i = 0; i < 4; i++) bucket[cnt][i] = temp[i];
		cnt++;
		return;
	}
	for (int i = 0; i < 10; i++)
	{
		if (!use[i])
		{
			use[i] = true;
			temp[index] = i;
			dfs(index + 1);
			use[i] = false;
		}
	}
}

Result process(int assume[], int test[])
{
	Result ret;
	ret.strike = 0;
	ret.ball = 0;
	bool assume_use[10] = {}, test_use[10] = {};
	for (int i = 0; i < 4; i++)
	{
		if (assume[i] == test[i]) ret.strike++;
		else
		{
			assume_use[assume[i]] = true;
			test_use[test[i]] = true;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (assume_use[i] == true && test_use[i] == true) ret.ball++;
	}
	return ret;
}

void doUserImplementation(int guess[]) {
	bool isImpossible[5040] = {};
	int remain = 5040;
	if (cnt == 0) dfs(0);
	while (true)
	{
		for (int i = 0; i < 5040; i++)
		{
			if (isImpossible[i]) continue;
			for (int j = 0; j < 4; j++) guess[j] = bucket[i][j];
			break;
		}
		if (remain == 1) return;
		Result query_result = query(guess);
		for (int i = 0; i < 5040; i++)
		{
			if (isImpossible[i]) continue;
			Result process_result = process(bucket[i], guess);
			if (process_result.strike != query_result.strike || process_result.ball != query_result.ball)
			{
				isImpossible[i] = true;
				remain--;
			}
		}
	}
}