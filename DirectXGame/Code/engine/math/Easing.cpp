#include "Easing.h"

XMFLOAT3 Easing::lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float time)
{
	return start * (1.0f - time) + end * time;
}

XMFLOAT3 Easing::easeIn(const XMFLOAT3& start, const XMFLOAT3& end, const float time)
{
	float t = time * time * time;
	return start * (1.0f - t) + end * t;
}

XMFLOAT3 Easing::easeOut(const XMFLOAT3& start, const XMFLOAT3& end, const float time)
{
	float t = time * (2 - time);
	return start * (1.0f - t) + end * t;
}

XMFLOAT3 Easing::easeInOut(const XMFLOAT3& start, const XMFLOAT3& end, const float time)
{
	float t = time * time * (3 - 2 * time);
	return start * (1.0f - t) + end * t;
}

XMFLOAT2 Easing::lerp(const XMFLOAT2& start, const XMFLOAT2& end, const float time)
{
	return start * (1.0f - time) + end * time;
}

XMFLOAT2 Easing::easeIn(const XMFLOAT2& start, const XMFLOAT2& end, const float time)
{
	float t = time * time * time;
	return start * (1.0f - t) + end * t;
}

XMFLOAT2 Easing::easeOut(const XMFLOAT2& start, const XMFLOAT2& end, const float time)
{
	float t = time * (2 - time);
	return start * (1.0f - t) + end * t;
}

XMFLOAT2 Easing::easeInOut(const XMFLOAT2& start, const XMFLOAT2& end, const float time)
{
	float t = time * time * (3 - 2 * time);
	return start * (1.0f - t) + end * t;
}
