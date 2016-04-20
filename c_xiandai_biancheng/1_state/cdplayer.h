#ifndef cdplayer_header
#define cdplayer_header

#ifdef __cplusplus
extern "C" {
#endif

#if 0
	typedef enum {
		EV_STOP,
		EV_PLAY_PAUSE
	} EventCode;

	void initialize();
	void onEvent(EventCode ec);
	void stopPlayer();
	void pausePlayer();
	void resumePlayer();
	void startPlayer();

	// test
	extern int cmdIdx;
	extern const char* buf[10];
#else
	typedef struct _State {
		const struct _State* (*stop)(const struct _State* pThis);
		const struct _State* (*playOrPause)(const struct _State* pThis);
	} State;

	void initialize();
	void onStop();
	void onPlayOrPause();

	// test
	extern int cmdIdx;
	extern const char* buf[10];
#endif

#ifdef __cplusplus
}
#endif

#endif
