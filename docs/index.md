# Traversed

Traversed Engine is a 3D Engine for Game Development, this engine is used to learn game development in the third year of citm-upc.

<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/Engine1.png"> 
</p>

# Features
- Shader Pipeline implemented.
- All the fbx object will be rendered with shaders.
- The user is able to use the inspector to modify a GameObject:
- Hierarchy:create empty and create children
- Transform: translate, rotate and scale Game Objects.
- Texture: select or drop any imported texture
- Camera is a component with settings that can be modified.
- GameObjects can be picked from the world using the mouse.
- All meshes use a bounding volume (AABB) and can be discarded using Frustum Culling. This process is visualized in the editor (debug raycast and boxes).
- Models, meshes and textures are saved to custom format under “Library” folder
- Scene can be serialized to a file that can be loaded.
- The editor has 2 windows one with the scene(editor view) and another captured from a gameobject with a camera component(main game camera), each one has its own framebuffer and the user can visualize both at the same time.
- Resource Management
- In the library panel, all the library files can be drag&drop to the scene and Inspector, it is also allowed to create new material and shader, and they can be edit in the Inspector.
- Double click the shader file, you are able to edit the shader text and code a new shader by yourself.
- In the top of editor there are "Play" and "Pause" botton which can be used to stwith the editor mode to game mode.

