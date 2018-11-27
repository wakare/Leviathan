#pragma once
#include "BaseMath.h"
#include "IModelStruct.h"
#include "LPtr.h"

namespace Leviathan
{
	class SceneNode
	{
	public:
		SceneNode();

		bool LoadModelFile(const char* szFileName);
		Leviathan::LPtr<Leviathan::IModelStruct> GetModelFile() const;
		void SetWorldCoord(const Vector3f& coord);
		const Vector3f& GetWorldCoord() const;
		Matrix4f GetWorldTransform() const;

	private:
		Vector3f m_worldCoord;
		Leviathan::LPtr<Leviathan::IModelStruct> m_pModelFile;
	};
}