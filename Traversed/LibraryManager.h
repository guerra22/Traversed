#pragma once
#include "Globals.h"

#include <string>

#define LIB_ROOT "Library";
#define LIB_MESHES "Library/Meshes";
#define LIB_MODELS "Library/Models";
#define LIB_MATERIALS "Library/Materials";
#define LIB_TEXTURES "Library/Textures";
#define LIB_SCENES "Library/Scenes";


class LibraryFolder;

namespace LibraryManager
{
	void Init(LibraryFolder& root);
	void CleanUp();

	void GenerateLibrary();

	bool Exists(std::string file);
	bool IsDirectory(std::string dir);
	bool CreateDir(std::string dir);
	bool RemoveFile(std::string filePath);
	std::string GetFilename(std::string file, bool extension = false);

	bool AddPath(std::string path);
	std::string NormalizePath(std::string path);
	std::string UnNormalizePath(std::string path);

	unsigned int Load(std::string filePath, char** buffer);

	unsigned int Save(std::string filePath, char* data, uint size = 0, bool append = false);
	unsigned int Copy(std::string filePath, std::string dir);

	void SaveJSON(std::string filePath, std::string jsonDump);
	std::string LoadJSON(std::string filePath);

	void FolderSystemUpdate(LibraryFolder* folder, bool recursive = false);
};