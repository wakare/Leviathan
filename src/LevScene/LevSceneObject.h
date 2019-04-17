#pragma once

#include <vector>
#include <functional>
#include <Eigen/Dense>
#include "LPtr.h"

namespace Leviathan
{
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

		class LevLAttrWorldTransform;
		class LevLAttrModelTransform;

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

			bool SetObjectDesc(LPtr<LevSceneObjectDescription> pObjDesc);
			const LevSceneObjectDescription& GetObjDesc() const;

			bool SetWorldTransform(const Eigen::Matrix4f& trans);
			const Eigen::Matrix4f& GetWorldTransform() const;

			bool SetModelTransform(const Eigen::Matrix4f& trans);
			const Eigen::Matrix4f& GetModelTransform() const;

		private:
			SceneObjectID m_ID;

			bool m_modified;
			LevSceneObjModified m_modifiedCallback;
			LevSceneObjectState m_state;

			const LevSceneObjectType m_type;
			std::vector<LPtr<LevSceneObjectAttribute>> m_pAttributes;

			LPtr<LevLAttrWorldTransform> m_pWorldTransform;
			LPtr<LevLAttrModelTransform> m_pModelTransform;

			LPtr<LevSceneObjectDescription> m_pObjDesc;
		};
	}
}