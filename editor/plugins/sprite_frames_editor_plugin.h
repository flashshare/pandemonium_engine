#ifndef SPRITE_FRAMES_EDITOR_PLUGIN_H
#define SPRITE_FRAMES_EDITOR_PLUGIN_H

/*************************************************************************/
/*  sprite_frames_editor_plugin.h                                        */
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

#include "editor/editor_plugin.h"
#include "scene/gui/split_container.h"

#include "core/containers/pool_vector.h"
#include "core/containers/rb_set.h"
#include "core/math/vector2.h"
#include "core/object/object.h"
#include "core/object/reference.h"
#include "core/string/string_name.h"
#include "core/string/ustring.h"
#include "core/variant/variant.h"

class AcceptDialog;
class Button;
class CheckButton;
class ConfirmationDialog;
class Control;
class EditorFileDialog;
class EditorNode;
class InputEvent;
class ItemList;
class ScrollContainer;
class SpinBox;
class SpriteFrames;
class TextureRect;
class ToolButton;
class Tree;
class UndoRedo;
class LineEdit;

class SpriteFramesEditor : public HSplitContainer {
	GDCLASS(SpriteFramesEditor, HSplitContainer);

	enum {
		PARAM_USE_CURRENT, // Used in callbacks to indicate `dominant_param` should be not updated.
		PARAM_FRAME_COUNT, // Keep "Horizontal" & "Vertical" values.
		PARAM_SIZE, // Keep "Size" values.
	};
	int dominant_param = PARAM_FRAME_COUNT;

	ToolButton *load;
	ToolButton *load_sheet;
	ToolButton *_delete;
	ToolButton *copy;
	ToolButton *paste;
	ToolButton *empty;
	ToolButton *empty2;
	ToolButton *move_up;
	ToolButton *move_down;
	ToolButton *zoom_out;
	ToolButton *zoom_reset;
	ToolButton *zoom_in;
	ItemList *tree;
	bool loading_scene;
	int sel;

	ToolButton *new_anim;
	ToolButton *remove_anim;
	LineEdit *anim_search_box;

	Tree *animations;
	SpinBox *anim_speed;
	CheckButton *anim_loop;

	EditorFileDialog *file;

	AcceptDialog *dialog;

	SpriteFrames *frames;

	StringName edited_anim;

	ConfirmationDialog *delete_dialog;

	ConfirmationDialog *split_sheet_dialog;
	ScrollContainer *split_sheet_scroll;
	TextureRect *split_sheet_preview;
	SpinBox *split_sheet_h;
	SpinBox *split_sheet_v;
	SpinBox *split_sheet_size_x;
	SpinBox *split_sheet_size_y;
	SpinBox *split_sheet_sep_x;
	SpinBox *split_sheet_sep_y;
	SpinBox *split_sheet_offset_x;
	SpinBox *split_sheet_offset_y;
	ToolButton *split_sheet_zoom_out;
	ToolButton *split_sheet_zoom_reset;
	ToolButton *split_sheet_zoom_in;
	EditorFileDialog *file_split_sheet;
	RBSet<int> frames_selected;
	RBSet<int> frames_toggled_by_mouse_hover;
	int last_frame_selected;

	float scale_ratio;
	int thumbnail_default_size;
	float thumbnail_zoom;
	float max_thumbnail_zoom;
	float min_thumbnail_zoom;
	float sheet_zoom;
	float max_sheet_zoom;
	float min_sheet_zoom;

	Size2i _get_frame_count() const;
	Size2i _get_frame_size() const;
	Size2i _get_offset() const;
	Size2i _get_separation() const;

	void _load_pressed();
	void _file_load_request(const PoolVector<String> &p_path, int p_at_pos = -1);
	void _copy_pressed();
	void _paste_pressed();
	void _empty_pressed();
	void _empty2_pressed();
	void _delete_pressed();
	void _up_pressed();
	void _down_pressed();
	void _update_library(bool p_skip_selector = false);

	void _animation_select();
	void _animation_name_edited();
	void _animation_add();
	void _animation_remove();
	void _animation_remove_confirmed();
	void _animation_search_text_changed(const String &p_text);
	void _animation_loop_changed();
	void _animation_fps_changed(double p_value);

	void _tree_input(const Ref<InputEvent> &p_event);
	void _zoom_in();
	void _zoom_out();
	void _zoom_reset();

	bool updating;
	bool updating_split_settings; // Skip SpinBox/Range callback when setting value by code.

	UndoRedo *undo_redo;

	Variant get_drag_data_fw(const Point2 &p_point, Control *p_from);
	bool can_drop_data_fw(const Point2 &p_point, const Variant &p_data, Control *p_from) const;
	void drop_data_fw(const Point2 &p_point, const Variant &p_data, Control *p_from);

	void _open_sprite_sheet();
	void _prepare_sprite_sheet(const String &p_file);
	int _sheet_preview_position_to_frame_index(const Vector2 &p_position);
	void _sheet_preview_draw();
	void _sheet_spin_changed(double p_value, int p_dominant_param);
	void _sheet_preview_input(const Ref<InputEvent> &p_event);
	void _sheet_scroll_input(const Ref<InputEvent> &p_event);
	void _sheet_add_frames();
	void _sheet_zoom_in();
	void _sheet_zoom_out();
	void _sheet_zoom_reset();
	void _sheet_select_clear_all_frames();

protected:
	void _notification(int p_what);
	void _gui_input(Ref<InputEvent> p_event);
	static void _bind_methods();

public:
	void set_undo_redo(UndoRedo *p_undo_redo) { undo_redo = p_undo_redo; }

	void edit(SpriteFrames *p_frames);
	SpriteFramesEditor();
};

class SpriteFramesEditorPlugin : public EditorPlugin {
	GDCLASS(SpriteFramesEditorPlugin, EditorPlugin);

	SpriteFramesEditor *frames_editor;
	EditorNode *editor;
	Button *button;

public:
	virtual String get_name() const { return "SpriteFrames"; }
	bool has_main_screen() const { return false; }
	virtual void edit(Object *p_object);
	virtual bool handles(Object *p_object) const;
	virtual void make_visible(bool p_visible);

	SpriteFramesEditorPlugin(EditorNode *p_node);
	~SpriteFramesEditorPlugin();
};

#endif // SPRITE_FRAMES_EDITOR_PLUGIN_H
