
#ifndef GAME_H
#define GAME_H

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace DirectX;

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


	// this is the game's start function (only happens once)
	void Initialize();

	// this is the games update function (happens repeatedly)
	void Update();

	// this is how the game renders info to screen (happens repeatedly)
	void Render();
		
protected:

private:
};
#endif
