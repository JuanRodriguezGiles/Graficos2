#include <time.h>	// class needs this inclusion


//////////////////////////////////////////
// class declaration:


class Timer {
public:
	Timer();
	void           start();
	void           stop();
	void           reset();
	bool           isRunning();
	float  getTime();
	bool           isOver(unsigned long seconds);
private:
	bool           resetted;
	bool           running;
	unsigned long  beg;
	unsigned long  end;
};