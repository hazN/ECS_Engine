#include "RenderCommand.h"
#include "../OpenGL/OpenGLRendererAPI.h"

namespace sas
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}