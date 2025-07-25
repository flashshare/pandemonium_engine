/**************************************************************************/
/*  scene_tree_fti_tests.h                                                */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef SCENE_TREE_FTI_TESTS_H
#define SCENE_TREE_FTI_TESTS_H

class Spatial;
class Node;
class Transform;
class SceneTreeFTI;

class SceneTreeFTITests {
	SceneTreeFTI &_fti;

	void debug_verify_failed(const Spatial *p_spatial, const Transform &p_test);

public:
	void update_dirty_spatials(Node *p_node, uint32_t p_current_half_frame, float p_interpolation_fraction, bool p_active, const Transform *p_parent_global_xform = nullptr, int p_depth = 0);
	void frame_update(Node *p_root, uint32_t p_half_frame, float p_interpolation_fraction);

	SceneTreeFTITests(SceneTreeFTI &p_fti);
};

#endif // SCENE_TREE_FTI_TESTS_H
