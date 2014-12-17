#include "Input.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "Random.hpp"

int main()
{
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW.\n");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Satellite", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW.\n");
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

	World world;
	Renderer renderer;

	double last_time = glfwGetTime();
	double current_time = last_time;
	double total_time = 0.0;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);

		last_time = current_time;
		current_time = glfwGetTime();

		double dt = current_time - last_time;
		total_time += dt;

		world.Update(dt);

		renderer.Clear();

		const std::vector<Entity*> entities = world.GetEntities();
		
		for (Entity* entity : entities)
		{
			glm::vec2 position = entity->GetPosition();
			glm::vec2 size = entity->GetSize();
			float rotation = entity->GetRotation();

			renderer.RenderQuad(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y, rotation + 3.141592654 / 2, 0, 0, 16, 16);
		}

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}
