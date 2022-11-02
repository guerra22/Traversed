#include "ModuleFileSystem.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleUI.h"

#include "AssimpDefs.h"
#include "Resource.h"
#include "External/SDL/include/SDL_filesystem.h"
#include "External/Assimp/include/assimp/cimport.h"
#include "External/DevIL/include/il.h"

#pragma comment (lib, "External/Assimp/lib/assimp-vc142-mt.lib")

ModuleFileSystem::ModuleFileSystem(Application* app, const char* assetsPath)
{
	this->App = app;

	name = "Filesystem";
	char* basePath = SDL_GetBasePath();
	PHYSFS_init(basePath);
	SDL_free(basePath);

	// workaround VS string directory mess
	AddPath(".");

	if (0 && assetsPath != nullptr)
		AddPath(assetsPath);

	// Dump list of paths
	LOGGING("FileSystem Operations base is [%s] plus:", GetBasePath());
	LOGGING(GetReadPaths());

	// enable us to write in the game's dir area
	if (PHYSFS_setWriteDir(".") == 0)
		LOGGING("File System error while creating write dir: %s\n", PHYSFS_getLastError());

	// Make sure standard paths exist
	//Put all the different folder paths here
	const char* dirs[] = {
		SETTINGS_FOLDER
	};

	for (uint i = 0; i < sizeof(dirs) / sizeof(const char*); ++i)
	{
		if (PHYSFS_exists(dirs[i]) == 0)
			PHYSFS_mkdir(dirs[i]);
	}

	texExtension = { ".png", ".jpg", ".dds", ".tga" };
	modelExtension = { ".obj", ".fbx", ".3DS", ".FBX" };
}

ModuleFileSystem::~ModuleFileSystem()
{
	aiDetachAllLogStreams();
	PHYSFS_deinit();
}

bool ModuleFileSystem::Init(JsonParser& node)
{
	LOGGING("Loading File System");
	bool ret = true;
	
	// Ask SDL for a write dir
	char* writePath = SDL_GetPrefPath(App->GetOrganizationName(), App->GetAppName());

	SDL_free(writePath);

	return ret;
}

bool ModuleFileSystem::CleanUp()
{
	return true;
}

std::string ModuleFileSystem::ChangePath(const char* path) const
{
	std::string normalized_path(path);

	for (uint i = 0; i < normalized_path.size(); ++i)
	{
		if (normalized_path[i] == '\\')
		{
			normalized_path[i] = '/';
		}
	}

	return normalized_path;
}

bool ModuleFileSystem::AddPath(const char* path)
{
	bool ret = false;

	if (PHYSFS_mount(path, nullptr, 1) == 0)
	{
		LOGGING("File System error while adding a path or zip: %s\n", PHYSFS_getLastError());
	}

	else
	{
		ret = true;
	}

	return ret;
}

uint ModuleFileSystem::Load(const char* file, char** buffer)
{
	uint ret = 0;

	PHYSFS_file* fsFile = PHYSFS_openRead(file);

	if (fsFile != nullptr)
	{
		PHYSFS_sint32 size = (PHYSFS_sint32)PHYSFS_fileLength(fsFile);

		if (size > 0)
		{
			*buffer = new char[size];
			uint readed = (uint)PHYSFS_read(fsFile, *buffer, 1, size);
			if (readed != size)
			{
				LOGGING("File System error while reading from file %s: %s\n", file, PHYSFS_getLastError());
				RELEASE_ARRAY(buffer);
			}
			else
				ret = readed;
		}

		if (PHYSFS_close(fsFile) == 0)
			LOGGING("File System error while closing file %s: %s\n", file, PHYSFS_getLastError());
	}
	else
		LOGGING("File System error while opening file %s: %s\n", file, PHYSFS_getLastError());

	return ret;
}

uint ModuleFileSystem::Save(const char* file, const void* buffer, unsigned int size, bool append)
{
	unsigned int ret = 0;

	bool overWrite = PHYSFS_exists(file) != 0;
	PHYSFS_file* fsFile = (append) ? PHYSFS_openAppend(file) : PHYSFS_openWrite(file);

	if (fsFile != nullptr)
	{
		uint written = (uint)PHYSFS_write(fsFile, (const void*)buffer, 1, size);
		if (written != size)
		{
			LOGGING("File System error while writing to file %s: %s", file, PHYSFS_getLastError());
		}

		else
		{
			if (append == true)
			{
				LOGGING("Added %u data to [%s%s]", size, PHYSFS_getWriteDir(), file);
			}

			else if (overWrite == false)
			{
				LOGGING("New file created [%s%s] of %u bytes", PHYSFS_getWriteDir(), file, size);
			}

			ret = written;
		}

		if (PHYSFS_close(fsFile) == 0)
		{
			LOGGING("File System error while closing file %s: %s", file, PHYSFS_getLastError());
		}

	}
	else
	{
		LOGGING("File System error while opening file %s: %s", file, PHYSFS_getLastError());
	}

	return ret;
}

const char* ModuleFileSystem::GetReadPaths() const
{
	static char paths[512];

	paths[0] = '\0';

	char** path;
	for (path = PHYSFS_getSearchPath(); *path != nullptr; ++path)
	{
		strcat_s(paths, 512, *path);
		strcat_s(paths, 512, "\n");
	}

	return paths;
}

std::string ModuleFileSystem::GetFileExtension(const char* path)
{
	std::string full_path = path;
	std::string extension = "";

	size_t dot_position = full_path.find_last_of(".");

	extension = full_path.substr(dot_position + 1);

	return extension;
}