# Attention
- Watch the instructions in the last release or in our github page before running the engine.
- Delete the "Library" folder when you are the first time to run the engine(If there's a Library folder inside the Engine folder).
- You can only quit engine when all the popped up windows are closed.
- The scene view is not focus any object at the start because the initial postion of the editor camera is in the origin point(there's nothing in the view of camera), you should move the camera with camera controls.(Review the instructions below)
- If the game view dosen't display nothing, that because it dosen't have a Camera object, in order to do that please read the instruction of game panel below.

# Instruction of the water demo scene.

- Drag an fbx object and drop into the scene
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/dragfbx.png"> 
</p>

- Select the object in hierarchy, then right click on the Library panel and create a new Material.
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/createMaterial.png"> 
</p>

- Name the new material.
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/newmaterial.png"> 
</p>

- Drag the material into the material component in inspector to assign the material.
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/assignMaterial.png"> 
</p>

- Choose the water shader which is already inside the assets.
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/chooseShader.png"> 
</p>

- Choose the color in the color picker and set the value of the variables.
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/SetColor.png"> 
</p>

- drag the water textures into the inspector.
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/setvalue.png"> 
</p>

- Set the value of velocity then you will get a moving water.
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/Moving%20water.gif"> 
</p>

## Example video for the demo scene(Town and moving water).
<iframe width="560" height="315" src="https://www.youtube.com/embed/idL9ePR36PQ" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

# Shader Pipeline
When importing a model to the library, the default shader will be automatically applied to its material. Every ".shader" file created inside the editor starts with a basic template containing the most basic configuration. The template is the same default shader used by the engine every time a new FBX is imported to the library (in case it contains a material).

## Shader file creation
- Right click inside the Library window.
- Create->Shader
- Type the name and click create.

## Shader editing and usage
- Double-click a shader to open the GLSL editor.
- Edit the shader.
- Save the shader.
- Inside the "Material" component, select the desired shader.
- Edit the uniform values. 

## Material file creation and usage
- Right click inside the library window.
- Create->Material
- Type the name and click create.
- Select a scene Game Object.
- select Add Component->Material in the inspector window.
- Drag the created material into the 'EMPTY' box.
- select a Shader.
- set the uniform value.
- Click 'SAVE' to save the material.

# Editor Windows

## Scene panel 
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/Engine%20image.png"> 
</p>
Camera Controls:
- While Right clicking, free look around is enabled.
- While Right clicking, “WASD” fps-like movement.()
- holding the "shift" key to duplicate the movement speed.
- Mouse wheel zoom in and out.
- Pressing “f” focus the camera around the selected object.
- Holding SHIFT duplicates movement speed.
- "Alt Left/right" can orbit camera around the selected object.
Mouse picking:
- An object can be selected if you move the cursor on an object and left click the mouse.(The axis of the object displayed)
- When one object is selected in secen panel, click and drag the axis can chage the transform("Q"->Position, "E"->Rotation, "R"->Scale)

## Game panel
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/Game.png"> 
</p>
- The game view only displays when there is a Camera object.
- In order to do it, u should right click the mouse in the Hierarchy panel and create a camera node.
- The initial position of a new camera object is (0,0,0)
- You can change the transform of the camera in Inspector to move game view.
- The other method is select an object then add a camera component.
- Click "play" and "pause" botton switch the editor mode to game mode.(In the example scene, you can click pause to stop the water's movement)

## General menu
File: 
- New Scene: Create a new scene(clear current scene)
- Save Scene: Save current scene to Library folder.
- Load Scene: Pop up the file browser window, u can find and choose the target scene file to load.
- Exit: quit the engine.

View:
- Enable and disable the panels.

Help:
- Visit github page
- About information

## Configuration panel
- A graph for the frames per second.
- Configuration for all variables on each module (window, renderer, input).
- Information of Game and Resources. 
- Information output of memory consumption, hardware detection and software

## About panel
- engine introduction 
- versions (SDL, OpenGL, DevIL......).
- License 

## Hierarchy panel:
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/Hierarchy.png"> 
</p>
- It displays a list with all GameObjects in this window. The user is able to select a GameObject through this window.
- Right click the mouse->Creat a new node.(Empty, spetail, mesh, camera)

## Inspector panel
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/Inspector.png"> 
</p>
- It display information about the components of the selected GameObject
- It's allowed to add a new component or delet the component. 
- Transform: change the value of position, rotation and scale for the selected GameObject.
- Mesh: information about the loaded mesh.
- Texture: information about the loaded texture.(support drag&drop from Library panel)
- Camera: information about the loaded camera.
- Material: it displays the detail of the material and the shader which is applyed to this material.
- Material and the values of a shader can be edited here.
- It supports drag&drop from library.

## Console panel
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/console.png"> 
</p>
- display the logs messages.
- Clear->Clear the list of logs.
- Log types->filter the different log types.
- Options->extra options.
- Collapse->Collapses all the logs that are exactly the same.
- Time->Shows the time when the log has been registered.

## Library panel
<p align="center">
  <img src="https://github.com/guerra22/Traversed/raw/main/Wiki/Library.png"> 
</p>
- Display the game library files for the engine.
- All files are displayed in box view.
- You can click the folder file to see the content files.
- It accepts drag&drop of FBX files from the Library panel folder to the scene panel.
- It accepts drag&drop of DDS/PNG files from the Library panel folder(apply the texture to the selected GameObject)(firstly select a gameobject, then drop the file into Material component in inspector).

## Shader Text Editor
- A GLSL editor powered by ImGuiColorTextEdit that allows Vertex and Fragment shader programing on the same file, improving reliabilty inside the engine and easing the coding.
- Display the script of a shader.
- It supports copy, paste, cut, and save.
- It is used to create and edit a new shader, all the variables can be changed in the inspector.

# Developers
- [Hang Xue](https://github.com/Patronum129)
- [Oriol Via](https://github.com/guerra22)

# For more details
- [Last Release](https://github.com/guerra22/Traversed/releases/tag/Assignment3.1)
- [GitHub repository](https://github.com/guerra22/Traversed)
- [Github page](https://guerra22.github.io/Traversed/)

# Libraries
- [SDL](https://github.com/libsdl-org/SDL)
- [Glew](https://github.com/nigels-com/glew)
- [ImGUI](https://github.com/ocornut/imgui)
- [JSON](https://github.com/nlohmann/json)
- [MathGeoLib](https://github.com/juj/MathGeoLib)
- [Assimp](https://github.com/assimp/assimp)
- [DevIL](https://github.com/DentonW/DevIL)
- [ImGuiFileDialog](https://github.com/aiekick/ImGuiFileDialog)
- [ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit)

# License 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
