
#include "Shader.hpp"
#include <fstream>
#include <cassert>

namespace OpenGLAssignment
{
	Shader::Shader(SourceCode & source_code, GLenum shader_type)
		:id(0)
	{
		
			//Creacion del shader
			id = glCreateShader(shader_type);
			const char * shader_code_list[] = { source_code };
			const GLint  shader_size_list[] = { (GLint)source_code.size() };

			glShaderSource(id, 1, shader_code_list, shader_size_list);
			//Compilacion del sahder
			glCompileShader(id);

			GLint succeeded = GL_FALSE;
			glGetShaderiv(id, GL_COMPILE_STATUS, &succeeded);

			//Comprobacion de error
			if (!succeeded)
			{
				GLint log_length;

				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
				
				glDeleteShader(id);
				id = 0;
				assert(false);
			}
		
	}

	Shader::~Shader()
	{
		glDeleteShader(id);
		id = 0;
	}

	Shader::SourceCode Shader::SourceCode::from_file(const std::string & file_path)
	{
		using std::fstream;
		SourceCode source_code;

		//Lectura de archivo
		fstream file_reader(file_path, fstream::in | fstream::binary);

		if (file_reader.is_open())
		{
			file_reader.seekg(0, fstream::end);

			size_t file_size = size_t(file_reader.tellg());
			if (file_reader.good() && file_size > 0)
			{
				source_code.string.resize(file_size);

				file_reader.seekg(0, fstream::beg);

				//Paso de archivo a SourceCode
				file_reader.read(&source_code.string.front(), file_size);

				assert(file_reader.good());
			}
		}

		else
			assert(false);

		return (source_code);
	}
}