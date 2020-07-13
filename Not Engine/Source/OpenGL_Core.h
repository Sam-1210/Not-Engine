#pragma once

namespace OpenGL
{
	struct Enums
	{
		static int ColorBit;
		static int DepthBit;
	};
	class Core
	{
	private:
		static bool Initialized;
	public:
		static const char* GetVendor();  
		static const char* GetRenderer();
		static const char* GetVersion(); 
		static void LoadGL();
		static void ClearColor(float r, float g, float b, float a);
		static void ClearBufferBits(int bits);
		static void EnableWireframeMode();
		static void EnableSoildMode();
		static void SetBlending(bool ToogleBlend);
		static void SetDepthTest(bool ToogleDepthTest);
		static void SetViewportSize(int x, int y, int w, int h);
	};
}
