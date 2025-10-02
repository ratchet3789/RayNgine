#pragma once

#include "PxPhysics.h"
#include "foundation/PxFoundation.h"
#include "extensions/PxDefaultErrorCallback.h"
#include "extensions/PxDefaultAllocator.h"
#include "pvd/PxPvd.h"
#include "PxPhysics.h"
#include "extensions/PxExtensionsAPI.h"
#include "pvd/PxPvdTransport.h"

using namespace physx;

class Physics
{
public:
	Physics();
	void Release()
	{
		PxCloseExtensions();
		m_pTransport->release();
		m_pPhysics->release();
		m_pFoundation->release();
	}

	bool Initialize();

private:
	static PxDefaultErrorCallback gDefaultErrorCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;
	PxFoundation* m_pFoundation;
	PxPhysics* m_pPhysics;

	PxPvd* m_pPvd;
	PxPvdTransport* m_pTransport;

};

extern Physics g_Physics;
