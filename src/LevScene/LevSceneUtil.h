#pragma once

#include "LevSceneAPIDefine.h"
#include "LSPtr.h"
#include "LevSceneNode.h"
#include "LevNumericalUniform.h"

namespace Leviathan
{
	namespace Scene
	{
		class LEV_SCENE_API LevSceneUtil
		{
		public:
			static bool InitSceneNodeWithMeshFile(const char* mesh_file, unsigned scene_object_mask, LSPtr<LevSceneNode>& out_scene_node);

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

			static bool GenerateEmptySceneNode(LSPtr<LevSceneNode>& out);

			static bool GenerateCube(const float* cube_center, float cube_length, LSPtr<LevSceneNode>& out_cube_node);
			static bool GenerateBallNode(const float* ball_center, float ball_radius, LSPtr<LevSceneNode>& out_ball_node);
			static bool GeneratePlaneNode(const float* plane_node0, const float* plane_node1, const float* plane_node2, const float* plane_node3, LSPtr<LevSceneNode>& out_plane_node);
			static bool GeneratePoints(const float* vertices, const float* normals, unsigned count, LSPtr<LevSceneNode>& out_points_node);
			

			/*
				Easy-interface to generate uniform.
			*/
			static bool GenerateIdentityMatrixUniform(const char* uniform_name, LSPtr<LevNumericalUniform>& out_uniform);
			static bool GenerateLookAtMatrixUniform(const char* uniform_name, const float* eye, const float* target,
			                                        const float* up, LSPtr<LevNumericalUniform>& out_uniform);

			static bool GenerateProjectionMatrix(const char* uniform_name, float fov, float aspect, float near, float far, LSPtr<LevNumericalUniform>& out_uniform);
		};
	}
}