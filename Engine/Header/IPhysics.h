#pragma once

class IPhysics {
public:
	enum BOUNDING_TYPE {
		BOX
		, SPHERE
	};

	enum COLLISION_OPT {
		AABB
		, OBB
	};
private:
	struct PHYSICS_OPT {
		_bool			bApplyGravity	= true;
		_bool			bApplyRolling	= false;
		_bool			bApplyBouncing = false;
		_bool			bApplyKnockBack = false;
		_float			fReflectSpeed = 5.f;
		_float			fDeceleration = 0.8f;
		BOUNDING_TYPE	eBoundingType = BOX;
		COLLISION_OPT	stCollisionOpt = AABB;
	};

protected:
	PHYSICS_OPT	m_stOpt;
	_vec3		m_vMinBox;
	_vec3		m_vMaxBox;
	_vec3		m_vNextMinBox;
	_vec3		m_vNextMaxBox;
	_vec3		m_vSphereCenter;
	_float		m_vSphereRadius;
	_vec3		m_vCollisionDir;

public:
	_vec3* Get_MinBox() {
		return &m_vMinBox;
	}

	_vec3* Get_MaxBox() {
		return &m_vMaxBox;
	}

	_vec3* Get_NextMinBox() {
		return &m_vNextMinBox;
	}

	_vec3* Get_NextMaxBox() {
		return &m_vNextMaxBox;
	}

	_vec3* Get_SphereCenter() {
		return &m_vSphereCenter;
	}

	_float* Get_SphereRadius() {
		return &m_vSphereRadius;
	}

	PHYSICS_OPT* Get_Opt() {
		return &m_stOpt;
	}

	void Set_BoundingBox(
		_vec3 _vMinBox, _vec3 _vMaxBox
		, _vec3 _vNextMinBox, _vec3 _vNextMaxBox
	) {
		m_vMinBox = _vMinBox;
		m_vMaxBox = _vMaxBox;
		m_vNextMinBox = _vNextMinBox;
		m_vNextMaxBox = _vNextMaxBox;
	}
};