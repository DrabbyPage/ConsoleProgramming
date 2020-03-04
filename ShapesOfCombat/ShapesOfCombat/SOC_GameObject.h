

#ifndef SOC_GAMEOBJECT_H
#define	SOC_GAMEOBJECT_H

#include "SOC_Particle2D.h"

class SOC_GameObject
{
public:

	SOC_GameObject();

	~SOC_GameObject();

	void RenderObject();

	void UpdateObject();

private:

	// sprite / graphics
	
	
	// Physics Component
	SOC_Particle2D particle;
};

#endif