#ifndef TERRAMAN_GIZMO_PLUGIN_H
#define TERRAMAN_GIZMO_PLUGIN_H

/*************************************************************************/
/*  terrain_world_gizmo_plugin.h                                         */
/*************************************************************************/
/*                         This file is part of:                         */
/*                          PANDEMONIUM ENGINE                           */
/*             https://github.com/Relintai/pandemonium_engine            */
/*************************************************************************/
/* Copyright (c) 2022-present Péter Magyar.                              */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "editor/spatial_editor_gizmos.h"

class TerrainWorldEditorPlugin;

class TerrainWorldGizmoPlugin : public EditorSpatialGizmoPlugin {
	GDCLASS(TerrainWorldGizmoPlugin, EditorSpatialGizmoPlugin);

public:
	String get_gizmo_name() const;
	int get_priority() const;
	bool is_handle_highlighted(const EditorSpatialGizmo *p_gizmo, int p_idx, bool p_secondary) const;

	TerrainWorldGizmoPlugin();
	~TerrainWorldGizmoPlugin();

	TerrainWorldEditorPlugin *plugin;

protected:
	Ref<EditorSpatialGizmo> create_gizmo(Spatial *p_spatial);
	static void _bind_methods();
};

#endif
