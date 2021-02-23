#include "Application.h"

float score = 0.0f, ospeed = 0.7f;
bool resume = false;

Application* Application::s_Application = nullptr;

glm::vec3 hsv2rgb(const glm::vec3& rgb)
{
	float hh, p, q, t, ff;
	int i;
	glm::vec3 hsv;

	if (rgb.s <= 0.0f)
	{
		hsv.r = rgb.z;
		hsv.g = rgb.z;
		hsv.b = rgb.z;
		return hsv;
	}
	hh = rgb.x;
	if (hh >= 360.0f)
		hh = 0.0f;
	hh /= 60.0f;
	i = (int)hh;
	ff = hh - i;
	p = rgb.z * (1.0f - rgb.y);
	q = rgb.z * (1.0f - (rgb.y * ff));
	t = rgb.z * (1.0f - (rgb.y * (1.0f - ff)));

	switch (i)
	{
		case 0:
			hsv.r = rgb.z;
			hsv.g = t;
			hsv.b = p;
			break;
		case 1:
			hsv.r = q;
			hsv.g = rgb.z;
			hsv.b = p;
			break;
		case 2:
			hsv.r = p;
			hsv.g = rgb.z;
			hsv.b = t;
			break;
		case 3:
			hsv.r = p;
			hsv.g = q;
			hsv.b = rgb.z;
			break;
		case 4:
			hsv.r = t;
			hsv.g = p;
			hsv.b = rgb.z;
			break;
		default:
			hsv.r = rgb.z;
			hsv.g = p;
			hsv.b = q;
	}

	return hsv;
}

Application::Application()
{
	Init();

	ME::Addon::ParticleProps particleprop;

	Ref<ME::Mesh> parent = ME::GenRect("parentofparticles", { 0.0f, 0.0f }, { 20.0f, 20.0f }, 3);
	particleprop.parent = parent;
	particleprop.color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	particleprop.count = 5;
	particleprop.lifetime = 5;
	particleprop.transform = glm::scale(glm::translate(glm::identity<glm::mat4>(), { -2.0f, 0.0f, 0.0f }), { 0.99f, 0.99f, 1.0f });
	m_Smoke = CreateScope<ME::Addon::ParticleSystem>(particleprop);


	parent = ME::GenRect("parentofparticles", { 0.0f, 0.0f }, { 30.0f, 30.0f }, 4);
	particleprop.parent = parent;
	particleprop.color = glm::vec4(1.0f, 0.3f, 0.0f, 1.0f);
	particleprop.count = 20;
	particleprop.lifetime = 3;
	particleprop.transform = glm::translate(glm::scale(glm::identity<glm::mat4>(), { 0.95, 0.95, 1.0 }), { -1.0f, 0.0f, 0.0f });
	m_Fire = CreateScope<ME::Addon::ParticleSystem>(particleprop);

	s_Application = this;
}

Application::~Application()
{
	renderer.reset();
}

void Application::Init()
{
	Window::WindowProperty windowprop("TheGame", 1280, 720);
	window = CreateRef<Window::Windows::WindowsWindow>(windowprop);
	window->SetEventCallBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	renderer = CreateRef<ME::Renderer::OpenGL::OpenGLRendererAPI>();
	renderer->SetViewPortSize(1580, 720);
	renderer->Init();
}

