#pragma once

#include "LevSceneObject.h"
#include "LevSceneAPIDefine.h"
#include <Eigen/Dense>

namespace Leviathan
{
	namespace Scene
	{
		enum LevLightType
		{
			ELLT_POINT_LIGHT,
			ELLT_DIR_LIGHT,
		};

		class LEV_SCENE_API LevLight : public LevSceneObject
		{
		public: 
			LevLight(LevLightType type, int scene_obj_type);
			virtual ~LevLight();

			LevLightType GetLightType() const;
			const Eigen::Vector3f& AmbientColor() const;
			void SetAmbientColor(const Eigen::Vector3f& val);
			const Eigen::Vector3f& DiffuseColor() const;
			void SetDiffuseColor(const Eigen::Vector3f& val);
			const Eigen::Vector3f& SpecularColor() const;
			void SetSpecularColor(const Eigen::Vector3f& val);

		private:
			LevLightType m_lightType;
			Eigen::Vector3f m_ambientColor;
			Eigen::Vector3f m_diffuseColor;
			Eigen::Vector3f m_specularColor;
		};

	}

}