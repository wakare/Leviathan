#include "LevSceneObject.h"
#include "GlobalDef.h"
#include "LevSceneObjectDescription.h"
#include "LevLRAttrModelTransform.h"
#include "LevLRAttrWorldTransform.h"
#include "LevLAttrLocalTransform.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneObject::LevSceneObject(int type) 
			: m_type((LevSceneObjectType)type)
			, m_modified(true)
			, m_pModelTransform(new LevLRAttrModelTransform)
			, m_pWorldTransform(new LevLRAttrWorldTransform)
			, m_pLocalTransform(new LevLAttrLocalTransform)
			, m_state(ELSOS_ADDED)
		{
			// Init unique id
			static unsigned _globalID = 0;
			m_ID = _globalID++;

			// Add transforms
			m_pAttributes.push_back(TryCast<LevLRAttrModelTransform, LevSceneObjectAttribute>(m_pModelTransform));
			m_pAttributes.push_back(TryCast<LevLRAttrWorldTransform, LevSceneObjectAttribute>(m_pWorldTransform));
			m_pAttributes.push_back(TryCast<LevLAttrLocalTransform, LevSceneObjectAttribute>(m_pLocalTransform));
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
			m_pAttributes.push_back(pAttribute);
			return true;
		}

		const std::vector<LPtr<LevSceneObjectAttribute>>& LevSceneObject::GetObjAttributes() const
		{
			return m_pAttributes;
		}

		bool LevSceneObject::SetObjectDesc(LPtr<LevSceneObjectDescription> pObjDesc)
		{
			m_pObjDesc.Reset(pObjDesc);
			return true;
		}

		const LevSceneObjectDescription & LevSceneObject::GetObjDesc() const
		{
			LEV_ASSERT(m_pObjDesc.Get());
			return *m_pObjDesc;
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
	}
}