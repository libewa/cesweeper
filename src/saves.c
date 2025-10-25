#include "saves.h"
#include <fileioc.h>

const char fileName[] = "MSSCORES";

bool loadScores(void) {
    unsigned char handle = ti_Open(fileName, "r");
    if (handle == 0) {
        return false; // File doesn't exist or couldn't be opened
    }
    ti_Read(scores, sizeof(ScoreEntry), 5, handle);
    ti_Close(handle);
    return true;
}

bool saveScores(void) {
    unsigned char handle = ti_Open(fileName, "w");
    ti_SetArchiveStatus(false, handle);
    if (handle == 0) {
        return false; // Failed to open file for writing
    }
    ti_Write(scores, sizeof(ScoreEntry), 5, handle);
    ti_Close(handle);
    ti_SetArchiveStatus(true, handle);
    return true;
}

void saveCurrentScore(void) {
    int pos = -1;
    for (int i = 0; i < 5; i++) {
        if (scores[i].time == 0 || playerScore.time < scores[i].time) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        /* Not a high score */
        return;
    }

    /* Shift lower scores down to make room (from the bottom up). */
    for (int i = 4; i > pos; i--) {
        scores[i] = scores[i - 1];
    }

    /* Insert new score */
    scores[pos] = playerScore;
}
