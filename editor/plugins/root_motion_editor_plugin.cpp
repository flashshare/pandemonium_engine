/*************************************************************************/
/*  root_motion_editor_plugin.cpp                                        */
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

#include "root_motion_editor_plugin.h"

#include "core/containers/list.h"
#include "core/containers/rb_map.h"
#include "core/containers/rb_set.h"
#include "core/error/error_macros.h"
#include "core/object/class_db.h"
#include "core/object/reference.h"
#include "core/os/memory.h"
#include "core/string/string_name.h"
#include "core/typedefs.h"
#include "editor/editor_node.h"
#include "scene/animation/animation.h"
#include "scene/animation/animation_player.h"
#include "scene/animation/animation_tree.h"
#include "scene/gui/box_container.h"
#include "scene/gui/button.h"
#include "scene/gui/dialogs.h"
#include "scene/gui/tree.h"
#include "scene/main/control.h"
#include "scene/main/node.h"
#include "scene/main/scene_tree.h"
#include "scene/main/viewport.h"
#include "scene/resources/texture.h"

#include "modules/modules_enabled.gen.h"

#ifdef MODULE_SKELETON_3D_ENABLED
#include "modules/skeleton_3d/nodes/skeleton.h"
#endif

void EditorPropertyRootMotion::_confirmed() {
	TreeItem *ti = filters->get_selected();
	if (!ti) {
		return;
	}

	NodePath path = ti->get_metadata(0);
	emit_changed(get_edited_property(), path);
	update_property();
	filter_dialog->hide(); //may come from activated
}

void EditorPropertyRootMotion::_node_assign() {
	NodePath current = get_edited_object()->get(get_edited_property());

	AnimationTree *atree = Object::cast_to<AnimationTree>(get_edited_object());
	if (!atree->has_node(atree->get_animation_player())) {
		EditorNode::get_singleton()->show_warning(TTR("AnimationTree has no path set to an AnimationPlayer"));
		return;
	}
	AnimationPlayer *player = Object::cast_to<AnimationPlayer>(atree->get_node(atree->get_animation_player()));
	if (!player) {
		EditorNode::get_singleton()->show_warning(TTR("Path to AnimationPlayer is invalid"));
		return;
	}

	Node *base = player->get_node(player->get_root());

	if (!base) {
		EditorNode::get_singleton()->show_warning(TTR("Animation player has no valid root node path, so unable to retrieve track names."));
		return;
	}

	RBSet<String> paths;
	{
		List<StringName> animations;
		player->get_animation_list(&animations);

		for (List<StringName>::Element *E = animations.front(); E; E = E->next()) {
			Ref<Animation> anim = player->get_animation(E->get());
			for (int i = 0; i < anim->get_track_count(); i++) {
				paths.insert(anim->track_get_path(i));
			}
		}
	}

	filters->clear();
	TreeItem *root = filters->create_item();

	RBMap<String, TreeItem *> parenthood;

	for (RBSet<String>::Element *E = paths.front(); E; E = E->next()) {
		NodePath path = E->get();
		TreeItem *ti = nullptr;
		String accum;
		for (int i = 0; i < path.get_name_count(); i++) {
			String name = path.get_name(i);
			if (accum != String()) {
				accum += "/";
			}
			accum += name;
			if (!parenthood.has(accum)) {
				if (ti) {
					ti = filters->create_item(ti);
				} else {
					ti = filters->create_item(root);
				}
				parenthood[accum] = ti;
				ti->set_text(0, name);
				ti->set_selectable(0, false);
				ti->set_editable(0, false);

				if (base->has_node(accum)) {
					Node *node = base->get_node(accum);
					ti->set_icon(0, EditorNode::get_singleton()->get_object_icon(node, "Node"));
				}

			} else {
				ti = parenthood[accum];
			}
		}

		Node *node = nullptr;
		if (base->has_node(accum)) {
			node = base->get_node(accum);
		}
		if (!node) {
			continue; //no node, can't edit
		}

		if (path.get_subname_count()) {
#ifdef MODULE_SKELETON_3D_ENABLED
			String concat = path.get_concatenated_subnames();

			Skeleton *skeleton = Object::cast_to<Skeleton>(node);
			if (skeleton && skeleton->find_bone(concat) != -1) {
				//path in skeleton
				const String &bone = concat;
				int idx = skeleton->find_bone(bone);
				List<String> bone_path;
				while (idx != -1) {
					bone_path.push_front(skeleton->get_bone_name(idx));
					idx = skeleton->get_bone_parent(idx);
				}

				accum += ":";
				for (List<String>::Element *F = bone_path.front(); F; F = F->next()) {
					if (F != bone_path.front()) {
						accum += "/";
					}

					accum += F->get();
					if (!parenthood.has(accum)) {
						ti = filters->create_item(ti);
						parenthood[accum] = ti;
						ti->set_text(0, F->get());
						ti->set_selectable(0, true);
						ti->set_editable(0, false);
						ti->set_icon(0, get_theme_icon("BoneAttachment", "EditorIcons"));
						ti->set_metadata(0, accum);
					} else {
						ti = parenthood[accum];
					}
				}

				ti->set_selectable(0, true);
				ti->set_text(0, concat);
				ti->set_icon(0, get_theme_icon("BoneAttachment", "EditorIcons"));
				ti->set_metadata(0, path);
				if (path == current) {
					ti->select(0);
				}

			} else {
				//just a property
				ti = filters->create_item(ti);
				ti->set_text(0, concat);
				ti->set_selectable(0, true);
				ti->set_metadata(0, path);
				if (path == current) {
					ti->select(0);
				}
			}
#endif
		} else {
			if (ti) {
				//just a node, likely call or animation track
				ti->set_selectable(0, true);
				ti->set_metadata(0, path);
				if (path == current) {
					ti->select(0);
				}
			}
		}
	}

	filters->ensure_cursor_is_visible();
	filter_dialog->popup_centered_ratio();
}

