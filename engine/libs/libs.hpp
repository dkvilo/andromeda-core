#ifndef __ANDROMEDA_LIBS__
#define __ANDROMEDA_LIBS__

#define ASSERT(check, msg, ...)                     \
	{                                               \
		if (!(check))                               \
		{                                           \
			printf("Assertion failed: %s\n", msg);  \
			if (__VA_ARGS__ != NULL)                \
			{                                       \
				printf("\tArg: %s\n", __VA_ARGS__); \
			}                                       \
			exit(1);                                \
		}                                           \
	}

namespace L
{

	namespace Graphics
	{
		namespace OpenGL
		{
			class Legacy;
			class Shader;
			class VertexBuffer;
			class IndexBuffer;
			class Texture;
		};
	}

	namespace Fs
	{
		static inline const char *ReadFileContent(const char *path);
	}
	namespace Math
	{
		struct Proxima;

		static const double PI = 3.1415926f;
		static const double TWO_PI = L::Math::PI * 2.0;
		static inline float Lerp(const float &a, const float &b, const float &t);
		static inline float InvLerp(const float &a, const float &b, const float &v);
		static inline float Remap(const float &i_max, const float &i_min, const float &o_min, const float &o_max, const float &v);
		static inline float RnR(const float &min, const float &max);
	}

	namespace Util
	{
		class UUID;
	}

}

#endif // __ANDROMEDA_LIBS__