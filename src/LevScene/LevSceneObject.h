#pragma once

#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		enum LevSceneObjectType
		{
			ELSOT_STATIC = 1,
			ELSOT_DYNAMIC = 2,
			ELSOT_LIGHT = 4,
			ELSOT_UNRENDERABLE = 1024,

			// Special defination
			ELSOT_CAMERA = ELSOT_DYNAMIC | ELSOT_UNRENDERABLE,
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