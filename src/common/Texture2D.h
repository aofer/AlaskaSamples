#pragma once
#include "Texture.h"

	class Texture2D : public Texture
	{
	public:
		Texture2D();
		virtual ~Texture2D();

	private:

		virtual void InitOnGPU(bool deleteAfterPush = false);

	};
