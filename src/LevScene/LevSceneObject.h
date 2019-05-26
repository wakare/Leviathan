#pragma once

#include <vector>
#include <functional>
#include <Eigen/Dense>
#include "LPtr.h"

namespace Leviathan
{
	class LevTimer;

	namespace Scene
	{
		enum LevSceneObjectType
		{
			// Only leaf node can be static node
			ELSOT_STATIC		= 1,

			// Dynamic node is updated per traverse
			ELSOT_DYNAMIC		= 2,

			ELSOT_LIGHT			= 4,
			ELSOT_CAMERA		= 8,

			// Not set [self and children] modified flag while processing reset node modified
			ELSOT_NOT_MODIFY	= 16,

			// Default situation: modify self cause setting child modified flag
			ELSOT_ONLY_MODIFY_SELF = 32,

			// No need add this object to render objects
			ELSOT_UNRENDERABLE	= 1024,

			// Special node defination
			ELSOT_ROOT = ELSOT_DYNAMIC | ELSOT_UNRENDERABLE
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

		class LevSceneObject
		{
		public:
			LevSceneObject(int type);
			virtual ~LevSceneObject();

			SceneObjectID GetID() const;
			LevSceneObjectType GetType() const;

			bool HasModified() const;
			void SetModified();

			void SetState(LevSceneObjectState state);
			LevSceneObjectState GetState() const;

			void ResetUnModified();
			void SetModifiedCallback(LevSceneObjModified modified);

			bool AddAttribute(LPtr<LevSceneObjectAttribute> pAttribute);
			const std::vector<LPtr<LevSceneObjectAttribute>>& GetObjAttributes() const;

			bool HasObjectDesc() const;
			bool SetObjectDesc(LPtr<LevSceneObjectDescription> pObjDesc);
			LevSceneObjectDescription& GetObjectDesc();
			const LevSceneObjectDescription& GetObjectDesc() const;

			void SetRecalculateWorldTransform(bool need);
			bool NeedRecalculateWorldTransform() const;

			void SetTimer(LPtr<LevTimer> timer);
			
			LPtr<LevTimer> GetTimer();
			const LPtr<LevTimer> GetTimer() const;

			/*
				Warn:
					World coord will be caluculate automatic by LevCalculateWorldCoordVisitor,
					if you want to disable the process, please set m_recalculateWorldTransform to false.
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

			bool m_modified;
			bool m_recalculateWorldTransform;
			LevSceneObjModified m_modifiedCallback;
			LevSceneObjectState m_state;

			const LevSceneObjectType m_type;
			std::vector<LPtr<LevSceneObjectAttribute>> m_pAttributes;

			LPtr<LevLRAttrWorldTransform> m_pWorldTransform;
			LPtr<LevLRAttrModelTransform> m_pModelTransform;
			LPtr<LevLAttrLocalTransform> m_pLocalTransform;
			LPtr<LevSceneObjectDescription> m_pObjDesc;

			LPtr<LevTimer> m_pTimer;
		};
	}
}