#pragma once
#include "Texture.h"

	class Texture2DArray : public Texture
	{
	public:
		Texture2DArray();
		virtual ~Texture2DArray();

	private:

		virtual void InitOnGPU(bool deleteAfterPush = false);



	};
