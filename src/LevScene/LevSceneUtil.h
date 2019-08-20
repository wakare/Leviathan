#pragma once

#include "LevSceneAPIDefine.h"
#include "LPtr.h"
#include "LevSceneNode.h"
#include "LevNumericalUniform.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevSceneUtil
		{
		public:
			static bool InitSceneNodeWithMeshFile(const char* mesh_file, unsigned scene_object_mask, LPtr<LevSceneNode>& out_scene_node);

			enum MeshBindDataType
			{
				EMBDT_INDEX		= 0x1,
				EMBDT_COORD		= 0x2,
				EMBDT_NORMAL	= 0x4,
				EMBDT_TEX		= 0x8,
			};

			/*
				Comfortable generate function for basic geometry.
			*/
			static bool BindMeshDataToRenderAttribute(LevSceneNode& node, int bind_type_mask);

			// TODO: Can calculate static ball coordination in compile time.
			// Generate vertices and normal (Attribute layout is 0 and 1).

			static bool GenerateCube(const float* cube_center, float cube_length, LPtr<LevSceneNode>& out_cube_node);
			static bool GenerateBallNode(const float* ball_center, float ball_radius, LPtr<LevSceneNode>& out_ball_node);
			static bool GeneratePlaneNode(const float* plane_node0, const float* plane_node1, const float* plane_node2, const float* plane_node3, LPtr<LevSceneNode>& out_plane_node);
			static bool GeneratePoints(const float* vertices, const float* normals, unsigned count, LPtr<LevSceneNode>& out_points_node);

			/*
				Easy-interface to generate uniform.
			*/
			static bool GenerateIdentityMatrixUniform(const char* uniform_name, LPtr<LevNumericalUniform>& out_uniform);
		};
	}
}