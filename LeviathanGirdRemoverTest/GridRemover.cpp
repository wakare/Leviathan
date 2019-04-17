#include "GridRemover.h"

void GridDefaultMerger::Merge(const GridBar & sourceGrid, GridBar & targetGrid)
{
}

GridRemover::GridRemover()
{
	m_gridMerger.reset(new GridDefaultMerger);
}

GridRemover::~GridRemover()
{

}

void GridRemover::SetParameters(const GridRemoverConfig& config)
{
	m_config = config;
}

void GridRemover::SetTSDFCloud(const GridRemoverPointCloud& pointCloud)
{
	if (pointCloud.size() == 0)
	{
		return;
	}

	m_bars.clear();
	m_bars.resize(m_config.gridSize * m_config.gridSize);

	float _xmin, _xmax, _ymin, _ymax, _zmin;
	_xmin = _xmax = pointCloud[0].x;
	_ymin = _ymax = pointCloud[0].y;
	_zmin = pointCloud[0].z;

	for (auto& point : pointCloud)
	{
		if (_xmin > point.x) _xmin = point.x;
		if (_ymin > point.y) _ymin = point.y;
		if (_zmin > point.z) _zmin = point.z;

		if (_xmax < point.x) _xmax = point.x;
		if (_ymin < point.y) _ymin = point.y;
	}

	m_box.min().x() = _xmin; m_box.max().x() = _xmax;
	m_box.min().y() = _ymin; m_box.max().y() = _ymax;
	m_box.min().z() = _zmin; m_box.max().z() = 0.0f;

	m_xStep = (m_box.max().x() - m_box.min().x()) / m_config.gridSize;
	m_yStep = (m_box.max().y() - m_box.min().y()) / m_config.gridSize;

	for (unsigned i = 0; i < m_config.gridSize; i++)
	{
		for (unsigned j = 0; j < m_config.gridSize; j++)
		{
			auto& bar = m_bars[i * m_config.gridSize + j];

			bar.box.min().x() = _xmin + i * m_xStep;
			bar.box.max().x() = _xmin + (i + 1) * m_xStep;

			bar.box.min().y() = _ymin + i * m_yStep;
			bar.box.max().y() = _ymin + (i + 1) * m_yStep;

			bar.tsdf = 0.0f;
			bar.vmax = 0.0f;
			bar.vmin = 0.0f;
			bar.inited = true;
		}
	}

	for (auto& point : pointCloud)
	{
		auto grid = _convertPointToGridbar(point);
		auto& _parent = _getParentGrid(point);
		m_gridMerger->Merge(grid, _parent);
	}
}

void GridRemover::TestOverlap(const Eigen::Matrix4f& trans, const GridRemoverPointCloud& testPointCloud, std::vector<bool> result)
{
	for (auto& point : testPointCloud)
	{
		Eigen::Vector4f _point;
		memcpy(_point.data(), &point, sizeof(float) * 4);
		_point = trans * _point;

		auto data = _point.data();
		if (data[0] < m_box.min().x() || data[0] > m_box.max().x() || data[1] < m_box.min().y() || data[1] > m_box.max().y())
		{
			result.push_back(false);
		}
		else
		{
			auto& parent = _getParentGrid(_point.data());
			auto _tsdf = parent.tsdf + m_config.removePlaneOffset;
			auto _needFilter = _tsdf < point.z;
			result.push_back(_needFilter);
		}
	}
}

GridBar& GridRemover::_getParentGrid(const GridRemoverPoint& point)
{
	return _getParentGrid(&point.x);
}

GridBar& GridRemover::_getParentGrid(const float* data) 
{
	unsigned xIndex = (data[0] - m_box.min().x()) / m_xStep;
	unsigned yIndex = (data[1] - m_box.min().y()) / m_yStep;

	return m_bars[xIndex * m_config.gridSize + yIndex];
}

GridBar GridRemover::_convertPointToGridbar(const GridRemoverPoint& point) const
{
	GridBar result;
	result.tsdf = point.z;
	result.vmax = 0.0f;

	return std::move(result);
}
