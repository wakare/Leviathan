#pragma once
#include <Eigen/Dense>
#include <vector>
#include <memory>

struct Point3D
{
	float x;
	float y;
	float z;
};

struct GridBar
{
	bool inited;
	Eigen::AlignedBox2f box;
	float tsdf;
	float vmin;
	float vmax;
};

struct GridRemoverConfig
{
	GridRemoverConfig()
	{
		removePlaneOffset = 2.0f;
		gridSize = 64;
	}

	float removePlaneOffset;
	unsigned gridSize;
};

class IGridMerger
{
public:
	virtual void Merge(const GridBar& sourceGrid, GridBar& targetGrid) = 0;
};

class GridDefaultMerger : public IGridMerger
{
public:
	void Merge(const GridBar& sourceGrid, GridBar& targetGrid);
};

class GridRemover
{
public:
	typedef Point3D GridRemoverPoint;
	typedef std::vector<GridRemoverPoint> GridRemoverPointCloud;

	GridRemover();
	~GridRemover();

	void SetParameters(const GridRemoverConfig& config);
	void SetTSDFCloud(const GridRemoverPointCloud& pointCloud);

	void TestOverlap(const Eigen::Matrix4f& trans, const GridRemoverPointCloud& testPointCloud, std::vector<bool> result);
private:
	GridBar& _getParentGrid(const GridRemoverPoint& point) const;
	GridBar& _getParentGrid(const float* data) const;

	GridBar _convertPointToGridbar(const GridRemoverPoint& point) const;

	GridRemoverConfig m_config;
	Eigen::AlignedBox2d m_box;
	std::vector<GridBar> m_bars;
	std::unique_ptr<IGridMerger> m_gridMerger;
};