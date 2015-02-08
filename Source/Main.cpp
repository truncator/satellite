#include "Input.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "Random.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/LineRenderer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"
#include "Transform.hpp"

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

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "floating", nullptr, nullptr);
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
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Input::Initialize(window);
	Shader::Initialize();
	Texture::Initialize();
	Random::Initialize();

	int test_width = SCREEN_WIDTH / 2;
	int test_height = SCREEN_HEIGHT / 2;

	std::vector<unsigned char> test_data(test_width * test_height * 4, 0);
	for (int y = 0; y < test_height; y++)
	{
		for (int x = 0; x < test_width; x++)
		{
			if (Random::Float() < 0.03f)
			{
				int brightness = Random::Int(20, 80);

				test_data[y * test_width * 4 + x * 4 + 0] = brightness;
				test_data[y * test_width * 4 + x * 4 + 1] = brightness;
				test_data[y * test_width * 4 + x * 4 + 2] = brightness;

				if (Random::Float() < 0.05f)
					test_data[y * test_width * 4 + x * 4 + 0] += 40;
			}
			else
			{
				test_data[y * test_width * 4 + x * 4 + 0] = 0;
				test_data[y * test_width * 4 + x * 4 + 1] = 0;
				test_data[y * test_width * 4 + x * 4 + 2] = 0;

				if (Random::Float() < 0.1f)
					test_data[y * test_width * 4 + x * 4 + 2] = Random::Int(0, 15);
			}

			test_data[y * test_width * 4 + x * 4 + 3] = 255;
		}
	}

	Texture::Load(std::string("test"), &test_data[0], test_width, test_height);

	Renderer renderer = Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
	LineRenderer line_renderer;

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

		Input::Reset();
		Input::Update();

		if (Input::IsKeyDown(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);

		if (Input::IsKeyDown(GLFW_KEY_EQUAL))
			renderer.Zoom(-0.5f);
		if (Input::IsKeyDown(GLFW_KEY_MINUS))
			renderer.Zoom(0.5f);
		#if 0
		if (Input::IsKeyDownNew(GLFW_KEY_EQUAL))
			renderer.Zoom(-0.5f);
		if (Input::IsKeyDownNew(GLFW_KEY_MINUS))
			renderer.Zoom(0.5f);
		#endif

		last_time = current_time;
		current_time = glfwGetTime();

		double dt = current_time - last_time;
		//dt *= 48.0f;
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
			Transform& transform = entity->GetTransform();
			Material& material = entity->GetMaterial();

			glm::vec2 position = transform.GetPosition();
			glm::vec2 size = transform.GetSize();
			float rotation = transform.GetRotation() + glm::pi<float>() / 2.0f;

			glm::vec3 color = material.GetColor();
			glm::vec4 uv = entity->GetMaterial().GetUV() / 1024.0f;

			sprite_batch.DrawQuad(position - size / 2.0f, size, rotation, color, uv, 0.0f);

			if (!transform.IsStatic())
			{
				Entity* nearest = world.GetNearestAttractor(entity);
				if (nearest == nullptr)
					continue;

				nearest->GetTransform().Attract(transform, dt);
				//line_renderer.DrawLine(position, nearest->GetTransform().GetPosition(), nearest->GetMaterial().GetColor());
				//nearest->GetMaterial().SetColor(glm::vec3(Random::Float(), Random::Float(), Random::Float()));
			}
		}

		sprite_batch.End();
		sprite_batch.Begin();

		Texture::Bind("test");
		sprite_batch.DrawQuad(glm::vec2(0.0f), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), 0.0f, glm::vec3(1.0f), glm::vec4(0.0f, 0.0f, test_width, test_height) / glm::vec4(test_width, test_height, test_width, test_height), 0.5f);

		sprite_batch.End();
		line_renderer.Draw();
		renderer.Cleanup();

		glfwSwapBuffers(window);
	}

	//
	// Cleanup
	//

	glfwTerminate();

	return 0;
}
