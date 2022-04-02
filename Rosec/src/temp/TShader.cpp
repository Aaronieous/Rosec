#include "rscpch.h"
#include "TShader.h"

#include <glad/glad.h>

namespace Rosec {

	Shader* Shader::s_Instance = nullptr;

	Shader* Shader::Create()
	{
		return new TShader();
	}

	TShader::TShader()
	{
		Shader::s_Instance = this;
		Init();
	}

	TShader::~TShader()
	{
	}

	void TShader::Init()
	{
		Load("default", "C:/dev/Rosec/Rosec/src/temp/Shaders/Vertex.shader|C:/dev/Rosec/Rosec/src/temp/Shaders/Fragment.shader|");
		Bind();
	}

	bool TShader::LoadImpl(const std::string& name, const std::string& filePath)
	{
		unsigned int shaderType;
		if (m_ID.find(name) != m_ID.end())
		{
			RSC_CORE_ERROR("Shader {0} already exists!", name.c_str());
			return false;
		}
		else
		{
			unsigned int* ID = &m_ID[name];
			*ID = glCreateProgram();
			std::string ssFile;
			for (char letter : filePath)
			{
				if (letter != '|')
				{
					if(letter != ' ')
						ssFile += letter;
				}
				else
				{
					//RSC_CORE_INFO("{0}", ssFile);
					std::string ssShader;
					std::ifstream fsFile(ssFile);
					
					if (fsFile.is_open())
					{
						for (std::string line; std::getline(fsFile, line);)
						{
							if (line.find("#vertex") != std::string::npos)
							{
								shaderType = glCreateShader(GL_VERTEX_SHADER);
								RSC_CORE_INFO("Linking vertex shader!");
							}
							else if (line.find("#fragment") != std::string::npos)
							{
								shaderType = glCreateShader(GL_FRAGMENT_SHADER);
								RSC_CORE_INFO("Linking fragment shader!");
							}
							else if (line.find("#geometry") != std::string::npos)
							{
								shaderType = glCreateShader(GL_GEOMETRY_SHADER);
								RSC_CORE_INFO("Linking geometry shader!");
							}
							else if (line.find("#compute") != std::string::npos)
							{
								shaderType = glCreateShader(GL_COMPUTE_SHADER);
								RSC_CORE_INFO("Linking compute shader!");
							}
							else if (line.find("#tesseval") != std::string::npos)
							{
								shaderType = glCreateShader(GL_TESS_EVALUATION_SHADER);
								RSC_CORE_INFO("Linking tesseval shader!");
							}
							else if (line.find("#tesscont") != std::string::npos)
							{
								shaderType = glCreateShader(GL_TESS_CONTROL_SHADER);
								RSC_CORE_INFO("Linking tesscont shader!");
							}
							else
								ssShader += line + '\n';
						}

						std::string source = ssShader;
						char const* sourcePoint = source.c_str();
						glShaderSource(shaderType, 1, &sourcePoint, NULL);
						glCompileShader(shaderType);

						int shader_compiled;
						glGetShaderiv(shaderType, GL_COMPILE_STATUS, &shader_compiled);
						if (!shader_compiled)
						{
							int InfoLogLength;
							glGetShaderiv(shaderType, GL_INFO_LOG_LENGTH, &InfoLogLength);
							std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
							glGetShaderInfoLog(shaderType, InfoLogLength, NULL, &ShaderErrorMessage[0]);
							std::string errorMessage;
							for (char letter : ShaderErrorMessage)
								errorMessage += letter;
							RSC_CORE_ERROR("SHADER ERROR: {0}", errorMessage);

							return false;
						}
						glAttachShader(*ID, shaderType);
						
						
					}
					else
					{
						RSC_CORE_ERROR("{0} is not a valid file path!", ssFile);

						return false;
					}
					ssFile.clear();
				}
			}
			RSC_CORE_INFO("Shader {0} successfully added!", name.c_str());
			return true;
		}
		return false;
	}

	bool TShader::BindImpl(const std::string& name)
	{
		if (m_ID.find(name) != m_ID.end())
		{
			unsigned int* ID = &m_ID[name];
			RSC_CORE_INFO("Binding Shader {0}!", name);
			glLinkProgram(*ID);

			int program_linked;
			glGetProgramiv(*ID, GL_LINK_STATUS, &program_linked);
			if (!program_linked)
			{
				int InfoLogLength;
				glGetProgramiv(*ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
				std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
				glGetProgramInfoLog(*ID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
				std::string errorMessage;
				for (char letter : ProgramErrorMessage)
					errorMessage += letter;
				RSC_CORE_ERROR("SHADER ERROR: {0}", errorMessage);

				return false;
			}
			else
				RSC_CORE_INFO("Shader {0} successfully bound!", name);
				return true;
		}
		else
		{
			RSC_CORE_ERROR("{0} is not an existng shader!", name);
			return false;
		}
		return false;
	}

	bool TShader::DeleteImpl(const std::string& name)
	{
		//Delete shaders by name
		return true;
	}

}