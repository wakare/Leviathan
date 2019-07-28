#pragma once

namespace Leviathan
{
	namespace Scene
	{
		/*
		 * LevAttachment is used to attach frame buffer object.
		 * It may be texture object, render buffer object, depth object and stencil object
		 */
		enum LevAttachmentType
		{
			ELAT_TEXTURE_OBJECT		/* LevTextureObject class */
		};

		class LevTextureObject;

		class LevAttachment
		{
		public:
			virtual ~LevAttachment() = default;
			virtual LevAttachmentType GetAttachmentType() const = 0;

			virtual LevTextureObject* ToLevTextureObject() { return nullptr; };
		};
	}
}
