#include "LevSceneObject.h"
#include "GlobalDef.h"
#include "LevSceneObjectDescription.h"
#include "LevLRAttrModelTransform.h"
#include "LevLRAttrWorldTransform.h"
#include "LevLAttrLocalTransform.h"
#include "LevTimer.h"
#include "LevRAttrUniformManager.h"

namespace Leviathan
{
	namespace Scene
	{
		LevSceneObject::LevSceneObject(int type) 
			: m_type((LevSceneObjectType)type)
			, m_modified(true)
			, m_recalculate_world_transform(true)
			, m_model_transform(new LevLRAttrModelTransform)
			, m_world_transform(new LevLRAttrWorldTransform)
			, m_local_transform(new LevLAttrLocalTransform)
			, m_timer(nullptr)
			, m_state(ELSOS_ADDED)
			, m_modified_callback(nullptr)
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
			, m_recalculate_world_transform(object.m_recalculate_world_transform)
			, m_model_transform(new LevLRAttrModelTransform(*object.m_model_transform))
			, m_world_transform(new LevLRAttrWorldTransform(*object.m_world_transform))
			, m_local_transform(new LevLAttrLocalTransform(*object.m_local_transform))
			, m_timer(object.m_timer.Get() ? new LevTimer(*object.m_timer) : nullptr)
			, m_state(ELSOS_ADDED)
			, m_ID(object.m_ID)
			, m_name(object.m_name)
			// No need copy obj_desc 
			, m_obj_desc(object.m_obj_desc)
			, m_modified_callback(nullptr)
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
			if (m_modified_callback)
			{
				m_modified_callback(*this);
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
			m_modified_callback = modified;
		}

		void LevSceneObject::SetUpdatedCallback(LevSceneObjUpdated updated)
		{
			m_update_callback = updated;
		}

		const LevSceneObjUpdated& LevSceneObject::GetSceneObjectUpdateCallback()
		{
			return m_update_callback;
		}

		bool LevSceneObject::AddUniform(LSPtr<ILevUniform> uniform)
		{
			LevRAttrUniformManager* uniform_manager = nullptr;
			GetAttribute<LevRAttrUniformManager>(uniform_manager);

			if (!uniform_manager)
			{
				LSPtr<LevRAttrUniformManager> manager = new LevRAttrUniformManager;
				AddAttribute(manager);
				uniform_manager = manager.Get();
			}

			if(!uniform_manager)
			{
				return false;
			}

			uniform_manager->AddUniform(std::move(uniform));
			return true;
		}

		const std::vector<LSPtr<LevSceneObjectAttribute>>& LevSceneObject::GetAllAttributes() const
		{
			return m_attributes;
		}

		bool LevSceneObject::HasObjectDesc() const
		{
			return m_obj_desc.Get();
		}

		bool LevSceneObject::SetObjectDesc(LSPtr<LevSceneObjectDescription> pObjDesc)
		{
			m_obj_desc.Reset(pObjDesc);
			return true;
		}

		LevSceneObjectDescription & LevSceneObject::GetObjectDesc()
		{
			return *m_obj_desc;
		}

		const LevSceneObjectDescription & LevSceneObject::GetObjectDesc() const
		{
			LEV_ASSERT(m_obj_desc.Get());
			return *m_obj_desc;
		}

		void LevSceneObject::SetRecalculateWorldTransform(bool need)
		{
			m_recalculate_world_transform = need;
		}

		bool LevSceneObject::NeedRecalculateWorldTransform() const
		{
			return m_recalculate_world_transform;
		}

		void LevSceneObject::SetTimer(LSPtr<LevTimer> timer)
		{
			m_timer = timer;
		}

		LSPtr<LevTimer> LevSceneObject::GetTimer()
		{
			return m_timer;
		}

		const LSPtr<LevTimer> LevSceneObject::GetTimer() const
		{
			return m_timer;
		}

		bool LevSceneObject::SetWorldTransform(const Eigen::Matrix4f& trans)
		{
			LEV_ASSERT(m_world_transform);
			m_world_transform->SetMatrix(trans);
			return true;
		}

		const Eigen::Matrix4f& LevSceneObject::GetWorldTransform() const
		{
			LEV_ASSERT(m_world_transform.Get());
			return m_world_transform->GetMatrix();
		}

		bool LevSceneObject::SetModelTransform(const Eigen::Matrix4f & trans)
		{
			LEV_ASSERT(m_model_transform);
			m_model_transform->SetMatrix(trans);
			return true;
		}

		const Eigen::Matrix4f& LevSceneObject::GetModelTransform() const
		{
			LEV_ASSERT(m_model_transform.Get());
			return m_model_transform->GetMatrix();
		}

		bool LevSceneObject::SetLocalTransform(const Eigen::Matrix4f & trans)
		{
			LEV_ASSERT(m_local_transform);
			m_local_transform->SetMatrix(trans);
			return true;
		}

		const Eigen::Matrix4f & LevSceneObject::GetLocalTransform() const
		{
			LEV_ASSERT(m_local_transform.Get());
			return m_local_transform->GetMatrix();
		}

		bool LevSceneObject::SetEmpty()
		{
			// Clear run time data.
			m_obj_desc.Reset(nullptr);
			m_timer.Reset(nullptr);
			m_attributes.clear();
			
			m_local_transform->Reset();
			m_model_transform->Reset();
			m_world_transform->Reset();
			_setBaseAttribute();

			SetState(ELSOS_UPDATE);

			return true;
		}

		void LevSceneObject::_setBaseAttribute()
		{
			// Add transforms
			m_attributes.push_back(TryCast<LevLRAttrModelTransform, LevSceneObjectAttribute>(m_model_transform));
			m_attributes.push_back(TryCast<LevLRAttrWorldTransform, LevSceneObjectAttribute>(m_world_transform));
			m_attributes.push_back(TryCast<LevLAttrLocalTransform, LevSceneObjectAttribute>(m_local_transform));
		}
	}
}
