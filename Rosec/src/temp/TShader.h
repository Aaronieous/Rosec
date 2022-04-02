#pragma once

#include "Rosec/Shader.h"


namespace Rosec {

	class TShader : public Shader
	{
	public:
		TShader();
		~TShader();
	protected:
		void Init();

		bool LoadImpl(const std::string& name, const std::string& filePath) override;
		bool BindImpl(const std::string& name) override;
		bool DeleteImpl(const std::string& name) override;
	
		std::unordered_map<std::string, unsigned int> m_ID;
	};

}
