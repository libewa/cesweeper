#pragma once
#include "globals.h"

bool loadScores(ScoreEntry scores[5]);
bool saveScores(const ScoreEntry scores[5]);
void saveCurrentScore(void);