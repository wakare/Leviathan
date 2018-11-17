#include "IModelStruct.h"

namespace Leviathan
{
	class CModelStruct : public IModelFile
	{
	public:
		CModelStruct();
		
		unsigned GetVertexCount();
		unsigned GetTriangleCount();
		float* GetVertex3DCoordArray();
		float* GetVertexColorArray();
		unsigned* GetTriangleIndexArray();

		void SetVertexCoordData(unsigned uVertexCount, float* vertexCoordData);
		void SetTriangleIndexData(unsigned uTriangleCount, unsigned* triangleIndexData);

	private:
		unsigned*	m_triangleIndex;
		unsigned	m_triangleNumber;

		float*		m_vertexCoords;
		unsigned	m_vertexNumber;
	};
}