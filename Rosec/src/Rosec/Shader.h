#pragma once

#include "rscpch.h"

namespace Rosec {

	class ROSEC_API Shader
	{
	public:
		inline static bool Load(const std::string& name, const std::string& filePath) { return s_Instance->LoadImpl(name, filePath); }
		inline static bool Bind(const std::string& name = "default") { return s_Instance->BindImpl(name); }
		inline static bool Delete(const std::string& name) { return s_Instance->DeleteImpl(name); }

		inline static Shader& Get() { return *s_Instance; }
		static Shader* Create();

	protected:
		virtual bool LoadImpl(const std::string& name, const std::string& filePath) = 0;
		virtual bool BindImpl(const std::string& name) = 0;
		virtual bool DeleteImpl(const std::string& name) = 0;
		
		static Shader* s_Instance;
	};

}