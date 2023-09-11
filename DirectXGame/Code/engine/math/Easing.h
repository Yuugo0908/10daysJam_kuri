#pragma once
#include "Operator.h"
#include <stdlib.h>
#include <time.h>
class Easing
{
public:
	static XMFLOAT3 lerp		(const XMFLOAT3& start, const XMFLOAT3& end, const float time);
	static XMFLOAT3 easeIn		(const XMFLOAT3& start, const XMFLOAT3& end, const float time);
	static XMFLOAT3 easeOut		(const XMFLOAT3& start, const XMFLOAT3& end, const float time);
	static XMFLOAT3 easeInOut	(const XMFLOAT3& start, const XMFLOAT3& end, const float time);

	static XMFLOAT2 lerp		(const XMFLOAT2& start, const XMFLOAT2& end, const float time);
	static XMFLOAT2 easeIn		(const XMFLOAT2& start, const XMFLOAT2& end, const float time);
	static XMFLOAT2 easeOut		(const XMFLOAT2& start, const XMFLOAT2& end, const float time);
	static XMFLOAT2 easeInOut	(const XMFLOAT2& start, const XMFLOAT2& end, const float time);
};
