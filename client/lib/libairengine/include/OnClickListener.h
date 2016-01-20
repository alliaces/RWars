#ifndef ONCLICKLISTENER_H_
#define ONCLICKLISTENER_H_

class OnClickListener
{
public:
	virtual ~OnClickListener() {}
	virtual void OnClick(void *) = 0;
};

#endif
