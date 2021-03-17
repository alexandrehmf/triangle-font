typedef struct 
{
  float x, y;
} vec2d;

vec2d mkvec(float x, float y)
{
	vec2d result;
	result.x = x;
	result.y = y;
	return result;
}

vec2d vpv2d(vec2d vec1, vec2d vec2)
{
	vec2d result;
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return result;
}

vec2d scaleVec(vec2d vec, float fac)
{
	vec2d result;
	result.x = vec.x * fac;
	result.y = vec.y * fac;
	return result;
}