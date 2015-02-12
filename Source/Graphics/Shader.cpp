#include "Shader.hpp"

void Shader::Initialize()
{
	Load("base");
	Load("fill");
	Load("line");
	g_current_program = &g_programs.find("base")->second;
}

void Shader::Load(const std::string& name)
{
	std::string path = "../../Resource/Shader/" + name;

	//
	// Vertex Shader
	//

	std::ifstream vertex_file((path + ".vert").c_str());
	if (!vertex_file)
		return;

	std::stringstream vertex_buffer;
	vertex_buffer << vertex_file.rdbuf();
	vertex_file.close();

	std::string vertex_source = vertex_buffer.str();
	const char* vertex_source_c = vertex_source.c_str();

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source_c, nullptr);
	glCompileShader(vertex_shader);

	GLint status;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);

		GLchar* info_log = new GLchar[length];
		glGetShaderInfoLog(vertex_shader, length, nullptr, info_log);

		printf("%s.vert failed to compile:\n%s\n", path.c_str(), info_log);

		delete[] info_log;
	}

	//
	// Fragment Shader
	//

	std::ifstream fragment_file((path + ".frag").c_str());
	if (!fragment_file)
		return;

	std::stringstream fragment_buffer;
	fragment_buffer << fragment_file.rdbuf();
	fragment_file.close();

	std::string fragment_source = fragment_buffer.str();
	const char* fragment_source_c = fragment_source.c_str();

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source_c, nullptr);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);

		GLchar* info_log = new GLchar[length];
		glGetShaderInfoLog(fragment_shader, length, nullptr, info_log);

		printf("%s.frag failed to compile:\n%s\n", path.c_str(), info_log);

		delete[] info_log;
	}

	GLint id = glCreateProgram();
	glAttachShader(id, vertex_shader);
	glAttachShader(id, fragment_shader);
	glLinkProgram(id);

	glDetachShader(id, vertex_shader);
	glDetachShader(id, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	Program program;
	program.m_id = id;
	program.m_binded = false;

	g_programs.emplace(name, program);
}

void Shader::Bind(const std::string& name)
{
	auto it = g_programs.find(name);
	if (it == g_programs.end())
		return;

	if (it->second.m_binded)
		return;

	glUseProgram(it->second.m_id);

	it->second.m_binded = true;
	g_current_program = &it->second;

	// Unbind other shaders.
	for (auto other = g_programs.begin(); other != g_programs.end(); other++)
	{
		if (other != it)
			other->second.m_binded = false;
	}
}

void Shader::Unbind(const std::string& name)
{
	auto it = g_programs.find(name);
	if (it == g_programs.end())
		return;

	if (!it->second.m_binded)
		return;

	glUseProgram(0);

	it->second.m_binded = false;
	g_current_program = nullptr;
}

void Shader::SetUniformMatrix(const std::string& uniform, const glm::mat4& value)
{
	assert(g_current_program != nullptr);
	assert(g_current_program->m_binded);

	GLint location = glGetUniformLocation(g_current_program->m_id, uniform.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniformVec2(const std::string& uniform, const glm::vec2& value)
{
	assert(g_current_program != nullptr);
	assert(g_current_program->m_binded);

	GLint location = glGetUniformLocation(g_current_program->m_id, uniform.c_str());
	glUniform2f(location, value.x, value.y);
}

void Shader::SetUniformVec3(const std::string& uniform, const glm::vec3& value)
{
	assert(g_current_program != nullptr);
	assert(g_current_program->m_binded);

	GLint location = glGetUniformLocation(g_current_program->m_id, uniform.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniformVec4(const std::string& uniform, const glm::vec4& value)
{
	assert(g_current_program != nullptr);
	assert(g_current_program->m_binded);

	GLint location = glGetUniformLocation(g_current_program->m_id, uniform.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniformInt(const std::string& uniform, GLint value)
{
	assert(g_current_program != nullptr);
	assert(g_current_program->m_binded);

	GLint location = glGetUniformLocation(g_current_program->m_id, uniform.c_str());
	glUniform1i(location, value);
}
