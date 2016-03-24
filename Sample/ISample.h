#ifndef __CRYSTAL_SAMPLE_I_SAMPLE_H__
#define __CRYSTAL_SAMPLE_I_SAMPLE_H__

class ISample
{
public:
	ISample() {
	};

	virtual void setup() = 0;

	virtual ~ISample() {
		cleanup();
	};

	virtual void demonstrate() = 0;

	virtual void cleanup() {};

private:
};

#endif