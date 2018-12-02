#include "IModelStruct.h"

namespace Leviathan
{
	class CModelStruct : public IModelStruct
	{
	public:
		CModelStruct();
		~CModelStruct();

		unsigned GetVertexCount();
		unsigned GetTriangleCount();
		unsigned* GetTriangleIndexArray();
		float* GetVertex3DCoordArray();
		float* GetVertexColorArray();
		float* GetVertexTexArray();

		void SetVertexCoordData(unsigned uVertexCount, float* vertexCoordData);
		void SetTriangleIndexData(unsigned uTriangleCount, unsigned* triangleIndexData);
		void SetVertexTex2DData(unsigned uVertexCount, float* vertexTexData);
		void SetVertexColorData(unsigned uVertexCount, float* vertexColorData);
		void SetMaterial(LPtr<Material> material);

		LPtr<Material> GetMaterial();
		const AABB& GetAABB();

	private:
		bool _setAABB();

		unsigned*	m_triangleIndex;
		unsigned	m_triangleNumber;

		float*		m_vertexCoords;
		float*		m_vertexColorData;
		float*		m_vertexTexData;

		unsigned	m_vertexNumber;
		LPtr<Material> m_pMaterial;

		bool		m_bAABBInited;
		AABB		m_AABB;
	};
}