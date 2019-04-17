#pragma once
#include <Eigen/Dense>
#include <vector>
#include <memory>

struct Point3D
{
	Point3D(float* data) { memcpy(this, data, sizeof(float) * 3); }
	Point3D() {}

	float x;
	float y;
	float z;
};

struct GridBar
{
	void GetBoxRange(float* min, float* max) 
	{
		min[0] = box.min().x();
		min[1] = box.min().y();

		max[0] = box.max().x();
		max[1] = box.max().y();
	}

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
		//gridSize = 10;
		gridCellLength = 200.0f;
	}

	float removePlaneOffset;
	//unsigned gridSize;
	float gridCellLength;
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

	void TestOverlap(const Eigen::Matrix4f& trans, const GridRemoverPointCloud& testPointCloud, std::vector<bool>& result);

	//Debug
	const std::vector<GridBar>& GetGridBars() const;
	std::vector<GridBar>& GetGridBars();

private:
	GridBar& _getParentGrid(const GridRemoverPoint& point);
	GridBar& _getParentGrid(const float* data);

	GridBar _convertPointToGridbar(const GridRemoverPoint& point) const;

	float m_xStep;
	float m_yStep;

	unsigned m_maxIndexX;
	unsigned m_maxIndexY;

	GridRemoverConfig m_config;
	Eigen::AlignedBox3d m_box;
	std::vector<GridBar> m_bars;
	std::unique_ptr<IGridMerger> m_gridMerger;
};