void EditorPropertyRootMotion::_node_clear() {
	emit_changed(get_edited_property(), NodePath());
	update_property();
}

void EditorPropertyRootMotion::update_property() {
	NodePath p = get_edited_object()->get(get_edited_property());

	assign->set_tooltip(p);
	if (p == NodePath()) {
		assign->set_icon(Ref<Texture>());
		assign->set_text(TTR("Assign..."));
		assign->set_flat(false);
		return;
	}
	assign->set_flat(true);

	Node *base_node = nullptr;
	if (base_hint != NodePath()) {
		if (get_tree()->get_root()->has_node(base_hint)) {
			base_node = get_tree()->get_root()->get_node(base_hint);
		}
	} else {
		base_node = Object::cast_to<Node>(get_edited_object());
	}

	if (!base_node || !base_node->has_node(p)) {
		assign->set_icon(Ref<Texture>());
		assign->set_text(p);
		return;
	}

	Node *target_node = base_node->get_node(p);
	ERR_FAIL_COND(!target_node);

	assign->set_text(target_node->get_name());
	assign->set_icon(EditorNode::get_singleton()->get_object_icon(target_node, "Node"));
}

void EditorPropertyRootMotion::setup(const NodePath &p_base_hint) {
	base_hint = p_base_hint;
}

void EditorPropertyRootMotion::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE || p_what == NOTIFICATION_THEME_CHANGED) {
		Ref<Texture> t = get_theme_icon("Clear", "EditorIcons");
		clear->set_icon(t);
	}
}

void EditorPropertyRootMotion::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_confirmed"), &EditorPropertyRootMotion::_confirmed);
	ClassDB::bind_method(D_METHOD("_node_assign"), &EditorPropertyRootMotion::_node_assign);
	ClassDB::bind_method(D_METHOD("_node_clear"), &EditorPropertyRootMotion::_node_clear);
}

EditorPropertyRootMotion::EditorPropertyRootMotion() {
	HBoxContainer *hbc = memnew(HBoxContainer);
	add_child(hbc);
	assign = memnew(Button);
	assign->set_flat(true);
	assign->set_h_size_flags(SIZE_EXPAND_FILL);
	assign->set_clip_text(true);
	assign->connect("pressed", this, "_node_assign");
	hbc->add_child(assign);

	clear = memnew(Button);
	clear->set_flat(true);
	clear->connect("pressed", this, "_node_clear");
	hbc->add_child(clear);

	filter_dialog = memnew(ConfirmationDialog);
	add_child(filter_dialog);
	filter_dialog->set_title(TTR("Edit Filtered Tracks:"));
	filter_dialog->connect("confirmed", this, "_confirmed");

	filters = memnew(Tree);
	filter_dialog->add_child(filters);
	filters->set_v_size_flags(SIZE_EXPAND_FILL);
	filters->set_hide_root(true);
	filters->connect("item_activated", this, "_confirmed");
	//filters->connect("item_edited", this, "_filter_edited");
}
//////////////////////////

bool EditorInspectorRootMotionPlugin::can_handle(Object *p_object) {
	return true; //can handle everything
}

void EditorInspectorRootMotionPlugin::parse_begin(Object *p_object) {
	//do none
}

bool EditorInspectorRootMotionPlugin::parse_property(Object *p_object, Variant::Type p_type, const String &p_path, PropertyHint p_hint, const String &p_hint_text, int p_usage) {
	if (p_path == "root_motion_track" && p_object->is_class("AnimationTree") && p_type == Variant::NODE_PATH) {
		EditorPropertyRootMotion *editor = memnew(EditorPropertyRootMotion);
		if (p_hint == PROPERTY_HINT_NODE_PATH_TO_EDITED_NODE && p_hint_text != String()) {
			editor->setup(p_hint_text);
		}
		add_property_editor(p_path, editor);
		return true;
	}

	return false; //can be overridden, although it will most likely be last anyway
}

void EditorInspectorRootMotionPlugin::parse_end() {
	//do none
}
