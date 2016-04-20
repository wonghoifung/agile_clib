#include <stdbool.h>
#include "cdplayer.h"

#if 0
bool playflag;
bool pauseflag;

int cmdIdx = 0;
const char* buf[10];

void initialize() {
	cmdIdx = 0;
	playflag = false;
	pauseflag = false;
}

void onEvent(EventCode ec) {
	switch (ec)
	{
	case EV_STOP:
		if (playflag || pauseflag) stopPlayer();
		break;

	case EV_PLAY_PAUSE:
		if (playflag) pausePlayer();
		else if (pauseflag) resumePlayer();
		else startPlayer();
		break;

	default:
		break;
	}
}

void stopPlayer() {
	pauseflag = false;
	playflag = false;
	buf[cmdIdx++] = "stop";
}

void pausePlayer() {
	pauseflag = true;
	playflag = false;
	buf[cmdIdx++] = "pause";
}

void resumePlayer() {
	pauseflag = false;
	playflag = true;
	buf[cmdIdx++] = "resume";
}

void startPlayer() {
	pauseflag = false;
	playflag = true;
	buf[cmdIdx++] = "start";
}
#else
static const State* pCurrentState;

static const State* ignore(const State* pThis);
static const State* startPlay(const State* pThis);
static const State* stopPlay(const State* pThis);
static const State* pausePlay(const State* pThis);
static const State* resumePlay(const State* pThis);

const State IDLE = { ignore, startPlay };
const State PLAY = { stopPlay, pausePlay };
const State PAUSE = { stopPlay, resumePlay };

int cmdIdx = 0;
const char* buf[10];

void initialize() {
	cmdIdx = 0;
	pCurrentState = &IDLE;
}

void onStop() {
	pCurrentState = pCurrentState->stop(pCurrentState);
}

void onPlayOrPause() {
	pCurrentState = pCurrentState->playOrPause(pCurrentState);
}

static const State* ignore(const State* pThis) {
	return pCurrentState;
}

static const State* stopPlay(const State* pThis) {
	buf[cmdIdx++] = "stop";
	return &IDLE;
}

static const State* pausePlay(const State* pThis) {
	buf[cmdIdx++] = "pause";
	return &PAUSE;
}

static const State* resumePlay(const State* pThis) {
	buf[cmdIdx++] = "resume";
	return &PLAY;
}

static const State* startPlay(const State* pThis) {
	buf[cmdIdx++] = "start";
	return &PLAY;
}

#endif
