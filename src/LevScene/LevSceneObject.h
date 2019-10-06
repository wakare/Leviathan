#pragma once

#include <vector>
#include <functional>
#include <Eigen/Dense>
#include <string>
#include "LSPtr.h"
#include "LevSceneAPIDefine.h"
#include "ILevUniform.h"

namespace Leviathan
{
	class LevTimer;

	namespace Scene
	{
		enum LevSceneObjectType
		{
			// Only leaf node can be static node
			ELSOT_STATIC = 1,

			// Dynamic node is updated per traverse
			ELSOT_DYNAMIC = 2,

			// Not set [self and children] modified flag while processing reset node modified
			ELSOT_NOT_MODIFY = 4,

			// Default situation: modify self cause setting child modified flag
			ELSOT_ONLY_MODIFY_SELF = 8,

			// No need add this object to render objects
			ELSOT_UNRENDERABLE = 16,

			// Special node defination
			ELSOT_LIGHT		= 32,
			ELSOT_CAMERA	= 64,

			ELSOT_EMPTY = ELSOT_DYNAMIC | ELSOT_UNRENDERABLE | 128,
			ELSOT_ROOT	= ELSOT_DYNAMIC | ELSOT_UNRENDERABLE | 256
		};

		enum LevSceneObjectState
		{
			// Most of object state
			ELSOS_UNMODIFIED	= 0,

			// Add to scene just now
			ELSOS_ADDED			= 1,

			// Attribute changed
			ELSOS_UPDATE		= 2,

			ELSOS_DISABLE		= 3,

			// Delete this object next frame
			ELSOS_DELETED		= 4,

			// Default state
			ELSOS_UNKNOWN		= 100
		};

		class LevSceneObject;
		class LevSceneObjectAttribute;
		class LevSceneObjectDescription;

		class LevLRAttrWorldTransform;
		class LevLRAttrModelTransform;
		class LevLAttrLocalTransform;
		
		typedef unsigned SceneObjectID;
		
		typedef std::function<void(const LevSceneObject&)> LevSceneObjModified;
		typedef std::function<void(LevSceneObject&)> LevSceneObjUpdated;

		class LEV_SCENE_API LevSceneObject
		{
		public:
			LevSceneObject(int type);
			LevSceneObject(const LevSceneObject& object);

			virtual ~LevSceneObject();

			SceneObjectID GetID() const;
			LevSceneObjectType GetType() const;

			void SetName(std::string name);
			const std::string& GetName() const;

			bool HasModified() const;
			void SetModified();

			void SetState(LevSceneObjectState state);
			LevSceneObjectState GetState() const;

			void ResetUnModified();
			void SetModifiedCallback(LevSceneObjModified modified);

			void SetUpdatedCallback(LevSceneObjUpdated updated);
			const LevSceneObjUpdated& GetSceneObjectUpdateCallback();

			template <typename T>
			bool AddAttribute(LSPtr<T> pAttribute);

			bool AddUniform(LSPtr<ILevUniform> uniform);

			const std::vector<LSPtr<LevSceneObjectAttribute>>& GetAllAttributes() const;

			template<typename T>
			void UpdateAttribute(LSPtr<T> attribute);

			template<typename T>
			bool GetAttribute(const T*& out) const;

			template<typename T>
			bool GetAttribute(T*& out);

			bool HasObjectDesc() const;
			bool SetObjectDesc(LSPtr<LevSceneObjectDescription> pObjDesc);
			LevSceneObjectDescription& GetObjectDesc();
			const LevSceneObjectDescription& GetObjectDesc() const;

			void SetRecalculateWorldTransform(bool need);
			bool NeedRecalculateWorldTransform() const;

			void SetTimer(LSPtr<LevTimer> timer);
			
			LSPtr<LevTimer> GetTimer();
			const LSPtr<LevTimer> GetTimer() const;
			
			/*
				Warn:
					World coord will be calculate automatic by LevCalculateWorldCoordVisitor,
					if you want to disable the process, please set m_recalculate_world_transform to false.
			*/
			bool SetWorldTransform(const Eigen::Matrix4f& trans);
			const Eigen::Matrix4f& GetWorldTransform() const;

			bool SetModelTransform(const Eigen::Matrix4f& trans);
			const Eigen::Matrix4f& GetModelTransform() const;

			bool SetLocalTransform(const Eigen::Matrix4f& trans);
			const Eigen::Matrix4f& GetLocalTransform() const;

			bool SetEmpty();

		private:
			void _setBaseAttribute();

			SceneObjectID m_ID;
			std::string m_name;

			bool m_modified;
			bool m_recalculate_world_transform;
			LevSceneObjModified m_modified_callback;
			LevSceneObjectState m_state;

			LevSceneObjUpdated m_update_callback;

			const LevSceneObjectType m_type;
			std::vector<LSPtr<LevSceneObjectAttribute>> m_attributes;

			LSPtr<LevLRAttrWorldTransform> m_world_transform;
			LSPtr<LevLRAttrModelTransform> m_model_transform;
			LSPtr<LevLAttrLocalTransform> m_local_transform;
			LSPtr<LevSceneObjectDescription> m_obj_desc;

			LSPtr<LevTimer> m_timer;
		};

		template <typename T>
		bool LevSceneObject::AddAttribute(LSPtr<T> pAttribute)
		{
			const LSPtr<LevSceneObjectAttribute> attribute = pAttribute.To<LevSceneObjectAttribute>();
			LEV_ASSERT(attribute.Get());
			return AddAttribute(attribute);
		}

		template <>
		inline bool LevSceneObject::AddAttribute(LSPtr<LevSceneObjectAttribute> pAttribute)
		{
			LEV_ASSERT(pAttribute.Get());
			if (!pAttribute)
			{
				return false;
			}

			m_attributes.push_back(pAttribute);
			return true;
		}

		template<typename T>
		void LevSceneObject::UpdateAttribute(LSPtr<T> attribute)
		{
			//LSPtr<Scene::LevSceneObjectAttribute> scene_attribute = TryCast(attribute);
			const LSPtr<Scene::LevSceneObjectAttribute> scene_attribute = attribute.To<LevSceneObjectAttribute>();

			for (auto& old_attribute : m_attributes)
			{
				auto p = dynamic_cast<T*>(old_attribute.Get());
				if (p)
				{
					old_attribute = scene_attribute;
					return;
				}
			}

			AddAttribute(attribute);
		}

		template<typename T>
		bool LevSceneObject::GetAttribute(const T*& out) const
		{
			for (auto& attribute : m_attributes)
			{
				T* p = dynamic_cast<T*>(attribute.Get());
				if (p)
				{
					out = p;
					return true;
				}
			}

			return false;
		}

		template<typename T>
		bool LevSceneObject::GetAttribute(T*& out)
		{
			for (auto& attribute : m_attributes)
			{
				T* p = dynamic_cast<T*>(attribute.Get());
				if (p)
				{
					out = p;
					return true;
				}
			}

			return false;
		}

}
}
