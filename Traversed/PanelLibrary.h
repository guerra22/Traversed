#ifndef __PANEL_LIBRARY_H_
#define __PANEL_LIBRARY_H_

#include "UiPanel.h"

//#include "LibraryManager.h"

struct FileSystemProperties;
struct SceneProperties;
struct ResourceProperties;
class LibraryFolder;

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

private:
	float leftWin;
	float rightWin;

	FileSystemProperties* fsIntance = nullptr;
	ResourceProperties* resInstance = nullptr;
	SceneProperties* sInstance = nullptr;
	LibraryFolder* currentFolder = nullptr;
};


#endif