
#ifndef GAME_H
#define GAME_H

#include <fstream>

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace DirectX;

struct Vertex 
{
	float x, y, z; // vertext positions
};

class ShapesOfCombat
{
public:
	/*
	1. A COM object is a class or set of classes controlled by an interface. When we create an instance
	of a COM object, we don't create it directly, we create an interface, and access the object through that.

	2. Interfaces are easy to identify, because they typically start with an 'I', such as 'IMyCOMObject'.

	3. Under the hood, COM can get quite complex and be a real pain in the ass. Fortunately COM makes use
	of something called a smart pointer, which is really just a special class that understands COM and 
	takes care of the whole mess for us.
	*/
	ComPtr<ID3D11Device1> dev;              // the device interface
	ComPtr<ID3D11DeviceContext1> devcon;    // the device context interface
	ComPtr<IDXGISwapChain1> swapchain;      // the swap chain interface
	ComPtr<ID3D11Buffer> vertexbuffer;    // 

	// A special COM object exists for every type of shader. For the vertex and pixel shaders, the interfaces 
	// to these objects are ID3D11VertexShader and ID3D11PixelShader.
	ComPtr<ID3D11VertexShader> vertexshader;
	ComPtr<ID3D11PixelShader> pixelshader;

	ComPtr<ID3D11InputLayout> inputLayout;

	// you must establish the render target. This is a simple COM object that maintains a location in
	// video memory for you to render into.
	ComPtr<ID3D11RenderTargetView> renderTarget; 

	// this is the game's start function (only happens once)
	void Initialize();

	void InitGraphics();

	// this function initializes the GPU settings and prepares it for rendering
	void InitPipeline();

	// this is the games update function (happens repeatedly)
	void Update();

	// this is how the game renders info to screen (happens repeatedly)
	void Render();
		
protected:

private:
};

#endif
