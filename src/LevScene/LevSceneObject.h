#pragma once

#include <vector>
#include <functional>
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		enum LevSceneObjectType
		{
			// Only leaf node can be static node
			ELSOT_STATIC = 1,

			// Dynamic node is updated per traverse
			ELSOT_DYNAMIC = 2,

			ELSOT_LIGHT = 4,
			ELSOT_CAMERA = 8,
			// Not set [self and children] modified flag while processing reset node modified
			ELSOT_NOT_MODIFY = 16,

			ELSOT_UNRENDERABLE = 1024,

			// Special node defination
			ELSOT_ROOT = ELSOT_DYNAMIC | ELSOT_UNRENDERABLE
		};

		class LevSceneObject;
		class LevSceneObjectAttribute;
		class LevSceneObjectDescription;

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
			void ResetModified();
			void SetModifiedCallback(LevSceneObjModified modified);

			bool AddAttribute(LPtr<LevSceneObjectAttribute> pAttribute);
			const std::vector<LPtr<LevSceneObjectAttribute>>& GetObjAttributes() const;

			bool SetObjectDesc(LPtr<LevSceneObjectDescription> pObjDesc);
			const LevSceneObjectDescription& GetObjDesc() const;

		private:
			SceneObjectID m_ID;

			bool m_modified;
			LevSceneObjModified m_modifiedCallback;

			const LevSceneObjectType m_type;
			std::vector<LPtr<LevSceneObjectAttribute>> m_pAttributes;
			LPtr<LevSceneObjectDescription> m_pObjDesc;
		};
	}
}