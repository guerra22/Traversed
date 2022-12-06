#include "MeshRenderer.h"
#include "MeshImporter.h"
#include "TextureImporter.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"

#include "Shader.h"

MeshRenderer::MeshRenderer()
{
	
}

MeshRenderer::MeshRenderer(Meshe meshData)
{
	this->mesh = meshData;

	//init
	VAO = 0;
	VBO = 0;
	EBO = 0;

	//Generation of buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//Vertex
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);

	//VERTEX POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//VERTEX NORMALS
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//VERTEX TEXTURE COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//Index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], GL_STATIC_DRAW);

	//Cleaning
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	CreateNormals();
}


MeshRenderer::~MeshRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	VAO = 0;
	VBO = 0;
	EBO = 0;

	CleanNormals();
}

void MeshRenderer::Draw(Shader* shader, Texture text, float4x4 model)
{
	if (this->shader == nullptr) this->shader = shader;

	if (EBO != 0)
	{
		this->shader->Use();

		if (RenderProperties::Instance()->texture2D)
		{
			glActiveTexture(GL_TEXTURE0);

			glBindTexture(GL_TEXTURE_2D, text.id);

			shader->SetInt("texture_albedo", 0);
		}

		this->shader->SetMat4("projection", CameraProperties::Instance()->editorCamera.GetProjectionMatrix());
		this->shader->SetMat4("view", CameraProperties::Instance()->editorCamera.GetViewMatrix());
		this->shader->SetMat4("model", &model.v[0][0]);

		//Light
		if (RenderProperties::Instance()->lighting)
		{
			RenderProperties::Instance()->worldLight->SetShaderData(this->shader);
		}

		//Draw Mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}
}

void MeshRenderer::DrawNormals(Shader* shader, float4x4 model, bool faceNormals)
{
	if (this->debugShader == nullptr) this->debugShader = shader;
	debugShader->Use();
	debugShader->SetMat4("projection", CameraProperties::Instance()->editorCamera.GetProjectionMatrix());
	debugShader->SetMat4("view", CameraProperties::Instance()->editorCamera.GetViewMatrix());
	debugShader->SetMat4("model", &model.v[0][0]);
	if (!faceNormals)
	{
		glBindVertexArray(VNVAO);
		glDrawArrays(GL_LINES, 0, vNormals.size());
	}
	else
	{
		glBindVertexArray(FNVAO);
		glDrawArrays(GL_LINES, 0, fNormals.size());
	}
	glBindVertexArray(0);
}

void MeshRenderer::CreateNormals(float magnitude)
{
	//VERETX NORMALS
	vNormals.reserve(mesh.vertices.size() * 2);
	VNVAO = 0;
	VNVBO = 0;
	for (int i = 0; i < mesh.vertices.size(); ++i)
	{
		vNormals.emplace_back(mesh.vertices[i].position);
		vNormals.emplace_back(mesh.vertices[i].position + mesh.vertices[i].normal * magnitude);
	}
	//Buffer generation
	glGenVertexArrays(1, &VNVAO);
	glGenBuffers(1, &VNVBO);
	glBindVertexArray(VNVAO);

	//Vertex
	glBindBuffer(GL_ARRAY_BUFFER, VNVBO);
	glBufferData(GL_ARRAY_BUFFER, vNormals.size() * sizeof(float3), &vNormals[0], GL_STATIC_DRAW);

	//Vertex Postition
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (void*)0);

	glBindVertexArray(0);

	///FACE NORMALS
	fNormals.reserve((mesh.indices.size() / 3) * 2);

	FNVAO = 0;
	FNVBO = 0;

	for (int i = 0; i < mesh.indices.size(); i += 3)
	{
		int aux[3] =
		{
			mesh.indices[i],
			mesh.indices[i + 1],
			mesh.indices[i + 2]
		};

		float3 face = (mesh.vertices[aux[0]].position + mesh.vertices[aux[1]].position + mesh.vertices[aux[2]].position) / 3;
		float3 dir = (mesh.vertices[aux[0]].normal + mesh.vertices[aux[1]].normal + mesh.vertices[aux[2]].normal) / 3;
		dir.Normalize();

		fNormals.emplace_back(face);
		fNormals.emplace_back(face + dir * magnitude);
	}

	//Buffer generation
	glGenVertexArrays(1, &FNVAO);
	glGenBuffers(1, &FNVBO);

	glBindVertexArray(FNVAO);

	//Vertex
	glBindBuffer(GL_ARRAY_BUFFER, FNVBO);
	glBufferData(GL_ARRAY_BUFFER, fNormals.size() * sizeof(float3), &fNormals[0], GL_STATIC_DRAW);

	//Vertex Postition
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float3), (void*)0);

	glBindVertexArray(0);
}

void MeshRenderer::CleanNormals()
{
	vNormals.clear();

	glDeleteVertexArrays(1, &VNVAO);
	glDeleteBuffers(1, &VNVBO);

	VNVAO = 0;
	VNVBO = 0;

	fNormals.clear();

	glDeleteVertexArrays(1, &FNVAO);
	glDeleteBuffers(1, &FNVBO);

	FNVAO = 0;
	FNVBO = 0;
}

#pragma region Getters and Setters
void MeshRenderer::SetShader(Shader* shader)
{
	this->shader = shader;
}

void MeshRenderer::SetDebugShader(Shader* shader)
{
	this->debugShader = shader;
}
#pragma endregion Getters and Setters