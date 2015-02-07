#pragma once

#include "Precompiled.hpp"

//
// Shader
//     Manages shader programs.
//

namespace Shader
{

	//
	// Program
	//

	struct Program
	{
		GLint m_id;
		bool m_binded;

		Program() :
			m_id(-1), m_binded(false)
		{
		}
	};


	void Initialize();
	void Load(const std::string& name);

	void Bind(const std::string& name);
	void Unbind(const std::string& name);

	void SetUniformMatrix(const std::string& uniform, const glm::mat4& value);
	void SetUniformVec2(const std::string& uniform, const glm::vec2& value);
	void SetUniformVec3(const std::string& uniform, const glm::vec3& value);
	void SetUniformVec4(const std::string& uniform, const glm::vec4& value);
	void SetUniformInt(const std::string& uniform, GLint value);
}

typedef std::unordered_map<std::string, Shader::Program> ProgramList;

static ProgramList g_programs;
static Shader::Program* g_current_program = nullptr;
