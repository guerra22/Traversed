#ifndef __PANEL_LIBRARY_H_
#define __PANEL_LIBRARY_H_

#include "UiPanel.h"

//#include "LibraryManager.h"

struct FileSystemProperties;
struct SceneProperties;
struct ResourceProperties;
struct LibraryItem;
class LibraryFolder;

struct NewFileData
{
	NewFileData() {};
	NewFileData(std::string placeHolderName, std::string extension, std::string buffer)
	{
		this->placeHolderName = placeHolderName;
		this->extension = extension;
		this->buffer = buffer;
		openPopUp = true;
	}

	std::string placeHolderName;
	std::string extension;
	std::string buffer;
	bool openPopUp = false;
};

class PanelLibrary : public UiPanel
{
public:
	PanelLibrary(bool enabled = false);
	~PanelLibrary();

	void Start();

	void Update();

private:
	void Hierarchy();
	void BoxView();

	void ExecuteItemActive(LibraryItem* item, float cellSize);

	int RightClickMenuContextItem(LibraryItem* item);
	int RightClickMenuContextWindow();
	int RightClickMenuContent(LibraryItem* item = nullptr);

	void PopUpFileName();

private:
	float leftWin;
	float rightWin;

	FileSystemProperties* fsIntance = nullptr;
	ResourceProperties* resInstance = nullptr;
	SceneProperties* sInstance = nullptr;
	LibraryFolder* currentFolder = nullptr;

	std::string* package = nullptr;
	NewFileData newFileData;
};

#endif