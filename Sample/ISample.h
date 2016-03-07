#ifndef __CRYSTAL_SAMPLE_I_SAMPLE_H__
#define __CRYSTAL_SAMPLE_I_SAMPLE_H__

class ISample
{
public:
	ISample() {
	};

	virtual void setup() = 0;

	virtual ~ISample() {
	};

	virtual void demonstrate() = 0;

private:
};

#endif