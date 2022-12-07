#ifndef __MODULERESOURCE_H__
#define __MODULERESOURCE_H__

#include "Module.h"

#include "Resource.h"

#include <map>


class LibraryFodler;
struct FileSystemProperties;

struct ResourceProperties
{
	ResourceProperties();

	static ResourceProperties* Instance();

	static void Delete();

private:
	static ResourceProperties* instance;

public:
	std::map<std::string, Resource*> resources;

	bool requestFolderFileCheck = false;

};

class ModuleResources : public Module
{
public:
	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();

	bool Init() override;
	bool Start() override;

	bool CleanUp() override;

	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	std::string Find(std::string assetsFile);
	std::string ImportFile(std::string assetsFile);

	Resource* RequestResource(std::string uuid);
	void ReleaseResource(std::string uuid);

	void FolderFileCheck(LibraryFolder* folder);

private:
	RESOURCE_TYPE GetResourceType(std::string extension);

private:
	Resource* CreateNewResource(std::string assetsPath, RESOURCE_TYPE type);

private:
	ResourceProperties* resProps = nullptr;
	FileSystemProperties* fsProps = nullptr;
};

#endif // !__MODULERESOURCE_H__