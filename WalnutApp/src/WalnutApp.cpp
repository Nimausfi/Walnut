#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/Image.h"

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnAttach() override
	{
		m_Image = std::make_shared<Walnut::Image>("eagle.png");
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Dashboard");
		ImGui::SetWindowSize(ImVec2(750.0f, 750.0f));

		// Text
		ImGui::BulletText("Select Your Option: ");

		// Colored Text
		ImGuiStyle* style = &ImGui::GetStyle();
		style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
		char text1[] = "Click to Continue";
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255)); //
		ImGui::InputText(" ", text1, sizeof(text1));
		ImGui::PopStyleColor();

		// Adjust Mouse Sensitivity
		static float v = 0.0f;
		ImGui::SliderFloat("Adjust Mouse Sensitivity", &v, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f

		// Change Color of Normal Windows
		ImGui::ColorEdit3("Change Windows Color", (float*)&style->Colors[ImGuiCol_WindowBg]); // Edit 3 floats representing a color

		// Counter
		static int counter = 0;
		if (ImGui::Button("Counter"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		// Image
		ImGui::Image(m_Image->GetDescriptorSet(), { (float)m_Image->GetWidth(), (float)m_Image->GetHeight() });

		ImGui::End();

		ImGui::ShowDemoWindow();
	}
private:
	std::shared_ptr<Walnut::Image> m_Image;
};


class ExampleLayer2 : public Walnut::Layer {

public:
	virtual void OnAttach2() override
	{
		m_Image2 = std::make_shared<Walnut::Image>("clock.png");
	}

	virtual void OnUIRender2()
	{

		ImGui::Begin("Date & Time", nullptr, ImGuiWindowFlags_NoCollapse);
		ImGui::SetWindowSize(ImVec2(180.0f, 220.0f));
		//ImGui::GetWindowSize(2.0f, 1.0f);

		// Date & Time
		if (ImGui::BeginMenu("Navigate here")) {
			d_t->date_time();
			ImGui::EndMenu();
		}

		// Image
		ImGui::Image(m_Image2->GetDescriptorSet(), { (float)m_Image2->GetWidth(), (float)m_Image2->GetHeight() });

		ImGui::End();

		ImGui::ShowDemoWindow();
	}

private:
	std::unique_ptr<Walnut::Application> d_t;
	std::shared_ptr<Walnut::Image> m_Image2;
};


Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->PushLayer2<ExampleLayer2>();

	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}