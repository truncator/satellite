#include "Input.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "Random.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

int main()
{
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW.\n");
		return 1;
	}

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	// Request OpenGL 3.3 Core Profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Satellite", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Vsync.
	glfwSwapInterval(0);

	/*
	const GLubyte* gl_vendor = glGetString(GL_VENDOR);
	const GLubyte* gl_version = glGetString(GL_VERSION);
	const GLubyte* glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

	printf("Vendor: %s\nVersion: %s\nGLSL: %s\n", gl_vendor, gl_version, glsl_version);
	*/

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW.\n");
		return 1;
	}

	if (!glewIsSupported("GL_VERSION_3_3"))
	{
		printf("OpenGL 3.3 is not supported.\n");
		return 1;
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Input::Initialize(window);
	Shader::Initialize();
	Texture::Initialize();
	Random::Initialize();

	Renderer renderer = Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

	World world;

	double last_time = glfwGetTime();
	double current_time = last_time;
	double total_time = 0.0;

	//
	// Main Loop
	//

	while (!glfwWindowShouldClose(window))
	{
		//
		// Update
		//

		glfwPollEvents();

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);

		last_time = current_time;
		current_time = glfwGetTime();

		double dt = current_time - last_time;
		total_time += dt;

		world.Update(dt);

		//
		// Render
		//

		renderer.Prepare();

		SpriteBatch& sprite_batch = renderer.GetSpriteBatch();
		sprite_batch.Begin();

		const std::vector<Entity*> entities = world.GetEntities();

		for (Entity* entity : entities)
		{
			glm::vec2 position = entity->GetPosition();
			glm::vec2 size = entity->GetSize();
			float rotation = entity->GetRotation();

			sprite_batch.DrawQuad(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y, rotation - 3.141592654 / 2, 0, 0, 16, 16);
		}

		sprite_batch.End();
		renderer.Cleanup();

		glfwSwapBuffers(window);
	}

	//
	// Cleanup
	//

	glfwTerminate();

	return 0;
}
