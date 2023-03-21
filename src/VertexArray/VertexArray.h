#pragma once
#include "Export.h"
#include "VertexBuffer/VertexBuffer.h"
namespace Engine
{
	class VertexBufferLayout;
	class ENGINE_API VertexArray
	{
	private:
		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
	};
}