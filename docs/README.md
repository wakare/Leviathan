# OverView: 
	Leviathan is a simple renderer for rendering simple scene.
	
# Feature: 
	1. light-weight 
	2. easy to extend 
	
# Version plan 
## v0.1: 
	1. implement Render manager module (GLRenderMgr)
		1. RenderTree generation
		2. common render pipeline abstraction
 
	2. implement Scene manager module (basic 3D scene)
		1. scene camera manipulator
		2. scene logic object representation
		3. scene logic Tree generation
	
	3. implement Resource manager module
		1. file load

	4. render simple scene (using phong-light model) 
	 
## v0.2: 
	1. provide interface to modify shader effect
	2. provide interface to add custom shader effect

### 7.7 Updated:
	Now user must add default shader program to a "render-base" root node, all of children of the node will be added into the pass util traverse a node owned their shader program.
