#include "Physics.h"

#include "../Debugging/Logger.h"
#include "common/PxTolerancesScale.h"
#include "foundation/PxPhysicsVersion.h"
#include "pvd/PxPvdTransport.h"

Physics g_Physics;

#define PVD_HOST "127.0.0.1"

Physics::Physics()
{
}

bool Physics::Initialize()
{
	m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	if (!m_pFoundation)
	{
		g_Logger.LogError("PxCreateFoundation failed!");
		return false; // This is a critical issue.
	}

	bool bRecordMemoryAllocations = true;
	PxCreatePvd(*m_pFoundation);
	m_pTransport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	m_pPvd->connect(*m_pTransport, PxPvdInstrumentationFlag::eALL);

	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, PxTolerancesScale(), bRecordMemoryAllocations, m_pPvd);
	if (!m_pPhysics)
	{
		g_Logger.LogError("PxCreatePhysics failed!");
		return false;
	}
	return true;
}

