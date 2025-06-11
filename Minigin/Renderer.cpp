#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "imgui_plot.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	/*
	constexpr size_t buf_size = 512;
	static float x_data[buf_size];
	static float y_data1[buf_size];
	static float y_data2[buf_size];
	static float y_data3[buf_size];

	constexpr float sampling_freq = 44100;
	constexpr float freq = 500;
	for (size_t i = 0; i < buf_size; ++i) {
		const float t = i / sampling_freq;
		x_data[i] = t;
		const float arg = 2.f * static_cast<float>(M_PI) * freq * t;
		y_data1[i] = static_cast<float>(sin(arg));
		y_data2[i] = static_cast<float>(y_data1[i] * -0.6 + sin(2 * arg) * 0.4);
		y_data3[i] = static_cast<float>(y_data2[i] * -0.6 + sin(3 * arg) * 0.4);
	}

	static const float* y_data[] = { y_data1, y_data2, y_data3 };
	static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::Begin("Example plot", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = x_data;
	conf.values.count = buf_size;
	conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
	conf.values.ys_count = 3;
	conf.values.colors = colors;
	conf.scale.min = -1;
	conf.scale.max = 1;
	conf.tooltip.show = true;
	conf.grid_x.show = true;
	conf.grid_x.size = 128;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = 0.5f;
	conf.grid_y.subticks = 5;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(buf_size, 200);
	ImGui::Plot("plot1", conf);

	// Draw second plot with the selection
	// reset previous values
	conf.values.ys_list = nullptr;
	conf.selection.show = false;
	// set new ones
	conf.values.ys = y_data3;
	conf.values.offset = selection_start;
	conf.values.count = selection_length;
	conf.line_thickness = 2.f;
	ImGui::Plot("plot2", conf);

	ImGui::End();
	*/
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const float srcx, const float srcy, const float srcwidth, const float srcheight) const
{
	if (srcwidth == -1 or srcheight == -1)
	{
		RenderTexture(texture, x, y, width, height);
		return;
	}
	SDL_Rect src{};
	src.x = static_cast<int>(srcx);
	src.y = static_cast<int>(srcy);
	src.w = static_cast<int>(srcwidth);
	src.h = static_cast<int>(srcheight);
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float srcx, const float srcy, const float srcwidth, const float srcheight) const
{
	if (srcwidth == -1 or srcheight == -1)
	{
		RenderTexture(texture, x, y);
		return;
	}
	SDL_Rect src{};
	src.x = static_cast<int>(srcx);
	src.y = static_cast<int>(srcy);
	src.w = static_cast<int>(srcwidth);
	src.h = static_cast<int>(srcheight);
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
