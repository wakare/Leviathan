#include "IModelStruct.h"

namespace Leviathan
{
	class CModelStruct : public IModelFile
	{
	public:
		CModelStruct();
		~CModelStruct();

		unsigned GetVertexCount();
		unsigned GetTriangleCount();
		float* GetVertex3DCoordArray();
		float* GetVertexColorArray();
		unsigned* GetTriangleIndexArray();

		void SetVertexCoordData(unsigned uVertexCount, float* vertexCoordData);
		void SetTriangleIndexData(unsigned uTriangleCount, unsigned* triangleIndexData);
		const AABB& GetAABB();
	private:
		bool _setAABB();

		unsigned*	m_triangleIndex;
		unsigned	m_triangleNumber;

		float*		m_vertexCoords;
		unsigned	m_vertexNumber;
		bool		m_bAABBInited;
		AABB		m_AABB;
	};
}