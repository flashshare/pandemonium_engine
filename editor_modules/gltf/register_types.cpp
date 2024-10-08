/*************************************************************************/
/*  register_types.cpp                                                   */
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

#ifndef _3D_DISABLED

#include "register_types.h"

#include "extensions/gltf_document_extension.h"
#include "extensions/gltf_spec_gloss.h"
#include "extensions/physics/gltf_document_extension_physics.h"
#include "gltf_document.h"
#include "gltf_state.h"

#ifdef TOOLS_ENABLED
#include "editor/editor_node.h"
#include "editor_scene_exporter_gltf_plugin.h"
#include "editor_scene_importer_gltf.h"
#endif

#ifdef TOOLS_ENABLED
static void _editor_init() {
	Ref<EditorSceneImporterGLTF> import_gltf;
	import_gltf.instance();
	ResourceImporterScene::get_singleton()->add_importer(import_gltf);
}
#endif

#define GLTF_REGISTER_DOCUMENT_EXTENSION(m_doc_ext_class) \
	Ref<m_doc_ext_class> extension_##m_doc_ext_class;     \
	extension_##m_doc_ext_class.instance();               \
	GLTFDocument::register_gltf_document_extension(extension_##m_doc_ext_class);

void register_gltf_types(ModuleRegistrationLevel p_level) {
#ifdef TOOLS_ENABLED
	if (p_level == MODULE_REGISTRATION_LEVEL_EDITOR) {
		ClassDB::APIType prev_api = ClassDB::get_current_api();
		ClassDB::set_current_api(ClassDB::API_EDITOR);
		//ClassDB::register_class<EditorSceneImporterGLTF>();
		EditorPlugins::add_by_type<SceneExporterGLTFPlugin>();
		ClassDB::set_current_api(prev_api);
		EditorNode::add_init_callback(_editor_init);
	}
#endif

	if (p_level == MODULE_REGISTRATION_LEVEL_SCENE) {
		ClassDB::register_class<GLTFSpecGloss>();
		ClassDB::register_class<GLTFNode>();
		ClassDB::register_class<GLTFAnimation>();
		ClassDB::register_class<GLTFBufferView>();
		ClassDB::register_class<GLTFAccessor>();
		ClassDB::register_class<GLTFCollider>();
		ClassDB::register_class<GLTFTexture>();
		ClassDB::register_class<GLTFTextureSampler>();
		ClassDB::register_class<GLTFSkeleton>();
		ClassDB::register_class<GLTFSkin>();
		ClassDB::register_class<GLTFCamera>();
		ClassDB::register_class<GLTFMesh>();
		ClassDB::register_class<GLTFLight>();
		ClassDB::register_class<GLTFPhysicsBody>();
		ClassDB::register_class<GLTFState>();
		ClassDB::register_class<GLTFDocument>();
		ClassDB::register_class<GLTFDocumentExtension>();
		ClassDB::register_class<PackedSceneGLTF>();
		GLTF_REGISTER_DOCUMENT_EXTENSION(GLTFDocumentExtensionPhysics);
	}
}

void unregister_gltf_types(ModuleRegistrationLevel p_level) {
	GLTFDocument::unregister_all_gltf_document_extensions();
}

#endif // _3D_DISABLED
