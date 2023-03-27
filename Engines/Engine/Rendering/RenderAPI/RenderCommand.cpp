#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;