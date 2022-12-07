#include "PanelAbout.h"

#include "Globals.h"

#include "External/SDL/include/SDL.h"
#include "MathGeoLib.h"
#include "External/Glew/include/glew.h"
#include "External/Assimp/include/assimp/version.h"
#include "External/Nlohmann/json.hpp"
#include "External/PhysFS/include/physfs.h"
#include "External/PugiXml/src/pugixml.hpp"
#include <gl/GL.h>
#include <gl/GLU.h>

PanelAbout::PanelAbout(bool enabled) : UiPanel(enabled)
{
	name = "About";

	vEngine = "v.";
	vEngine += std::to_string(ENGINE_VERSION_MAJOR);
	vEngine += ".";
	vEngine += std::to_string(ENGINE_VERSION_MINOR);

	//Versions
	SDL_version version;
	SDL_GetVersion(&version);

	PHYSFS_Version versionPhys;
	PHYSFS_getLinkedVersion(&versionPhys);

	vSdl = "SDL " + std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(version.patch);
	vImGui = "DearImGui " + std::string(ImGui::GetVersion());
	vMathGeoLib = "MathGeoLib 1.5";
	vGlew = "Glew ";
	vGlew += (const char*)glewGetString(GLEW_VERSION);
	vOpenGl = "OpenGl ";
	vOpenGl += (const char*)glGetString(GL_VERSION);
	vNlohmann = "Nlohmann ";
	vNlohmann += "NOT YET";
	vAssimp = "Assimp " + std::to_string(aiGetVersionMajor()) + "." + std::to_string(aiGetVersionMinor()) + "." + std::to_string(aiGetVersionRevision());
	vPhysfs = "PhysFS " + std::to_string(versionPhys.major) + "." + std::to_string(versionPhys.minor) + "." + std::to_string(versionPhys.patch);

	vPugiXml = "PugiXML ";
	std::string auxV = std::to_string(PUGIXML_VERSION);
	for (int i = 0; i < auxV.size(); ++i)
	{
		vPugiXml += auxV[i];

		if (i != auxV.size() - 1)
			vPugiXml += ".";
	}
}

PanelAbout::~PanelAbout()
{

}

void PanelAbout::Update()
{
	if (ImGui::Begin("About"))
	{
		ImGui::Text("Traversed Engine \n");
		ImGui::SameLine();
		ImGui::Text(vEngine.c_str());
		ImGui::Spacing();
		ImGui::Text("A simple 3D engine.");
		ImGui::Spacing();
		ImGui::TextURL("Made by HangXue & Oriol Via", "https://github.com/guerra22/Traversed");

		ImGui::NewLine();
		ThirdPartyLibs();

		ImGui::NewLine();
		MyLicense();
	}

	ImGui::End();
}

#pragma region Text
void PanelAbout::ThirdPartyLibs()
{
	ImGui::Text("3rd Party Libraries used: ");
	ImGui::BulletText("");
	ImGui::TextURL(vSdl.c_str(), "https://libsdl.org/index.php", 1, 0);

	ImGui::BulletText("");
	ImGui::TextURL(vImGui.c_str(), "https://github.com/ocornut/imgui", 1, 0);

	ImGui::BulletText("");
	ImGui::TextURL(vGlew.c_str(), "http://glew.sourceforge.net", 1, 0);

	ImGui::BulletText("");
	ImGui::TextURL(vOpenGl.c_str(), "https://www.opengl.org", 1, 0);

	ImGui::BulletText("");
	ImGui::TextURL(vMathGeoLib.c_str(), "https://github.com/juj/MathGeoLib", 1, 0);

	ImGui::BulletText("");
	ImGui::TextURL(vNlohmann.c_str(), "https://github.com/nlohmann/json", 1, 0);

	ImGui::BulletText("");
	ImGui::TextURL(vAssimp.c_str(), "https://github.com/assimp/assimp", 1, 0);

	ImGui::BulletText("");
	ImGui::TextURL(vPhysfs.c_str(), "https://github.com/icculus/physfs", 1, 0);

	ImGui::BulletText("");
	ImGui::TextURL(vPugiXml.c_str(), "https://pugixml.org", 1, 0);
}

void PanelAbout::MyLicense()
{
	ImGui::Text("License: ");
	ImGui::NewLine();
	ImGui::TextWrapped("MIT License");
	ImGui::NewLine();
	ImGui::TextWrapped("Copyright (c) 2022 CITM");
	ImGui::NewLine();
	ImGui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the \Software\), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions : ");
	ImGui::NewLine();
	ImGui::TextWrapped("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.");
	ImGui::NewLine();
	ImGui::TextWrapped("THE SOFTWARE IS PROVIDED \AS IS\, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
}
#pragma endregion About Text