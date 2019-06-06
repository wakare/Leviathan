#include "LevSceneObject.h"
#include "GlobalDef.h"
#include "LevSceneObjectDescription.h"
#include "LevLRAttrModelTransform.h"
#include "LevLRAttrWorldTransform.h"
#include "LevLAttrLocalTransform.h"
#include "LevTimer.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneObject::LevSceneObject(int type) 
			: m_type((LevSceneObjectType)type)
			, m_modified(true)
			, m_recalculateWorldTransform(true)
			, m_pModelTransform(new LevLRAttrModelTransform)
			, m_pWorldTransform(new LevLRAttrWorldTransform)
			, m_pLocalTransform(new LevLAttrLocalTransform)
			, m_pTimer(nullptr)
			, m_state(ELSOS_ADDED)
			, m_modifiedCallback(nullptr)
		{
			// Init unique id
			static unsigned _globalID = 0;
			m_ID = _globalID++;

			_setBaseAttribute();

			// Default name: SceneObject: + id
			char name_buf[50];
			snprintf(name_buf, sizeof(name_buf), "SceneObject:%u", m_ID);
			SetName(name_buf);
		}

		LevSceneObject::LevSceneObject(const LevSceneObject& object)
			: m_type(object.GetType())
			, m_modified(object.m_modified)
			, m_recalculateWorldTransform(object.m_recalculateWorldTransform)
			, m_pModelTransform(new LevLRAttrModelTransform(*object.m_pModelTransform))
			, m_pWorldTransform(new LevLRAttrWorldTransform(*object.m_pWorldTransform))
			, m_pLocalTransform(new LevLAttrLocalTransform(*object.m_pLocalTransform))
			, m_pTimer(object.m_pTimer.Get() ? new LevTimer(*object.m_pTimer) : nullptr)
			, m_state(ELSOS_ADDED)
			, m_ID(object.m_ID)
			, m_name(object.m_name)
			// No need copy obj_desc 
			, m_pObjDesc(object.m_pObjDesc)
			, m_modifiedCallback(nullptr)
		{ 
			_setBaseAttribute();
		}

		LevSceneObject::~LevSceneObject()
		{
		}

		SceneObjectID LevSceneObject::GetID() const
		{
			return m_ID;
		}

		LevSceneObjectType LevSceneObject::GetType() const
		{
			return m_type;
		}

		void LevSceneObject::SetName(std::string name)
		{
			m_name = name;
		}

		const std::string & LevSceneObject::GetName() const
		{
			return m_name;
		}

		bool LevSceneObject::HasModified() const
		{
			return m_modified;
		}

		void LevSceneObject::SetModified()
		{
			m_modified = true;
			if (m_modifiedCallback)
			{
				m_modifiedCallback(*this);
			}
		}

		void LevSceneObject::SetState(LevSceneObjectState state)
		{
			m_state = state;
			SetModified();
		}

		LevSceneObjectState LevSceneObject::GetState() const
		{
			return m_state;
		}

		void LevSceneObject::ResetUnModified()
		{
			m_modified = false;
		}

		void LevSceneObject::SetModifiedCallback(LevSceneObjModified modified)
		{
			m_modifiedCallback = modified;
		}

		bool LevSceneObject::AddAttribute(LPtr<LevSceneObjectAttribute> pAttribute)
		{
			m_attributes.push_back(pAttribute);
			return true;
		}

		const std::vector<LPtr<LevSceneObjectAttribute>>& LevSceneObject::GetAllAttributes() const
		{
			return m_attributes;
		}

		bool LevSceneObject::HasObjectDesc() const
		{
			return m_pObjDesc.Get();
		}

		bool LevSceneObject::SetObjectDesc(LPtr<LevSceneObjectDescription> pObjDesc)
		{
			m_pObjDesc.Reset(pObjDesc);
			return true;
		}

		LevSceneObjectDescription & LevSceneObject::GetObjectDesc()
		{
			return *m_pObjDesc;
		}

		const LevSceneObjectDescription & LevSceneObject::GetObjectDesc() const
		{
			LEV_ASSERT(m_pObjDesc.Get());
			return *m_pObjDesc;
		}

		void LevSceneObject::SetRecalculateWorldTransform(bool need)
		{
			m_recalculateWorldTransform = need;
		}

		bool LevSceneObject::NeedRecalculateWorldTransform() const
		{
			return m_recalculateWorldTransform;
		}

		void LevSceneObject::SetTimer(LPtr<LevTimer> timer)
		{
			m_pTimer = timer;
		}

		LPtr<LevTimer> LevSceneObject::GetTimer()
		{
			return m_pTimer;
		}

		const LPtr<LevTimer> LevSceneObject::GetTimer() const
		{
			return m_pTimer;
		}

		bool LevSceneObject::SetWorldTransform(const Eigen::Matrix4f& trans)
		{
			LEV_ASSERT(m_pWorldTransform);
			m_pWorldTransform->SetMatrix(trans);
			return true;
		}

		const Eigen::Matrix4f& LevSceneObject::GetWorldTransform() const
		{
			LEV_ASSERT(m_pWorldTransform.Get());
			return m_pWorldTransform->GetMatrix();
		}

		bool LevSceneObject::SetModelTransform(const Eigen::Matrix4f & trans)
		{
			LEV_ASSERT(m_pModelTransform);
			m_pModelTransform->SetMatrix(trans);
			return true;
		}

		const Eigen::Matrix4f& LevSceneObject::GetModelTransform() const
		{
			LEV_ASSERT(m_pModelTransform.Get());
			return m_pModelTransform->GetMatrix();
		}

		bool LevSceneObject::SetLocalTransform(const Eigen::Matrix4f & trans)
		{
			LEV_ASSERT(m_pLocalTransform);
			m_pLocalTransform->SetMatrix(trans);
			return true;
		}

		const Eigen::Matrix4f & LevSceneObject::GetLocalTransform() const
		{
			LEV_ASSERT(m_pLocalTransform.Get());
			return m_pLocalTransform->GetMatrix();
		}

		bool LevSceneObject::SetEmpty()
		{
			// Clear run time data.
			m_pObjDesc.Reset(nullptr);
			m_pTimer.Reset(nullptr);
			m_attributes.clear();
			
			m_pLocalTransform->Reset();
			m_pModelTransform->Reset();
			m_pWorldTransform->Reset();
			_setBaseAttribute();

			SetState(ELSOS_UPDATE);

			return true;
		}

		void LevSceneObject::_setBaseAttribute()
		{
			// Add transforms
			m_attributes.push_back(TryCast<LevLRAttrModelTransform, LevSceneObjectAttribute>(m_pModelTransform));
			m_attributes.push_back(TryCast<LevLRAttrWorldTransform, LevSceneObjectAttribute>(m_pWorldTransform));
			m_attributes.push_back(TryCast<LevLAttrLocalTransform, LevSceneObjectAttribute>(m_pLocalTransform));
		}
	}
}