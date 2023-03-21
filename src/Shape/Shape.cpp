#include <GL/glew.h>
#include "Shape.h"
namespace Engine
{
	Shape::Shape(float minX, float minY, float maxX, float maxY)
	{
		positions[0] = minX;
		positions[1] = maxY;
		positions[2] = topLeft.x;					//topleft
		positions[3] = topLeft.y;
	/*	topLeft.x = minXAtlas;
		topLeft.y = minYAtlas;*/

		positions[4] = maxX;
		positions[5] = maxY;					//topright
		positions[6] = topRight.x;
		positions[7] = topRight.y;
		/*topRight.x = maxXAtlas;
		topRight.y = minYAtlas;*/

		positions[8] = maxX;
		positions[9] = minY;					//bottomright
		positions[10] = bottomRight.x;
		positions[11] = bottomRight.y;
	/*	bottomRight.x = maxXAtlas;
		bottomRight.y = maxYAtlas;*/

		positions[12] = minX;
		positions[13] = minY;					//bottomleft
		positions[14] = bottomLeft.x;
		positions[15] = bottomLeft.y;
		/*bottomLeft.x = minXAtlas;
		bottomLeft.y = maxYAtlas;*/

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;

		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

		height = maxY - minY;
		width = maxX - minX;
		UpdateBuffer();
	}
	glm::mat4 Shape::GetModel()
	{
		return model;
	}
	void Shape::UpdateBuffer()
	{
		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
	}
	void Shape::SetModel(glm::mat4 _model)
	{
		model = _model;
	}
	bool Shape::IsAnimationRunning()
	{
		return animationactive;
	}
	void Shape::Animate(int currentRow, int totalFrames)
	{
		if (animation == NULL) {
			animation = new Animation(rows, columns, m_Texture->GetWidth(), m_Texture->GetHeight(), totalAnimations);
		}
		if (animation->PlayAnimation(columns, currentRow, totalFrames, topRight, bottomRight, bottomLeft, topLeft))
		{
			positions[2] = topLeft.x;
			positions[3] = topRight.y;

			positions[6] = bottomRight.x;
			positions[7] = topRight.y;

			positions[10] = bottomRight.x;
			positions[11] = bottomLeft.y;
			
			positions[14] = topLeft.x;
			positions[15] = bottomLeft.y;

			UpdateBuffer();
		}
	}
	void Shape::Draw()
	{
		if (!animationactive) {
			m_Texture->Bind();
		}
	}
	void Shape::SetPos(glm::vec3 pos)
	{
		m_translation = pos;
		model = glm::translate(model, pos);
		model = glm::translate(glm::mat4(1.0f), GetPos());
	}
	void Shape::SetPath(std::string Path)
	{
		path = Path;
	}
	void Shape::SetTexturePath()
	{
		m_Texture = std::make_unique<Texture>(path);
	}
	void Shape::SetRot(glm::vec3 rot)
	{
		model = glm::rotate(model, (float)glfwGetTime(), rot);
	}
	void Shape::SetScale(glm::vec3 scale)
	{
		m_scale = scale;
		model = glm::scale(model, scale);
	}
	void Shape::SetTime(float Time)
	{
		if (animation != NULL) {
			animation->SetTimePerAnimation(Time);
		}
	}
	void Shape::SetTexture(std::unique_ptr<Texture> m_Texture)
	{

	}
	void Shape::SetRigidBody(bool RigidBody)
	{
		rigidbody = RigidBody;
	}
	void Shape::SetAnimation(Animation* Animation)
	{
		animation = Animation;
	}
	glm::vec3 Shape::GetPos()
	{
		return m_translation;
	}
	std::string Shape::GetPath()
	{
		return path;
	}
	glm::vec4 Shape::GetRot()
	{
		return m_rotation;
	}
	glm::vec3 Shape::GetScale()
	{
		return m_scale;
	}
	float Shape::GetTime()
	{
		return time;
	}
	float Shape::GetWidth()
	{
		return width;
	}
	float Shape::GetHeight()
	{
		return height;
	}
	bool Shape::GetRigidBody()
	{
		return rigidbody;
	}
	Animation* Shape::GetAnimation()
	{
		return animation;
	}
}