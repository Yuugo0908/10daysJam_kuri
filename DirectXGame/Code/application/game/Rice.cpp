#include "Rice.h"

Rice::Rice()
{
}

Rice::~Rice()
{
}

Rice* Rice::GetInstance()
{
	static Rice instance;
	return &instance;
}

void Rice::Update()
{
}

void Rice::Draw()
{
}
