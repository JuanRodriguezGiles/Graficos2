#include "textureImporter.h"
#include "renderer.h"
#include "animation.h"
#include "sprite.h"
#include "glew.h"
#include "glfw3.h"

namespace engine
{
	sprite::sprite()
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = nullptr;

		baseUVCoords[0] = { 1.0f, 1.0f };
		baseUVCoords[1] = { 1.0f, 0.0f };
		baseUVCoords[2] = { 0.0f, 0.0f };
		baseUVCoords[3] = { 0.0f, 1.0f };
	}
	sprite::sprite(renderer* render, const char* filePathImage, bool invertImage)
	{
		VAO = 0;
		VBO = 0;
		EBO = 0;
		_vertices = 0;
		_renderer = render;

		baseUVCoords[0] = { 1.0f, 1.0f };
		baseUVCoords[1] = { 1.0f, 0.0f };
		baseUVCoords[2] = { 0.0f, 0.0f };
		baseUVCoords[3] = { 0.0f, 1.0f };

		setTexture(render, filePathImage, invertImage);
	}
	sprite::~sprite()
	{
	}
	void sprite::draw()
	{
		_renderer->textureShader.use();
		unsigned int texture = getCurrentTextureIDToDraw();
		glBindTexture(GL_TEXTURE_2D, texture);
		setShader(texture);
		_renderer->drawRequest(model, VAO, _vertices, _renderer->textureShader.ID);
	}
	void sprite::modifyBaseTextureCoords(atlasCutConfig config)
	{
		int spriteWidth = 0;
		int spriteHeight = 0;
		if (config.useSize)
		{
			spriteWidth = config.spriteWidth;
			spriteHeight = config.spriteHeight;
		}
		else
		{
			spriteWidth = (int)(baseTexture->width / config.columns);
			spriteHeight = (int)(baseTexture->height / config.rows);
		}

		baseUVCoords[0].x = (spriteWidth + (spriteWidth * config.offsetX)) / baseTexture->width;		// top right
		baseUVCoords[0].y = (spriteHeight * config.offsetY) / baseTexture->height;						// top right
		baseUVCoords[1].x = (spriteWidth + (spriteWidth * config.offsetX)) / baseTexture->width; 		// bottom right
		baseUVCoords[1].y = (spriteHeight + (spriteHeight * config.offsetY)) / baseTexture->height;		// bottom right
		baseUVCoords[2].x = (spriteWidth * config.offsetX) / baseTexture->width;						// bottom left
		baseUVCoords[2].y = (spriteHeight + (spriteHeight * config.offsetY)) / baseTexture->height;		// bottom left
		baseUVCoords[3].x = (spriteWidth * config.offsetX) / baseTexture->width;						// top left 
		baseUVCoords[3].y = (spriteHeight * config.offsetY) / baseTexture->height;						// top left 

		float UVs[8] =
		{
			baseUVCoords[0].x, baseUVCoords[0].y,
			baseUVCoords[1].x, baseUVCoords[1].y,
			baseUVCoords[2].x, baseUVCoords[2].y,
			baseUVCoords[3].x, baseUVCoords[3].y
		};
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
	}
	void sprite::setShader(unsigned int texture)
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(_renderer->textureShader.ID, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(_renderer->textureShader.ID, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));

		unsigned int textureLoc = glGetUniformLocation(_renderer->textureShader.ID, "ourTexture");
		glUniform1f(textureLoc, (GLfloat)texture);
	}
	unsigned int sprite::getCurrentTextureIDToDraw()
	{
		for (unsigned int i = 0; i < animations.size(); i++)
		{
			if(animations[i]->isPlaying())
			{
				if(animations[i]->update())
				{
					bindCustomUVCoords(i);
					lastCoordIndex = i;
				}
				return animations[i]->getTextureID();
			}
		}
		if (animations.size() > 0) bindCustomUVCoords(lastCoordIndex);
		else bindBaseUVCoords();
		return baseTexture->ID;
	}
	void sprite::bindCustomUVCoords(int i)
	{
		glm::vec2* uv = animations[i]->getCurrentFramesCoordinates();
		float UVs[8] =
		{
			uv[0].x, uv[0].y, // top right
			uv[1].x, uv[1].y, // bottom right
			uv[2].x, uv[2].y, // bottom left
			uv[3].x, uv[3].y, // top left 
		};
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
	}
	void sprite::bindBaseUVCoords()
	{
		float UVs[8] =
		{
			baseUVCoords[0].x, baseUVCoords[0].y,
			baseUVCoords[1].x, baseUVCoords[1].y,
			baseUVCoords[2].x, baseUVCoords[2].y,
			baseUVCoords[3].x, baseUVCoords[3].y
		};
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_STATIC_DRAW);
	}
	textureData* sprite::createAnimationAtlas(const char* AtlasFilepath, bool invertImage)
	{
		return new textureData(textureImporter::loadTexture(AtlasFilepath, invertImage));
	}
	void sprite::deleteAnimationAtlas(textureData* atlas)
	{
		delete atlas;
	}
	int sprite::createAnimation()
	{
		animation* anim = new animation();
		animations.push_back(anim);
		return animations.size() - 1;
	}
	int sprite::createAnimation(atlasCutConfig config)
	{
		animation* anim = new animation();
		anim->setAnimation(baseTexture, config);
		animations.push_back(anim);
		return animations.size() - 1;
	}
	int sprite::createAnimation(textureData* animationAtlasData, int columns, int rows)
	{
		animation* anim = new animation();
		anim->setAnimation(animationAtlasData, columns, rows);
		animations.push_back(anim);
		return animations.size() - 1;
	}
	int sprite::createAnimation(textureData* animationAtlasData, atlasCutConfig config)
	{
		animation* anim = new animation();
		anim->setAnimation(animationAtlasData, config);
		animations.push_back(anim);
		return animations.size() - 1;
	}
	void sprite::addFrameToAnimation(int animationID, int positionX, int positionY, int width, int height)
	{
		animations[animationID]->addFrameToAnimation(positionX, positionY, width, height);
	}
	void sprite::playAnimation(int animationID)
	{
		if (!animations[animationID]->isPlaying())
		{
			for (unsigned int i = 0; i < animations.size(); i++)
			{
				animations[i]->stop();
			}
			animations[animationID]->play();
		}
	}
	void sprite::stopAnimation(int animationID)
	{
		animations[animationID]->stop();
	}
	void sprite::stopAllAnimations()
	{
		for (unsigned int i = 0; i < animations.size(); i++)
		{
			animations[i]->stop();
		}
	}
	void sprite::setAnimationSpeed(int animationID, float speed)
	{
		animations[animationID]->setAnimationSpeed(speed);
	}
	void sprite::setAnimationTimeBetweenFrames(int animationID, float time)
	{
		animations[animationID]->setAnimationTimeBetweenFrames(time);
	}
	void sprite::setAnimationFullTime(int animationID, float time)
	{
		animations[animationID]->setAnimationFullTime(time);
	}
	void sprite::setTextureCoordinates(glm::vec2 coord1, glm::vec2 coord2, glm::vec2 coord3, glm::vec2 coord4)
	{
		baseUVCoords[0] = coord1;
		baseUVCoords[1] = coord2;
		baseUVCoords[2] = coord3;
		baseUVCoords[3] = coord4;
	}
	void sprite::setTexture(renderer* render, const char* filePathImage, bool invertImage)
	{
		_renderer = render;
		float vertex[24] =
		{
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f
		};
		unsigned int indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};
		_renderer->createBaseBuffer(VAO, VBO, EBO);
		_renderer->bindBaseBufferRequest(VAO, VBO, EBO, vertex, sizeof(vertex), indices, sizeof(indices));
		_vertices = 6;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		float UVs[8] =
		{
			baseUVCoords[0].x, baseUVCoords[0].y,
			baseUVCoords[1].x, baseUVCoords[1].y,
			baseUVCoords[2].x, baseUVCoords[2].y,
			baseUVCoords[3].x, baseUVCoords[3].y
		};
		_renderer->createExtraBuffer(bufferPosUVs, 1);
		_renderer->bindExtraBuffer(bufferPosUVs, UVs, sizeof(UVs), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);

		baseTexture = new textureData(textureImporter::loadTexture(filePathImage, invertImage));
	}
	void sprite::deinit()
	{
		_renderer->deleteBaseBuffer(VAO, VBO, EBO);
		_renderer->deleteExtraBuffer(bufferPosUVs, 1);
		glDeleteTextures(1, &baseTexture->ID);
		delete baseTexture;
		for (unsigned int i = 0; i < animations.size(); i++)
		{
			delete animations[i];
		}
	}
}
