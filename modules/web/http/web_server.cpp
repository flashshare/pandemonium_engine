/*************************************************************************/
/*  web_server.cpp                                                       */
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

#include "web_server.h"

#include "core/object/class_db.h"
#include "web_node.h"
#include "web_server_request.h"

#include "http_session_manager.h"

bool WebServer::get_is_running() {
	return _is_running;
}

WebNode *WebServer::get_web_root() {
	return _web_root;
}

HTTPSessionManager *WebServer::get_session_manager() {
	return _session_manager;
}

void WebServer::server_handle_request(Ref<WebServerRequest> request) {
	ERR_FAIL_COND(!_web_root);

	request->_set_server(this);
	request->_set_web_root(_web_root);

	_rw_lock.read_lock();
	_web_root->handle_request_main(request);
	_rw_lock.read_unlock();
}

void WebServer::request_write_lock() {
	_write_lock_requested = true;
}

void WebServer::refresh_root() {
	_web_root = nullptr;
	_session_manager = nullptr;

	for (int i = 0; i < get_child_count(); ++i) {
		if (!_web_root) {
			_web_root = Object::cast_to<WebNode>(get_child(i));
		}

		if (!_session_manager) {
			_session_manager = Object::cast_to<HTTPSessionManager>(get_child(i));
		}
	}
}

void WebServer::start() {
	call("_start");
}
void WebServer::stop() {
	call("_stop");
}

void WebServer::_start() {
	if (_is_running) {
		return;
	}

	_is_running = true;

	refresh_root();
}
void WebServer::_stop() {
	if (!_is_running) {
		return;
	}

	_is_running = false;
}

Dictionary WebServer::unregister_connection_for_request(const Ref<WebServerRequest> &request) {
	return call("_unregister_connection_for_request", request);
}
Dictionary WebServer::_unregister_connection_for_request(const Ref<WebServerRequest> &request) {
	return Dictionary();
}

String WebServer::get_configuration_warning() const {
	int webnode_count = 0;
	int session_manager_count = 0;

	for (int i = 0; i < get_child_count(); ++i) {
		WebNode *wn = Object::cast_to<WebNode>(get_child(i));

		if (wn) {
			++webnode_count;
		}

		if (!_session_manager) {
			HTTPSessionManager *sm = Object::cast_to<HTTPSessionManager>(get_child(i));

			if (sm) {
				++session_manager_count;
			}
		}
	}

	String err;

	if (webnode_count == 0) {
		err += "You need one (and only one) WebNode as the child for the webserver to work. (A WebRoot Node is recommended by default.)";
	} else if (webnode_count > 1) {
		err += "You have more than one root WebNode as the child of the server. Please move them under a new common WebNode, else the server will only use the first one!";
	}

	if (session_manager_count > 1) {
		if (err != "") {
			err += "\n";
		}

		err += "You have more than one HTTPSessionManager nodes as child, the server will only be able use the first one. Please remove the other.";
	}

	return err;
}

WebServer::WebServer() {
	_is_running = false;

	_web_root = nullptr;
	_session_manager = nullptr;

	_write_lock_requested = false;

	set_process_internal(true);
}

WebServer::~WebServer() {
}

void WebServer::_notification(int p_what) {
	if (p_what == NOTIFICATION_INTERNAL_PROCESS) {
		if (_write_lock_requested) {
			_rw_lock.write_lock();
			notification(NOTIFICATION_WEB_SERVER_WRITE_LOCK_ACQUIRED);
			//the root could have changed.
			refresh_root();
			_rw_lock.write_unlock();

			_write_lock_requested = false;
		}
	}
}

void WebServer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_web_root"), &WebServer::get_web_root);
	ClassDB::bind_method(D_METHOD("get_session_manager"), &WebServer::get_session_manager);

	ClassDB::bind_method(D_METHOD("server_handle_request", "request"), &WebServer::server_handle_request);
	ClassDB::bind_method(D_METHOD("request_write_lock"), &WebServer::request_write_lock);

	BIND_VMETHOD(MethodInfo("_start"));
	BIND_VMETHOD(MethodInfo("_stop"));
	ClassDB::bind_method(D_METHOD("start"), &WebServer::start);
	ClassDB::bind_method(D_METHOD("stop"), &WebServer::stop);
	ClassDB::bind_method(D_METHOD("_start"), &WebServer::_start);
	ClassDB::bind_method(D_METHOD("_stop"), &WebServer::_stop);

	BIND_VMETHOD(MethodInfo(Variant::DICTIONARY, "_unregister_connection_for_request",
			PropertyInfo(Variant::OBJECT, "request", PROPERTY_HINT_RESOURCE_TYPE, "WebServerRequest")));
	ClassDB::bind_method(D_METHOD("unregister_connection_for_request", "request"), &WebServer::unregister_connection_for_request);
	ClassDB::bind_method(D_METHOD("_unregister_connection_for_request", "request"), &WebServer::_unregister_connection_for_request);

	BIND_CONSTANT(NOTIFICATION_WEB_SERVER_STARTED);
	BIND_CONSTANT(NOTIFICATION_WEB_SERVER_STOPPED);
	BIND_CONSTANT(NOTIFICATION_WEB_SERVER_WRITE_LOCK_ACQUIRED);
}
