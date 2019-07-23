#pragma once

namespace Leviathan
{
	namespace Scene
	{
		/*
		 * LevAttachment is used to attach frame buffer object.
		 * It may be texture object, render buffer object, depth object and stencil object
		 */
		class LevAttachment
		{
		public:
			virtual ~LevAttachment() = 0;
		};
	}
}
