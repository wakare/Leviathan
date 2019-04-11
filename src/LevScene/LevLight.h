#pragma once

#include "LevSceneObject.h"
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

		class LevLight : public LevSceneObject
		{
		public: 
			LevLight(LevLightType type, int scene_obj_type);
			virtual ~LevLight();
			const Eigen::Vector3f& LightCoordination() const;
			void LightCoordination(const Eigen::Vector3f& val);
			const Eigen::Vector3f& AmbientColor() const;
			void AmbientColor(const Eigen::Vector3f& val);
			const Eigen::Vector3f& DiffuseColor() const;
			void DiffuseColor(const Eigen::Vector3f& val);
			const Eigen::Vector3f& SpecularColor() const;
			void SpecularColor(const Eigen::Vector3f& val);

		private:
			LevLightType m_type;
			Eigen::Vector3f m_lightCoordination;
			Eigen::Vector3f m_ambientColor;
			Eigen::Vector3f m_diffuseColor;
			Eigen::Vector3f m_specularColor;
		};

	}

}