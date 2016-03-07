#ifndef __CRYSTAL_SAMPLE_I_SAMPLE_H__
#define __CRYSTAL_SAMPLE_I_SAMPLE_H__

class ISample
{
public:
	ISample() {};

	virtual ~ISample() {};

	virtual void setup() = 0;

	virtual void demonstrate() = 0;

	virtual void cleanup() = 0;
};

#endif