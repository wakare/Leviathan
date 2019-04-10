#pragma once

#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		enum LevSceneObjectType
		{
			LSOT_STATIC = 1,
			LSOT_DYNAMIC = 2,
			LSOT_UNRENDERABLE = 1024,

			// Special defination
			LSOT_CAMERA = LSOT_DYNAMIC | LSOT_UNRENDERABLE,
		};

		class LevSceneObjectAttribute;
		class LevSceneObjectDescription;

		class LevSceneObject
		{
		public:
			LevSceneObject(int type);
			virtual ~LevSceneObject();

			LevSceneObjectType GetType() const;

			bool AddAttribute(LPtr<LevSceneObjectAttribute> pAttribute);
			const std::vector<LPtr<LevSceneObjectAttribute>>& GetObjAttributes() const;

			bool SetObjectDesc(LPtr<LevSceneObjectDescription> pObjDesc);
			const LevSceneObjectDescription& GetObjDesc() const;

		private:
			const LevSceneObjectType m_type;
			std::vector<LPtr<LevSceneObjectAttribute>> m_pAttributes;
			LPtr<LevSceneObjectDescription> m_pObjDesc;
		};
	}
}