void Application::Run()
{
	
	ME::VERTEX Rocketvertex[] =
	{
		{ 270.0f, 570.0f, 1.0f, 0.0f, 0.0f, -1.0f},
		{ 300.0f, 570.0f, 1.0f, 1.0f, 0.0f, -1.0f},
		{ 300.0f, 610.0f, 1.0f, 1.0f, 1.0f, -1.0f},
		{ 270.0f, 610.0f, 1.0f, 0.0f, 1.0f, -1.0f}
	};

	ME::VERTEX Obstaclevertex1[] =
	{
		{200.0f, 1350.0f, 1.0f, 0.0f, 1.0f},
		{800.0f, 1350.0f, 1.0f, 1.0f, 1.0f},
		{800.0f,  650.0f, 1.0f, 1.0f, 0.0f},
		{200.0f,  650.0f, 1.0f, 0.0f, 0.0f}
	};

	ME::VERTEX Obstaclevertex2[] =
	{
		{600.0f,  1350.0f, 1.0f, 0.0f, 1.0f},
		{1200.0f, 1350.0f, 1.0f, 1.0f, 1.0f},
		{1200.0f,  650.0f, 1.0f, 1.0f, 0.0f},
		{600.0f,   650.0f, 1.0f, 0.0f, 0.0f}
	};

	ME::VERTEX Obstaclevertex3[] =
	{
		{1000.0f, 1350.0f, 1.0f, 0.0f, 1.0f},
		{1600.0f, 1350.0f, 1.0f, 1.0f, 1.0f},
		{1600.0f,  650.0f, 1.0f, 1.0f, 0.0f},
		{1000.0f,  650.0f, 1.0f, 0.0f, 0.0f}
	};

	ME::VERTEX Obstaclevertex4[] =
	{
		{1400.0f, 1350.0f, 1.0f, 0.0f, 1.0f},
		{2000.0f, 1350.0f, 1.0f, 1.0f, 1.0f},
		{2000.0f,  650.0f, 1.0f, 1.0f, 0.0f},
		{1400.0f,  650.0f, 1.0f, 0.0f, 0.0f}
	};

	ME::VERTEX Obstaclevertex10[] =
	{
		{200.0f, -30.0f, 1.0f, 0.0f, 1.0f},
		{800.0f, -30.0f, 1.0f, 1.0f, 1.0f},
		{800.0f, 650.0f, 1.0f, 1.0f, 0.0f},
		{200.0f, 650.0f, 1.0f, 0.0f, 0.0f}
	};

	ME::VERTEX Obstaclevertex11[] =
	{
		{600.0f,  -30.0f, 1.0f, 0.0f, 1.0f},
		{1200.0f, -30.0f, 1.0f, 1.0f, 1.0f},
		{1200.0f, 650.0f, 1.0f, 1.0f, 0.0f},
		{600.0f,  650.0f, 1.0f, 0.0f, 0.0f}
	};

	ME::VERTEX Obstaclevertex12[] =
	{
		{1000.0f, -30.0f, 1.0f, 0.0f, 1.0f},
		{1600.0f, -30.0f, 1.0f, 1.0f, 1.0f},
		{1600.0f, 650.0f, 1.0f, 1.0f, 0.0f},
		{1000.0f, 650.0f, 1.0f, 0.0f, 0.0f}
	};

	ME::VERTEX Obstaclevertex13[] =
	{
		{1400.0f, -30.0f, 1.0f, 0.0f, 1.0f},
		{2000.0f, -30.0f, 1.0f, 1.0f, 1.0f},
		{2000.0f, 650.0f, 1.0f, 1.0f, 0.0f},
		{1400.0f, 650.0f, 1.0f, 0.0f, 0.0f}
	};

	ME::VERTEX WallTopvertex[] =
	{
		{-2000.0f, 2300.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{ 1280.0f, 2300.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{ 1280.0f, 1000.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{-2000.0f, 1000.0f, 1.0f, 0.0f, 0.0f, 1.0f}
	};

	ME::VERTEX WallBottomvertex[] =
	{
		{-2000.0f,-2000.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{1280.0f, -2000.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{1280.0f,   320.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{-2000.0f,  320.0f, 1.0f, 0.0f, 0.0f, 1.0f}
	};

	ME::VERTEX Vignettevertex[] =
	{
		{   0.0f, 300.0f, 1.0f, 0.0f, 0.0f, 2.0f},
		{1280.0f, 300.0f, 1.0f, 0.0f, 0.0f, 2.0f},
		{1280.0f, 1020.0f, 1.0f, 0.0f, 0.0f, 2.0f},
		{   0.0f, 1020.0f, 1.0f, 0.0f, 0.0f, 2.0f}
	};

	unsigned int Commonindex[] =
	{
		0,1,2,
		2,3,0
	};

	Ref<ME::Mesh> Rocket = CreateRef<ME::Mesh>("The Me");
	Rocket->BufferVertices(Rocketvertex, sizeof(Rocketvertex)/sizeof(ME::VERTEX));
	Rocket->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));
	Rocket->Rotate({ 0.0f, 0.0f, 90.0f });
	Rocket->Translate({ -20.0f, 0.0f, 0.0f });
	Rocket->SetReset(Rocket->GetVertices());

	Ref<ME::Mesh> Obstacle1 = CreateRef<ME::Mesh>("Obstacle1");
	Obstacle1->BufferVertices(Obstaclevertex1, sizeof(Obstaclevertex1) / sizeof(ME::VERTEX));
	Obstacle1->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	Ref<ME::Mesh> Obstacle2 = CreateRef<ME::Mesh>("Obstacle2");
	Obstacle2->BufferVertices(Obstaclevertex2, sizeof(Obstaclevertex2) / sizeof(ME::VERTEX));
	Obstacle2->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	Ref<ME::Mesh> Obstacle3 = CreateRef<ME::Mesh>("Obstacle3");
	Obstacle3->BufferVertices(Obstaclevertex3, sizeof(Obstaclevertex3) / sizeof(ME::VERTEX));
	Obstacle3->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	Ref<ME::Mesh> Obstacle4 = CreateRef<ME::Mesh>("Obstacle4");
	Obstacle4->BufferVertices(Obstaclevertex4, sizeof(Obstaclevertex4) / sizeof(ME::VERTEX));
	Obstacle4->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	Ref<ME::Mesh> Obstacle10 = CreateRef<ME::Mesh>("Obstacle10");
	Obstacle10->BufferVertices(Obstaclevertex10, sizeof(Obstaclevertex10) / sizeof(ME::VERTEX));
	Obstacle10->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	Ref<ME::Mesh> Obstacle11 = CreateRef<ME::Mesh>("Obstacle11");
	Obstacle11->BufferVertices(Obstaclevertex11, sizeof(Obstaclevertex11) / sizeof(ME::VERTEX));
	Obstacle11->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	Ref<ME::Mesh> Obstacle12 = CreateRef<ME::Mesh>("Obstacle12");
	Obstacle12->BufferVertices(Obstaclevertex12, sizeof(Obstaclevertex12) / sizeof(ME::VERTEX));
	Obstacle12->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	Ref<ME::Mesh> Obstacle13 = CreateRef<ME::Mesh>("Obstacle13");
	Obstacle13->BufferVertices(Obstaclevertex13, sizeof(Obstaclevertex13) / sizeof(ME::VERTEX));
	Obstacle13->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	std::vector<Ref<ME::Mesh>> Obstacle_colltop{ Obstacle1 , Obstacle2 , Obstacle3, Obstacle4 };

	std::vector<Ref<ME::Mesh>> Obstacle_collbottom{ Obstacle10 , Obstacle11 , Obstacle12, Obstacle13 };

	Ref<ME::Mesh> WallTop = CreateRef<ME::Mesh>("WallTop");
	WallTop->BufferVertices(WallTopvertex, sizeof(WallTopvertex) / sizeof(ME::VERTEX));
	WallTop->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	Ref<ME::Mesh> WallBottom = CreateRef<ME::Mesh>("WallBottom");
	WallBottom->BufferVertices(WallBottomvertex, sizeof(WallBottomvertex) / sizeof(ME::VERTEX));
	WallBottom->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	Ref<ME::Mesh> Vignette = CreateRef<ME::Mesh>("Vignette");
	Vignette->BufferVertices(Vignettevertex, sizeof(Vignettevertex) / sizeof(ME::VERTEX));
	Vignette->BufferIndices(Commonindex, sizeof(Commonindex) / sizeof(unsigned int));

	ME::MeshQueue meshqueue;
	meshqueue.PushMesh(Rocket);
	meshqueue.PushMesh(WallTop);
	meshqueue.PushMesh(WallBottom);

	ME::MeshQueue Obstacles;
	Obstacles.PushMeshes(Obstacle_colltop);
	Obstacles.PushMeshes(Obstacle_collbottom);
	Obstacles.PushMesh(Vignette);

	ME::MeshQueue Particles;
	Particles.PushAddon(*m_Smoke);
	Particles.PushAddon(*m_Fire);

	Ref<ME::Renderer::Shader> shader = CreateRef<ME::Renderer::OpenGL::OpenGLShader>("shader\\Basic.shader");
	ME::Renderer::OpenGL::OpenGLTexture texture1("res\\Rocket.png");
	ME::Renderer::OpenGL::OpenGLTexture texture2("res\\Obstacles.png");

	glm::mat4 MVP = glm::ortho(0.0f, 1106.0f, 300.0f, 804.0f, -1.0f, 1.0f);
	MVP = glm::translate(MVP, { 0, -80.0f, 0.0f });

	renderer->SetClearColor({ 50.0f / 256.0f, 50.0f / 256.0f, 50.0f / 256.0f, 1.0f});

	renderer->AddRenderSubmition(Particles, []() {});
	renderer->AddRenderSubmition(meshqueue, [&shader, &texture1]()
		{
			texture1.Bind();
			int hero = texture1.GetSlot();
			shader->SetUniforms1i("u_Sampler", hero);
		});
	renderer->AddRenderSubmition(Obstacles, [&shader, &texture2]()
		{
			texture2.Bind();
			int obstacle = texture2.GetSlot();
			shader->SetUniforms1i("u_Sampler", obstacle);
		});

	glm::vec3 gravity = glm::vec3(0.0f, -5.8f, 0.0f), force = glm::vec3(0.0f, 15.0f, 0.0f), netforce = { 0.0f, 0.0f, 0.0f }, speed = { 0.0f, 0.0f, 0.0f };
	glm::mat4 transform;

	std::linear_congruential_engine<unsigned short, 1, 47, 200> rand;
	int rot = 0;
	glm::vec3 trans(1.0f, 1.0f, 0.0f);
	/*
	Window::Layer::imguiLayer imgui;
	imgui.OnAttach();
	imgui.SetDrawData([]()
		{
			ImGui::Text(std::to_string(ImGui::GetIO().Framerate).c_str());
		});
	*/
	ME::Utils::Time::Timer<ME::Utils::Time::Precision::SEC> particletimer;
	ME::Utils::Time::timer timer;
	ME::Utils::Time::Timer<ME::Utils::Time::Precision::SEC> click;
	float factor = 1;
	uint8_t framerate = 0;
	while (Running)
	{

		if (resume)
		{
			netforce = gravity;
			if (window->IsKeyPressed(Event::Key::Space))
			{
				netforce = force + gravity;
				if (rot < 15)
				{
					Rocket->Rotate({ 0.0f, 0.0f, -7.0f });
					rot += 2;
				}
			}
			else
				if (rot > -15)
				{
					Rocket->Rotate({ 0.0f, 0.0f, 3.5f });
					rot--;
				}
			speed = speed + netforce;
			Rocket->Translate(speed / glm::vec3(10.0f, 10.0f, 10.0f));
			Vignette* glm::translate(glm::identity<glm::mat4>(), speed / glm::vec3(10.0f, 10.0f, 10.0f));
			MVP = glm::translate(MVP, -(speed / glm::vec3(10.0f, 10.0f, 10.0f)));

			score += (0.05f * ospeed);
			ospeed += 0.001f;

		}
		if(resume)
			for (Ref<ME::Mesh> mesh : Obstacles)
			{
				if (mesh->GetName() != Vignette->GetName())
				{
					if (mesh->GetVertices().at(3).vertices[0] < -600)
					{
						mesh* glm::translate(glm::identity<glm::mat4>(), glm::vec3(1600.0f, 0.0f, 0.0f));
						mesh->Translate({ 0.0f, rand() - 100.0f, 0.0f });
					}
						mesh* glm::translate(glm::identity<glm::mat4>(), glm::vec3(-ospeed, 0.0f, 0.0f));
						particletimer.Start();
				}
			}
		for (ME::VERTEX const& vertex : Rocket->GetVertices())
			if (vertex.vertices[1] < 320 || vertex.vertices[1] > 1000)
			{
				for (Ref<ME::Mesh> mesh : Obstacle_colltop)
					mesh->Reset();
				for (Ref<ME::Mesh> mesh : Obstacle_collbottom)
					mesh->Reset();
				rot = 0;
				speed.y = 0.0f;
				ospeed = 0.7f;
				score = 0;
				Rocket->Reset();
				Vignette->Reset();
				MVP = glm::ortho(0.0f, 1106.0f, 300.0f, 804.0f, -1.0f, 1.0f);
				MVP = glm::translate(MVP, { 0, -80.0f, 0.0f });

				resume = false;
				break;
			}
			else
			{
				for (Ref<ME::Mesh> mesh : Obstacle_colltop)
				{
					glm::vec<2, int> v1(mesh->GetVertices().at(0).vertices[0] + 60, mesh->GetVertices().at(0).vertices[1]);
					glm::vec<2, int> v2(mesh->GetVertices().at(1).vertices[0] - 60, mesh->GetVertices().at(1).vertices[1]);
					glm::vec<2, int> v3(mesh->GetVertices().at(2).vertices[0] - 300, mesh->GetVertices().at(2).vertices[1] + 125);
					glm::vec<2, int> pt(vertex.vertices[0], vertex.vertices[1]);

					float area = abs(v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y)) / 2.0f;
					float area1 = abs(pt.x * (v2.y - v3.y) + v2.x * (v3.y - pt.y) + v3.x * (pt.y - v2.y)) / 2.0f;
					float area2 = abs(v1.x * (pt.y - v3.y) + pt.x * (v3.y - v1.y) + v3.x * (v1.y - pt.y)) / 2.0f;
					float area3 = abs(v1.x * (v2.y - pt.y) + v2.x * (pt.y - v1.y) + pt.x * (v1.y - v2.y)) / 2.0f;

					if (area == (area1 + area2 + area3))
					{
						for (Ref<ME::Mesh> mesh : Obstacle_colltop)
							mesh->Reset();
						for (Ref<ME::Mesh> mesh : Obstacle_collbottom)
							mesh->Reset();
						rot = 0;
						speed.y = 0.0f;
						ospeed = 0.7f;
						score = 0;
						Rocket->Reset();
						Vignette->Reset();
						MVP = glm::ortho(0.0f, 1106.0f, 300.0f, 804.0f, -1.0f, 1.0f);
						MVP = glm::translate(MVP, { 0, -80.0f, 0.0f });

						resume = false;
						break;
					}
				}

				for (Ref<ME::Mesh> mesh : Obstacle_collbottom)
				{
					glm::vec<2, int> v1(mesh->GetVertices().at(0).vertices[0] + 60, mesh->GetVertices().at(0).vertices[1]);
					glm::vec<2, int> v2(mesh->GetVertices().at(1).vertices[0] - 60, mesh->GetVertices().at(1).vertices[1]);
					glm::vec<2, int> v3(mesh->GetVertices().at(2).vertices[0] - 300, mesh->GetVertices().at(2).vertices[1] - 125);
					glm::vec<2, int> pt(vertex.vertices[0], vertex.vertices[1]);

					float area = abs(v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y)) / 2.0f;
					float area1 = abs(pt.x * (v2.y - v3.y) + v2.x * (v3.y - pt.y) + v3.x * (pt.y - v2.y)) / 2.0f;
					float area2 = abs(v1.x * (pt.y - v3.y) + pt.x * (v3.y - v1.y) + v3.x * (v1.y - pt.y)) / 2.0f;
					float area3 = abs(v1.x * (v2.y - pt.y) + v2.x * (pt.y - v1.y) + pt.x * (v1.y - v2.y)) / 2.0f;

					if (area == (area1 + area2 + area3))
					{
						for (Ref<ME::Mesh> mesh : Obstacle_colltop)
							mesh->Reset();
						for (Ref<ME::Mesh> mesh : Obstacle_collbottom)
							mesh->Reset();
						rot = 0;
						speed.y = 0.0f;
						ospeed = 0.7f;
						score = 0;
						Rocket->Reset();
						Vignette->Reset();
						MVP = glm::ortho(0.0f, 1106.0f, 300.0f, 804.0f, -1.0f, 1.0f);
						MVP = glm::translate(MVP, { 0, -80.0f, 0.0f });

						resume = false;
						break;
					}
				}
			}
		if (timer.TimeElapsed().at(0) > ME::Utils::Time::milliseconds(10ll))
		{
			factor++;
			if (factor >= 360)
				factor = 1;
			glm::vec3 rgb = hsv2rgb({ factor, 0.8f, 1.0f });
			shader->SetUniforms3f("u_rgb", &rgb[0]);
			timer.Reset();
		}
		shader->SetUniformsMat4f("u_MVP", MVP);
		if (window->IsKeyPressed(Event::Key::Space))
		{
			ME::VERTEX pt1 = Rocket->GetVertices()[0], pt2 = Rocket->GetVertices()[1];
			glm::vec3 pt((pt1.vertices[0] + pt2.vertices[0]) / 2.0f, (pt1.vertices[1] + pt2.vertices[1]) / 2.0f, 1.0f);
			m_Fire->Emit(pt);
			resume = true;
		}
		if (window->IsKeyPressed(Event::Key::Escape))
			resume = false;
		if (click.TimeElapsed()[0] >= ME::Utils::Time::seconds(1))
		{
			ME::VERTEX pt1 = Rocket->GetVertices()[0], pt2 = Rocket->GetVertices()[1];
			glm::vec3 pt((pt1.vertices[0] + pt2.vertices[0]) / 2.0f, (pt1.vertices[1] + pt2.vertices[1]) / 2.0f, 1.0f);
			m_Smoke->Emit(pt);
			click.Reset();
		}

		std::string title = "The Game by GOODBOY | Score: ";
		title += std::to_string(static_cast<int>(score));
		glfwSetWindowTitle(window->GetNativeWindow(), title.c_str());
		if (glfwWindowShouldClose(window->GetNativeWindow()))
			Running = false;
		renderer->OnUpdate();
		renderer->Draw(shader);
		m_Smoke->OnUpdate();
		m_Fire->OnUpdate();
		//imgui.OnUpdate();
		window->OnUpdate();
	}
}

void Application::OnEvent(Event::Event& e)
{
	
}